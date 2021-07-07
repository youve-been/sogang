#include <stdio.h> /* 20201631 장유빈*/
/* 문자, 정수, 실수를 각각 하나씩 입력받고 입력받은 그대로 출력하는 프로그램 */

int main(void)
{
	char ch; /*Ch, integer, real는 identifier이고 Ch는 문자형 변수,*/
	int integer; /*integer는 정수형 변수,*/
	float real; /*real는 실수형 변수이다.*/

	printf("Input one character, one integer, one real number : ");
	scanf("%c %d %f", &ch, &integer, &real); /*scanf() 함수를 통해 값을 입력받는다. 입력받을 때는 변수이름 앞에 &를 붙여준다.*/
	/*printf() 함수를 통해 값을 출력한다. 값을 입력받고 출력할 때 type에 따라 다른 형식문자(%c, %d, %f)를 사용한다.*/
	printf("%c %d %f\n", ch, integer, real); /*하나의 scanf() 함수에서 여러 개의 입력을 받을 때 각각의 입력 값은 스페이스로 구분을 하여 입력한다.*/

	return 0;
}

