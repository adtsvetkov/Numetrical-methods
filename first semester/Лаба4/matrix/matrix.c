#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#pragma warning (disable: 4996)
double **matr;
double **G, **Gt;
double **vector;
int size;
int ii, jj;
double max=0;
double eps = 0.01;
void nevyazka(double ***matr, double ***vector, char *string)
{
	FILE *f;
	int s, i, j, k;
	double **A = (double **) malloc(sizeof(double *)*size);
	double *res = (double *) malloc(sizeof(double)*size);
	double *res1 = (double *) malloc(sizeof(double)*size);
	for (i=0; i<size; i++) A[i] = (double *)malloc(sizeof(double)*size);
	f = fopen(string, "r");
	fscanf(f, "%i", &s);
	for (i=0; i<size; i++)
	{
		for (j=0; j<size; j++)
		{
			fscanf(f, "%lf", &A[i][j]);
		}
	}
	fclose(f);
	printf("Норма вектора невязки: Аx=lx\n");
	s = 0;
	while (s<size)
	{
		for (i=0; i<size; i++)
		{
			for (j=0; j<1; j++)
			{
				res[i] = 0;
				for (k=0; k<size; k++)
				{
					res[i]+= A[i][k]*(*vector)[k][s];
				}
			}
		}
		for (i=0; i<size; i++) res1[i] = (*vector)[i][s]*(*matr)[s][s];
		for (i=0; i<size; i++) 
		{
			//printf("%e\n", res[i]-res1[i]);
			if (res[i]-res1[i]>max) max = res[i]-res1[i];
		}
		//printf("\n");
		s++;
	}
	printf("%e\n", max);
}
void trans (double ***matr1, double ***matr2)
{
	int i, j;
	for (i=0; i<size; i++)
	{
		for (j=0; j<size; j++)
		{
			(*matr1)[i][j] = (*matr2)[j][i];
		}
	}
}
double find (double ***matr)
{
	int i, j;
	double max=0;
	for (i=0; i<size; i++)
	{
		for (j=0; j<size; j++)
		{
			if (i!=j)
			{
				if (fabs((*matr)[i][j]) > fabs(max)) max = (*matr)[i][j];
			}
		}
	}
	return fabs(max);
}
void vectorfill(double ***vector)
{
	int i, j;
	*vector = (double **) malloc(sizeof(double*)*size);
	for (i=0; i<size; i++)
	{
		(*vector)[i] = (double *) malloc (sizeof(double)*size);
	}
	for (i=0; i<size; i++)
	{
		for (j=0; j<size; j++)
		{
			if(i==j) (*vector)[i][j] = 1;
			else (*vector)[i][j] = 0;
		}
	}
}
void multiply (double ***matr, double ***matr1, double ***res)
{
	int i, j, k;
	double **result = (double **) malloc (sizeof(double *)*size);
	for (i=0; i<size; i++) result[i] = (double *) malloc (sizeof(double)*size);
	for (i=0; i<size; i++)
	{
		for (j=0; j<size; j++)
		{
			result[i][j] = 0;
			for (k = 0; k<size; k++)
			{
				result[i][j] += (*matr)[i][k]*(*matr1)[k][j];
			}
		}
	}
	for (i=0; i<size; i++)
	{
		for (j=0; j<size; j++)
		{
			(*res)[i][j] = result[i][j];
		}
	}
	for (i=0; i<size; i++) free(result[i]);
	free(result);
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
	printf("Исходная матрица A: \n");
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
	printf("Cond(A) = %lf\n", cond);
	fclose(f);
}
void turn (double ***g, double ***gt, double ***matr)
{
	double tan, s, c;
	int i, j;
	for (i=0; i<size; i++)
	{
		for (j=0; j<size; j++)
		{
			if (i!=j) (*g)[i][j] = 0;
			else (*g)[i][j] = 1;
		}
	}
	if (((*matr)[jj][jj] - (*matr)[ii][ii])!=0)
	{
		tan = 2*(*matr)[ii][jj]/((*matr)[jj][jj] - (*matr)[ii][ii]);
		printf("fi = %lf\n", 0.5*atan(tan));
		s = sqrt(0.5*(1-1/(sqrt(1+tan*tan))));
		c = sqrt(0.5*(1+1/(sqrt(1+tan*tan))));
		if (tan<0) s=-s;
	}
	else
	{
		s = sqrt(0.5);
		c = sqrt(0.5);
	}
	(*g)[ii][ii] = c;
	(*g)[jj][ii] = -s;
	(*g)[ii][jj] = s;
	(*g)[jj][jj] = c;
	printf("U = \n");
	for (i=0; i<size; i++)
	{
		for (j=0; j<size; j++)
		{
			printf("%lf ", (*g)[i][j]);
		}
		printf("\n");
	}
	trans(gt, g);
}
void solve (double ***matr, double ***g, double ***gt, double ***vector)
{
	double max=0, sum;
	int i, j;
	int count = 0;
	*g = (double **) malloc (sizeof(double *)*size);
	*gt = (double **) malloc (sizeof(double *)*size);
	for (i=0; i<size; i++)
	{
		(*g)[i] = (double *) malloc (sizeof(double)*size);
		(*gt)[i] = (double *) malloc (sizeof(double)*size);
	}
	vectorfill(vector);
	while (find(matr) > eps)
	{
		printf("\nИтерация %i:\n\n", count+1);
		for (i=0; i<size; i++)
		{
			sum = 0;
			for (j=0; j<size; j++)
			{
				if (i!=j) sum += ((*matr)[i][j])*((*matr)[i][j]);
			}
			if (max<sum)
			{
				max = sum;
				ii = i;
			}
		}
		max = 0;
		for (j=0; j<size; j++)
		{
			if (j!=ii)
			{
				if (fabs((*matr)[ii][j])>fabs(max))
				{
					max = (*matr)[ii][j];
					jj = j;
				}
			}
		}
		//printf("matr[i][j] = %lf, matr[i][i] = %lf, matr[j][j] = %lf\n", (*matr)[ii][jj], (*matr)[ii][ii], (*matr)[jj][jj]);
		turn(g, gt, matr);
		multiply (vector, g, vector);
		multiply (gt, matr, matr);
		multiply (matr, g, matr);
		printf("A = \n");
		for (i=0; i<size; i++)
		{
			for (j=0; j<size; j++)
			{
				printf("%lf ", (*matr)[i][j]);
			}
			printf("\n");
		}
		count++;
	}
	printf("\n");
	printf("Матрица собственных векторов: \n");
	for (i=0; i<size; i++)
	{
		for (j=0; j<size; j++)
		{
			printf("%lf ", (*vector)[i][j]);
		}
		printf("\n");
	}
	printf("Количество итераций при точности %e: %i\n", eps, count);
	printf("Вектор собственных чисел: \n");
	printf("{ ");
	for (i=0; i<size; i++) printf("%lf ", (*matr)[i][i]);
	printf("}\n");
}
void main()
{
	char str1[] = "matrixtest.txt";
	setlocale(LC_ALL, "rus");
	readA(&matr, str1);
	vectorfill(&vector);
	solve(&matr, &G, &Gt, &vector);
	nevyazka(&matr, &vector, str1);
}