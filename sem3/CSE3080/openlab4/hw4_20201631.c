#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50
typedef enum {head, entry} tagfield;
typedef struct matrix_node *matrix_pointer;
typedef struct {
    int row;
    int col;
    int value;
} entry_node;

typedef struct matrix_node{
    matrix_pointer down;
    matrix_pointer right;
    tagfield tag;
    union {
        matrix_pointer next;
        entry_node entry;
    } u;

    matrix_pointer hdnode[MAX_SIZE];
} matrix_node;

matrix_pointer new_node();   //새로운 노드를 생성하는 함수
matrix_pointer mread(FILE *fp);   //파일에서 행렬을 읽어 리스트에 저장하는 함수
void mwrite(matrix_pointer);   //행렬을 2차원 행렬형태로 출력하는 함수
void merase(matrix_pointer*);   //리스트를 비우는 함수

void main() {
    matrix_pointer a, b;
    FILE *fpa, *fpb;

    fpa = fopen("A.txt", "rt");
    fpb = fopen("B.txt", "rt");
    
    a = mread(fpa);
    b = mread(fpb);
    printf("Matrix A\n");
    mwrite(a);
    printf("Matrix B\n");
    mwrite(b);
    merase(&a);
    merase(&b);
    printf("Matrix A\n");
    mwrite(a);
    printf("Matrix B\n");
    mwrite(b);

    fclose(fpa);
    fclose(fpb);
}

matrix_pointer new_node() {
    matrix_pointer new;
    new = (matrix_node *)malloc(sizeof(matrix_node));
    return new;
}

matrix_pointer mread(FILE *fp) {
    int num_rows, num_cols, num_terms, num_heads, tmp, i;
    int row, col, value, current_row;
    matrix_pointer temp, last, node;

    fscanf(fp, "%d %d", &num_rows, &num_cols);   //행과 열 수 입력
    num_terms = 0;
    for(i = 0; i < num_rows*num_cols; i++) {   //0이 아닌 숫자의 개수 확인
        fscanf(fp, "%d", &tmp);   //행렬 값 하나씩 확인
        if(tmp != 0)
            num_terms++;
    }
    num_heads = (num_cols > num_rows) ? num_cols: num_rows;   //head node의 개수
    node = new_node();   //node는 head node의 head node
    node->tag = entry;
    node->u.entry.row = num_rows;
    node->u.entry.col = num_cols;

    if(!num_heads)   //num_heads가 0인 경우
        node->right = node;
    else {   
        for(i = 0; i < num_heads; i++) {   //head node 초기화
            temp = new_node();
            node->hdnode[i] = temp;
            node->hdnode[i]->tag = head;
            node->hdnode[i]->right = temp;
            node->hdnode[i]->u.next = temp;
        }
        current_row = 0;
        row = 0;
        col = 0;
        rewind(fp);   //다시 행렬을 읽기 위해 파일포인터를 파일의 처음으로 되돌려줌
        fscanf(fp, "%d %d", &num_rows, &num_cols);   //행렬부터 읽어들이기 위해
        last = node->hdnode[0];
        for(i = 0; i < num_terms; i++) {
            while(1) {   //0이 아닌 entry 찾기
                if(col == num_cols) {
                    row++;
                    col = 0;
                }
                fscanf(fp, "%d", &value);
                if(value != 0) {
                    break;
                }
                col++;
            }
            if(row>current_row) {   //현재 row에서는 0이 아닌 entry를 모두 찾았을 경우
                last->right = node->hdnode[current_row];
                current_row = row;
                last = node->hdnode[row];
            }
	//새로운 entry를 리스트에 입력
            temp = new_node();
            temp->tag = entry;
            temp->u.entry.row = row;
            temp->u.entry.col = col;
            temp->u.entry.value = value;
            last->right = temp;
            last = temp;
            node->hdnode[col]->u.next->down = temp;
            node->hdnode[col]->u.next = temp;
            col++;
        }
        last->right = node->hdnode[current_row];   //마지막 노드를 head node와 연결해줌
        for(i = 0; i < num_cols; i++)   //head node 연결
            node->hdnode[i]->u.next->down = node->hdnode[i];
        for(i = 0; i < num_heads-1; i++)
            node->hdnode[i]->u.next = node->hdnode[i+1];
        node->hdnode[num_heads-1]->u.next = node;
        node->right = node->hdnode[0];
    }
    return node;   //head node의 head node 반환
}

void mwrite(matrix_pointer node) {    
    if(node == NULL)   //리스트가 비어있을 경우
        printf("Empty Matrix!!\n");
    else {
        int i, col;
        matrix_pointer temp, head = node->right;
        for(i= 0; i < node->u.entry.row; i++) {
            col = 0;
            for(temp = head->right; temp != head; temp=temp->right) {
                while(temp->u.entry.col > col) {   //0이 아닌 entry가 나오기 전까지 0 출력
                    printf("   0");
                    col++;
                }
                printf("%4d", temp->u.entry.value);
                col++;
            }
            while(col < node->u.entry.col) {   //다음 row로 넘어가기 전까지 0 출력
                printf("   0");
                col++;
            }
                
            head = head->u.next;
            printf("\n");
        }
    }
}

void merase(matrix_pointer *node) {
    if((*node) == NULL)   //리스트가 비어있을 경우
        return;
    int i, num_heads;
    matrix_pointer x, y, head = (*node)->right;

    for(i = 0; i < (*node)->u.entry.row; i++) {
        y = head->right;
        while (y != head) {   //head node에 이어진 entry가 없을 때까지 삭제
            x = y;
            y = y->right;
            free(x);
        }
        x = head;   //마지막으로 head node도 삭제
        head = head->u.next;
        free(x);
    }
    y = head;   //head node의 head node 삭제
    while(y != *node) {
        x = y;
        y = y->u.next;
        free(x);
    }
    free(*node);
    *node = NULL;
}
