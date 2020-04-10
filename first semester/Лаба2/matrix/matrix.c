#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#pragma warning (disable: 4996)
double **matr, **matr1, **L, **U, **L1, **U1;
double *b, *b1;
int size;
void nevyazka (double ***A, double **x, double **b)
{
	double *C;
	int i, k;
	C = (double *) malloc(size*sizeof(double));
	for(i = 0; i < size; i++)
	{
		C[i] = 0;
		for(k = 0; k < size; k++)
		{
			C[i] += (*A)[i][k] * (*x)[k];
		}
	}
	printf("������ �������: \n");
	for (i=0; i<size; i++)
	{
		printf("%e \n", C[i] - (*b)[i]);
	}
}
void readB (double **b, char *string1, char *string2)
{
	FILE *f, *f1;
	int i;
	*b = (double *) malloc (sizeof(double)*size);
	f = fopen(string1, "r");
	f1 = fopen(string2, "a");
	printf("������ b: \n");
	for (i=0; i<size; i++)
	{
		fscanf(f, "%lf", &(*b)[i]);
		printf("%lf\n", (*b)[i]);
		fprintf(f1, "%lf ", (*b)[i]);
	}
	fprintf(f1, "\n");
	fclose(f1);
	fclose(f);
}
void print(double **arr, int size1, int size2)
{
	int i, j;
	for (i=0; i<size1; i++)
	{
		for (j=0; j<size2; j++)
		{
			printf("%lf ", arr[i][j]);
		}
		printf("\n");
	}
}
void readA (double ***matr, char *string)
{
	FILE *f;
	int i, j;
	double cond;
	f = fopen(string, "r");
	fscanf(f, "%i", &size);
	*matr = (double **) malloc(sizeof(double *)*size);
	for (i=0; i<size; i++)
	{
		(*matr)[i] = (double *) malloc(sizeof(double)*size);
	}
	printf("������� �: \n");
	for (i=0; i<size; i++)
	{
		for (j=0; j<size; j++)
		{
			fscanf(f, "%lf", &(*matr)[i][j]);
			printf("%lf ", (*matr)[i][j]);
		}
		printf("\n");
	}
	fscanf(f, "%lf", &cond);
	printf("cond(A) = %lf\n", cond);
	fclose(f);
}
void LU (double ***L, double ***U, double ***A)
{
	int i, j, k;
	*L = (double **) malloc(sizeof(double *)*size);
	for (i=0; i<size; i++)
	{
		(*L)[i] = (double *) malloc(sizeof(double)*size);
	}
	*U = (double **) malloc(sizeof(double *)*size);
	for (i=0; i<size; i++)
	{
		(*U)[i] = (double *) malloc(sizeof(double)*size);
	}
	for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            if(i==j) (*L)[i][j]=1;
            else (*L)[i][j]=0;
			(*U)[i][j] = (*A)[i][j];
        }
    }
	for(k = 1; k < size; k++)
	{
		for(i = k-1; i < size; i++)
			for(j = i; j < size; j++)
				(*L)[j][i]=(*U)[j][i]/(*U)[i][i];

		for(i = k; i < size; i++)
			for(j = k-1; j < size; j++)
				(*U)[i][j]=(*U)[i][j]-(*L)[i][k-1]*(*U)[k-1][j];
	}
	printf("������� L: \n");
	print(*L, size, size);
	printf("������� U: \n");
	print(*U, size, size);
	printf("�����, ��� L*U = A\n");
}
void solve (double ***L, double ***U, double **b, double ***A, char *string)
{
	FILE *f;
	double *y, *x;
	double sum=0;
	int i, j;
	y = (double *) malloc(sizeof(double)*sizeof(double));
	x = (double *) malloc(sizeof(double)*sizeof(double));
	printf("������ ��������� Ax = b (LUx = b) � ��� �����. \n");
	printf("������� ������� ������� Ly = b ��������������� ������ ������������. \n");
	printf("������ y: \n");
	y[0] = (*b)[0];
	for (i=1; i<size; i++)
	{
		sum =0;
		for (j=0; j<=i-1; j++)
		{
			sum+=(*L)[i][j]*y[j];
		}
		y[i] = (*b)[i] - sum;
	}
	for (i=0; i<size; i++)
	{
		printf("%lf\n", y[i]);
	}
	printf("������� ������� ������� Ux = y ��������������� �������� ������������. \n");
	printf("������ x ������� ����: \n");
	x[size-1] = y[size-1]/(*U)[size-1][size-1];
	for (i=size-2; i>=0; i--)
	{
		sum = 0;
		for (j=size-1; j>=i+1; j--)
		{
			sum+=(*U)[i][j]*x[j];
		}
		x[i] = (y[i] - sum)/(*U)[i][i];
	}
	f = fopen(string, "a");
	for (i=0; i<size; i++)
	{
		printf("%lf\n", x[i]);
		fprintf(f, "%lf ", x[i]);
	}
	fprintf(f, "\n");
	fclose(f);
	nevyazka(A, &x, b);
}
void errors (double ***A, double **b, double ***L, double ***U, char *string)
{
	FILE *f;
	double **newA, *newb;
	double left=1.0, right=1.01;
	int i, j;
	newA = (double **) malloc(sizeof(double *)*size);
	newb = (double *) malloc(sizeof(double)*size);
	for (i=0; i<size; i++)
	{
		newA[i] = (double *) malloc(sizeof(double)*size);
	}
	f = fopen(string, "a");
	for (i=0; i<size; i++)
	{
		newb[i] = (left + (((double) rand())/(RAND_MAX+1)) * (right-left))*(*b)[i];
		for (j=0; j<size; j++)
		{
			newA[i][j] = (left + (((double) rand())/(RAND_MAX+1)) * (right-left))*(*A)[i][j];
			fprintf(f, "%lf ", newA[i][j]);
		}
		fprintf(f, "\n");
	}
	printf("������ ��������� � ������� � �� ������ ������ �������� � ����� ��������� �����:\n");
	LU(L, U, &newA);
	solve(L, U, b, &newA, string);
	printf("������ ��������� � ������ b �� ������ ������ �������� � ����� ��������� �����: \n");
	for (i=0; i<size; i++)
	{
		fprintf(f, "%lf ", newb[i]);
	}
	fprintf(f, "\n");
	fclose(f);
	LU(L, U, A);
	solve(L, U, &newb, A, string);
}
void main()
{
	char str1[] = "matrix1.txt";
	char str2[] = "matrix2.txt";
	char str3[] = "vector1.txt";
	char str4[] = "vector2.txt";
	SetConsoleCP (1251);
	SetConsoleOutputCP(1251);
	printf("��� ������ ������������� �������: \n");
	readA(&matr, str1);
	readB(&b, str3, str1);
	LU(&L, &U, &matr);
	solve(&L, &U, &b, &matr, str1);
	errors(&matr, &b, &L, &U, str1);
	printf("��� ����� ������������� �������: \n");
	readA(&matr1, str2);
	readB(&b1, str4, str2);
	LU(&L1, &U1, &matr1);
	solve(&L1, &U1, &b1, &matr1, str2);
	errors(&matr1, &b1, &L1, &U1, str2);
}