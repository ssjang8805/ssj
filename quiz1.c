#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct domain{			// domain ����ü ����(���� : int size, int *value) 
	int size;
	int *value;
}Domain;						// Domain ���� rename ��Ŵ

int isOddNumber(int value);		// value ���� Ȧ������ �Ǵ��ϴ� �Լ�
int isPrimeNumber(int value);	// value ���� �Ҽ����� �Ǵ��ϴ� �Լ�
int isGreaterThan10(int value);	// value ���� 10���� ū�� Ȯ���ϴ� �Լ�
int universal(Domain* domain, int (*prove)(int));		// ��� value �� ���Ͽ� �����ϴ��� Ȯ���ϴ� �Լ�
int existential(Domain* domain, int (*prove)(int));		// � value �� ���Ͽ� �����ϴ��� Ȯ���ϴ� �Լ�(�κ�)

int main(int argc, char* argv[])
{
	Domain* d = 0;				// Domain ����ü ���� d �ʱ�ȭ
	int (*prove)(int);			// �Լ� ������ ����

	d = (Domain*) malloc(sizeof(Domain));		// �޸� �Ҵ�κ�
	d->value = (int *) malloc(sizeof(int)*5);
	d->size = 5;									// size 5�� ���� Domain ����
	d->value[0] = 2;							// d->value[0] ~ d->value[4]							
	d->value[1] = 3;
	d->value[2] = 7;
	d->value[3] = 14;
	d->value[4] = 16;

	prove = isGreaterThan10;						// �Լ������ͷ� ���� 10���� ū �� Ȯ���ϴ� �Լ� ����

	if(prove == isOddNumber)					// �Լ������Ͱ� isOddNumber �Լ��� ����ų ��
		printf("P(x) = x is odd integer\n");	
	else if(prove == isPrimeNumber)				// �Լ������Ͱ� isPrimeNumber �Լ��� ����ų ��
		printf("P(x) = x is prime integer\n");
	else										// �� �� �Լ������Ͱ� isGreaterThan10 �Լ��� ����ų ��
		printf("P(x) = x is greater than 10\n");
	
	universal(d,prove);							
	existential(d,prove);
}

int isOddNumber(int value)
{	
	return (value%2 == 1);				// value ���� 2�� ���� �������� 1�� �� Ȧ��
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
	if(temp == 0)						// i ���� ������Ű�� value �� �ƹ������ε� ������ ���� ���� ��
		return TRUE;
	else
		return FALSE;
}

int isGreaterThan10(int value)
{
	return (value > 10);			// 10���� Ŭ ��
}

int universal(Domain* d, int (*prove)(int))
{
	int i;
	printf("Domain is <");
	for(i=0 ; i<d->size ; i++)				// ������ ��� �κ�
	{
		if(i == d->size-1)
			printf("%d>. ",d->value[i]);
		else
			printf("%d, ",d->value[i]);
	}
	printf("\n\n");
	for(i=0 ; i<d->size ; i++)
	{
		if (!prove(d->value[i]))					// ��� x�� ���� �������� ���� ��
		{
			printf("For Some x, P(x) is false.\n");
			return FALSE;
		}			
	}
	printf("For Some x, P(x) is true.\n");		// ��� x�� ���� �����ϹǷ� true ���
	return TRUE;
}

int existential(Domain* d, int (*prove)(int))
{
	int i;
	for(i=0 ; i<d->size ; i++)
	{
		if (prove(d->value[i]))
		{
			printf("For All x, P(x) is true.\n");	// � x�� ���� ������ �� true ���
			return TRUE;
		}
	}
	return FALSE;									// �� �� false ���
}