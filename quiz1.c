#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct domain{			// domain 구조체 선언(변수 : int size, int *value) 
	int size;
	int *value;
}Domain;						// Domain 으로 rename 시킴

int isOddNumber(int value);		// value 값이 홀수인지 판단하는 함수
int isPrimeNumber(int value);	// value 값이 소수인지 판단하는 함수
int isGreaterThan10(int value);	// value 값이 10보다 큰지 확인하는 함수
int universal(Domain* domain, int (*prove)(int));		// 모든 value 에 대하여 만족하는지 확인하는 함수
int existential(Domain* domain, int (*prove)(int));		// 어떤 value 에 대하여 만족하는지 확인하는 함수(부분)

int main(int argc, char* argv[])
{
	Domain* d = 0;				// Domain 구조체 변수 d 초기화
	int (*prove)(int);			// 함수 포인터 선언

	d = (Domain*) malloc(sizeof(Domain));		// 메모리 할당부분
	d->value = (int *) malloc(sizeof(int)*5);
	d->size = 5;									// size 5에 대한 Domain 지정
	d->value[0] = 2;							// d->value[0] ~ d->value[4]							
	d->value[1] = 3;
	d->value[2] = 7;
	d->value[3] = 14;
	d->value[4] = 16;

	prove = isGreaterThan10;						// 함수포인터로 값이 10보다 큰 지 확인하는 함수 지정

	if(prove == isOddNumber)					// 함수포인터가 isOddNumber 함수를 가리킬 때
		printf("P(x) = x is odd integer\n");	
	else if(prove == isPrimeNumber)				// 함수포인터가 isPrimeNumber 함수를 가리킬 때
		printf("P(x) = x is prime integer\n");
	else										// 그 외 함수포인터가 isGreaterThan10 함수를 가리킬 때
		printf("P(x) = x is greater than 10\n");
	
	universal(d,prove);							
	existential(d,prove);
}

int isOddNumber(int value)
{	
	return (value%2 == 1);				// value 값을 2로 나눈 나머지가 1일 때 홀수
}

int isPrimeNumber(int value)
{
	int i;
	int temp=0;
	
	for(i=2 ; i<value ; i++)
	{
		if(value%i==0)
			temp++;
	}
	if(temp == 0)						// i 값을 증가시키며 value 가 아무것으로도 나누어 지지 않을 때
		return TRUE;
	else
		return FALSE;
}

int isGreaterThan10(int value)
{
	return (value > 10);			// 10보다 클 때
}

int universal(Domain* d, int (*prove)(int))
{
	int i;
	printf("Domain is <");
	for(i=0 ; i<d->size ; i++)				// 도메인 출력 부분
	{
		if(i == d->size-1)
			printf("%d>. ",d->value[i]);
		else
			printf("%d, ",d->value[i]);
	}
	printf("\n\n");
	for(i=0 ; i<d->size ; i++)
	{
		if (!prove(d->value[i]))					// 모든 x에 대해 만족하지 않을 때
		{
			printf("For Some x, P(x) is false.\n");
			return FALSE;
		}			
	}
	printf("For Some x, P(x) is true.\n");		// 모든 x에 대해 만족하므로 true 출력
	return TRUE;
}

int existential(Domain* d, int (*prove)(int))
{
	int i;
	for(i=0 ; i<d->size ; i++)
	{
		if (prove(d->value[i]))
		{
			printf("For All x, P(x) is true.\n");	// 어떤 x에 대해 만족할 때 true 출력
			return TRUE;
		}
	}
	return FALSE;									// 그 외 false 출력
}