#include <stdio.h>
#include <stdlib.h>
#define MAX_EXPR_SIZE 100

//편의를 위해 입력을 모두 enum으로 정리
typedef enum {lparen, rparen, plus, minus, times, divide, mod, eos, operand}
    precedence;
precedence token;

//LinkedList 구현을 위한 node
typedef struct NODE {
    struct NODE *link;   //다음 node의 주소를 저장하는 변수
    char data;   //연산자 및 피연산자를 저장하는 변수
} NODE;

NODE *top;   //첫 번째 노드
char expr[MAX_EXPR_SIZE];   //postfix로 바꿔야할 수식이 담긴 배열
//우선순위가 높을수록 배열의 원소값으로 큰 수를 할당
int isp[] = {0, 3, 1, 1, 2, 2, 2, 0};   // stack 안의 operator에 대한 precedence
int icp[] = {4, 3, 1, 1, 2, 2, 2, 0};   // stack에 들어오는 operator에 대한 precedence

//필요한 함수 목록
void postfix( );
precedence getToken(char *expr, int *n);
void rExpr(FILE *fp, char *expr);
void printToken(char token);
void push(char data);
char pop();

int main(void)
{
    FILE *fp;

    rExpr(fp, expr);
    postfix();

    fclose(fp);

    return 0;
} 

//infix로 작성된 수식을 postfix로 바꾸는 함수
void postfix()
{
    char symbol;
    int n = 0;
    top = (NODE *)malloc(sizeof(NODE));
    top->data = eos;   //가장 하위 우선순위인 eos를 stack의 바닥에 깔아두기
    
    for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
        if (token == operand)   //피연산자인 경우
            printf("%c ", symbol);   //피연산자 그대로 출력
        else if (token == rparen) {   //오른쪽 괄호인 경우
            while (top->data != lparen)   //왼쪽 괄호 이전까지
                printToken(pop());   //stack 안의 연산자를 꺼내어 출력
            pop();   //왼쪽 괄호 삭제
        }
        else {   //오른쪽 괄호를 제외한 연산자의 경우
            char tmp = token;
            //stack 안 연산자가 현재 연산자보다 우선순위가 높거나 같을 경우
            while (isp[top->data] >= icp[tmp])
                printToken(pop());   //stack에서 꺼내어 출력
            push(token);   //연산자를 stack에 저장
        }
    }

    while ((token = pop()) != eos)   //남은 연산자 모두 출력
        printToken(token);
    printf("\n");
}

//expr 배열의 n번째 원소를 enum precedence 원소 중 하나로 변환하는 함수
precedence getToken(char *symbol, int *n)
{
    *symbol = expr[(*n)++];   //함수가 호출될 때마다 expr 배열의 다음 원소를 읽어옴
    switch (*symbol) {
        case '(' : return lparen;
        case ')' : return rparen;
        case '+' : return plus;
        case '-' : return minus;
        case '/' : return divide;
        case '*' : return times;
        case '%' : return mod;
        case ' ' : return eos;   //문자열의 끝
        default : return operand;   //위 연산자가 아니면 피연산자로 간주
    }
}

//파일을 오픈하여 파일 안 수식을 공백 제거하여 expr 배열에 저장하는 함수
void rExpr(FILE *fp, char *arr)
{
    int i, index;   //공백 제거 시 각각 tmp와 expr의 인덱스로 사용
    char tmp[MAX_EXPR_SIZE] = {};   //공백을 제거하기 전 수식을 담을 배열
    fp = fopen("expr.txt", "rt");   //수식이 담긴 파일 열기
    fgets(tmp, sizeof(tmp), fp);

    // 공백 제거하기
    for(i = 0, index = 0; tmp[i] != '\0'; i++) {
        if(tmp[i] != ' ') {
            expr[index] = tmp[i];   //공백이 아닌 경우만 expr 배열에 대입
            index++;
        }
    }
    expr[index] = ' ';   //마지막 원소에 공백을 대입하여 문자열의 끝임을 표시
}

//stack에 원소를 집어넣는 함수
void push(char data)
{
    NODE *new;   //삽입되는 원소를 위한 node
    new = (NODE *)malloc(sizeof(NODE));
    new->data = data;
    new->link = top;   //new를 가장 위에 배치해야 하므로 new를 top에 연결
    top = new;   //new가 가장 위에 있으므로 top에 new의 주소 저장 
}

//stack에서 원소를 삭제하고, 원소값을 반환하는 함수
char pop()
{
    int data = top->data;
    NODE *tmp = top;
    top = tmp->link;   //top에 두 번째 node의 주소 저장
    free(tmp);   //가장 위에 있던 node 삭제
    return data;   //원소값 반환
}

//제시된 token을 문자로 변환하여 출력하는 함수
void printToken(char token)
{
    switch (token) {   //주어진 token을 문자로 변환
        //postfix 표기법의 경우 괄호를 사용하지 않으므로
        //괄호는 출력하지 않음
        case plus : printf("+ "); break;
        case minus : printf("- "); break;
        case divide : printf("/ "); break;
        case times : printf("* "); break;
        case mod : printf("%% "); break;
    }
}