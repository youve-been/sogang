#include <stdio.h>
#include <string.h>
#define max_string_size 100   //string의 최대 길이
#define max_pattern_size 100   //pat의 최대 길이
int pmatch(char *string, char *pat);   //pattern-matching function
void fail(char *pat);   //failure 배열을 작성하는 함수
int failure[max_pattern_size];
char string[max_string_size];
char pat[max_pattern_size];

int main(void)
{
    FILE *fp;

    fp = fopen("kmp.txt", "rt");   //kmp.txt 열기
    
    fscanf(fp, "%s", string);   //kmp.txt 파일로부터 string 입력받기
    fscanf(fp, "%s", pat);   //kmp.txt 파일로부터 pat 입력받기

    fail(pat);   //failure 배열 작성
    printf("%d\n", pmatch(string, pat));   //pattern-matching 결과 출력

    fclose(fp);
    return 0;
}

int pmatch(char *string, char *pat) {   //패턴 매칭 함수
    int i = 0, j = 0;
    int lens = strlen(string);   //string 배열의 크기
    int lenp = strlen(pat);   //pat 배열의 크기
    while (i < lens && j < lenp) {   //문자열이 모두 비교가 끝날 때까지
        if(string[i] == pat[j]) {   //겹치는 문자를 발견
            i++;
            j++;
        }
        else if (j == 0)  //pat 배열의 시작부터 문자열이 겹치지 않는 경우
            i++;
        else   //문자열 비교가 진행되던 도중 겹치지 않는 문자를 발견했을 때
            j = failure[j-1]+1;  //j 이전에 있는 겹치는 부분문자열 이후부터 다시 비교 시작
    }
    return ((j == lenp) ? (i - lenp) : -1);   //string에서 pat 발견하면 시작위치, 발견 못하면 -1 반환
        //j==lenp : string에서 pat 발견
        //i-lenp : string에서 pat이 시작하는 위치
}

void fail(char *pat) {   //failure 배열 작성하는 함수
    int i, j, n = strlen(pat);   //pat 배열 크기
    failure[0] = -1;   //pat의 시작이므로 원소값 = -1
    for(j = 1; j < n; j++) {
        i = failure[j-1];   //이전까지의 진행상황(이전까지 부분문자열이 얼마나 겹쳤는지)
        while ((pat[j] != pat[i+1]) && (i >= 0))   //인덱스가 j-1일 때 겹치는 문자열 존재 && 문자열이 이어서 겹쳐지지 않음
            i = failure[i];   //다시 비교 위치 설정
        if (pat[j] == pat[i+1])   //겹치는 문자열의 시작을 발견
            failure[j] = i+1;   
        else //겹치는 문자열 없음
            failure[j] = -1;   
    }
}