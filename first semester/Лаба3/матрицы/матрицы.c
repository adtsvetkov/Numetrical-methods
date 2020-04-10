#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#pragma warning (disable: 4996)
double **matrnew, **matr1new;
double *bnew, *b1new;
double **alpha, **alpha1;
double *beta, *beta1;
double max;
int size;
double eps = 0.000001;
double normir (double **x)
{
	int i, j;
	double max, s;
	max = 0;
	for (i = 0; i < size; i++) 
	{
		s = 0;
		for (j=0; j<1; j++)
		{
			if (((*x)[i])<0) s-=(*x)[i];
			else s += (*x)[i];
		}
		if (s > max)
			max = s;
	}
	return max;
}
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
	for (i=0; i<size; i++)
	{
		if (max < C[i] - (*b)[i]) max = C[i] - (*b)[i];
	}
}
void readB (double **bnew, char *string)
{
	FILE *f;
	int i;
	*bnew = (double *) malloc (sizeof(double)*size);
	f = fopen(string, "r");
	printf("Вектор b: \n");
	for (i=0; i<size; i++)
	{
		fscanf(f, "%lf", &(*bnew)[i]);
		printf("%lf\n", (*bnew)[i]);
	}
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
void readA (double ***matrnew, char *string)
{
	FILE *f;
	int i, j;
	double cond, determinant;
	f = fopen(string, "r");
	fscanf(f, "%i", &size);
	*matrnew = (double **) malloc(sizeof(double *)*size);
	for (i=0; i<size; i++)
	{
		(*matrnew)[i] = (double *) malloc(sizeof(double)*size);
	}
	printf("Матрица А: \n");
	for (i=0; i<size; i++)
	{
		for (j=0; j<size; j++)
		{
			fscanf(f, "%lf", &(*matrnew)[i][j]);
			printf("%lf ", (*matrnew)[i][j]);
		}
		printf("\n");
	}
	fscanf(f, "%lf", &cond);
	printf("cond(A) = %lf\n", cond);
	fscanf(f, "%lf", &determinant);
	printf("det = %lf\n", determinant);
	fclose(f);
}
void alphabeta (double ***matrnew, double **bnew, double ***alpha, double **beta)
{
	int i, j;
	*beta = (double *) malloc (sizeof(double)*size);
	*alpha = (double **) malloc(sizeof(double *)*size);
	for (i=0; i<size; i++)
	{
		(*alpha)[i] = (double *) malloc(sizeof(double)*size);
	}
	for (i=0; i<size; i++)
	{
		for (j=0; j<size; j++)
		{
			if (i!=j) (*alpha)[i][j] = -((*matrnew)[i][j]/(*matrnew)[i][i]);
			else (*alpha)[i][j] = 0;
		}
	}
	for (i=0; i<size; i++)
	{
		(*beta)[i] = (*bnew)[i]/(*matrnew)[i][i];
	}
	printf("Матрица альфа: \n");
	for (i=0; i<size; i++)
	{
		for (j=0; j<size; j++)
		{
			printf("%lf ", (*alpha)[i][j]);
		}
		printf("\n");
	}
	printf("Столбец бета: \n");
	for (i=0; i<size; i++)
	{
		printf("%lf\n", (*beta)[i]);
	}
}
void solve (double **beta, double ***alpha, double ***matrnew, double **bnew)
{
	double *x, *xfirst, *xsub;
	int i, j;
	int count=0;
	x = (double *) malloc(sizeof(double)*size);
	xfirst = (double *) malloc(sizeof(double)*size);
	xsub = (double *) malloc (sizeof(double)*size);
	for (i=0; i<size; i++)
	{
		xfirst[i] = (*beta)[i];
		xsub[i] = (*beta)[i];
	}
	while(normir(&xsub) > eps)
	{
		for (i=0; i<size; i++) x[i] = 0;
		for (i=0; i<size; i++)
		{
			for (j=0; j<i; j++)
			{
				x[i] += (*alpha)[i][j]*x[j];
			}
			for (j=i; j<size; j++)
			{
				x[i] += (*alpha)[i][j]*xfirst[j];
			}
			x[i] +=(*beta)[i];
		}
		count++;
		for (i=0; i<size; i++)
		{
			xsub[i] = x[i]-xfirst[i];
			xfirst[i] = x[i];
		}
	}
	//printf("norm %e\n", normir(&xsub));
	nevyazka(matrnew, &xfirst, bnew);
	printf("Вектор невязки: %e\n", max); 
	printf("Количество итераций при точности %lf: %i\n", eps, count);
	printf("Столбец решений: \n");
	for (i=0; i<size; i++) printf("%lf\n", x[i]);
}
void main()
{
	char str1[] = "matrixtest.txt";
	char str2[] = "vectortest.txt";
	setlocale(LC_ALL, "rus");
	printf("Для тестовой матрицы 3х3: \n");
	readA(&matr1new, str1);
	readB(&b1new, str2);
	alphabeta(&matr1new, &b1new, &alpha1, &beta1);
	solve(&beta1, &alpha1, &matr1new, &b1new);
}