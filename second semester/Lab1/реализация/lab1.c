#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma warning (disable:4996)
double *pogr;
FILE *ff;
double f(double x)
{
	return 2 * cos(x);
}
double f1(double x)
{
	return fabs(2 * cos(x));
}
void uniform(double **x, int size, double a, double b)
{
	double N = (b - a) / size;
	*x = (double *)malloc((size + 1) * sizeof(double));
	*x[0] = a;
	//fprintf(ff, "%e\n", (*x)[0]);
	for (int i = 1; i < size + 1; i++)
	{
		(*x)[i] = a + N;
		//fprintf(ff, "%e\n", (*x)[i]);
		a += N;
	}
}
double lagrange(int size, double **x, double xx, double(*f)(double)) //полином  для конкретной точки
{
	double ans, res = 0;
	for (int j = 0; j < size + 1; j++)
	{
		ans = 1;
		for (int i = 0; i < size + 1; i++)
		{
			if ((*x)[j] != (*x)[i]) ans *= (xx - (*x)[i]) / ((*x)[j] - (*x)[i]);
		}
		res += ans*(f((*x)[j]));
	}
	return res;
}
void chebyshev(double **x, int size, double a, double b) //чебышевская сетка
{
	*x = (double *)malloc(sizeof(double)*(size + 1));
	(*x)[0] = 0;
	//fprintf(ff, "%e\n", (*x)[0]);
	for (int i = 1; i < size + 1; i++)
	{
		(*x)[i] = (0.5)*(a + b) + (0.5)*(b - a)*cos((2 * i - 1)*(M_PI) / (2 * size));
		//fprintf(ff, "%e\n", (*x)[i]);
	}
}
void random(double **x, int size, double a, double b) //произвольная сетка
{
	*x = (double *)malloc(sizeof(double)*(size + 1));
	(*x)[0] = a;
	(*x)[size] = b;
	for (int i = 1; i < size; i++)
	{
		(*x)[i] = a + (((double)rand()) / (RAND_MAX + 1)) * (b - a);
	}
	int i, j;
	double tmp;
	for (i = 1; i < size; i++)
	{
		for (j = 1; j <= size - i; j++)
		{
			if ((*x)[j] < (*x)[j - 1])
			{
				tmp = (*x)[j];
				(*x)[j] = (*x)[j - 1];
				(*x)[j - 1] = tmp;
			}
		}
	}
	for (int i = 0; i < size + 1; i++)
	{
		fprintf(ff, "%e\n", (*x)[i]);
	}
}
double eps(double **x, int size, double(*f)(double))
{
	double ans = 0;
	for (int i = 0; i < size; i++)
	{
		double newx = ((*x)[i + 1] - (*x)[i]) / 2;
		double ansf = f(newx);
		double ansl = lagrange(size, x, newx, f);
		double e = ansf - ansl;
		if (ans < fabs(e)) ans = fabs(e);
	}
	return ans;
}
void main()
{
	int size = 10; //количество узлов
	int shag = 1000; //шаг для построения
	double a = 0;
	double b = M_PI;
	//double *y;
	double ans;
	double *x;
	double *kek = (double *)malloc(sizeof(double) * (shag + 1));
	double *x1 = (double *)malloc(sizeof(double)*(size+1));
	x1[0] = 0, x1[1] = M_PI / 4, x1[2] = (3 * M_PI) / 8, x1[3] = M_PI / 2, x1[4] = (5 * M_PI) / 8, x1[5] = (3 * M_PI) / 4, x1[6] = (7 * M_PI) / 8, x1[7] = M_PI, x1[8] = (5 * M_PI) / 4, x1[9] = (7 * M_PI) / 4, x1[10] = 2*M_PI;
	ff = fopen("file10.txt", "a");
	for (size; size <= 105; size += 5)
	{
		fprintf(ff, "%i ", size);
		//chebyshev(&x, size, a, b);
		//uniform(&x, size, a, b);
		//fprintf(ff, "%e\n", eps(&x, size, f1));
	}
	//uniform(&x, size, a, b);
	//chebyshev(&x, size, a, b);
	//random(&x, size, a, b);
	/*for (int i = 0; i <= shag; i++)
	{
		kek[i] = a + ((double)i / shag)*(b - a);
		fprintf(ff, "%e\n", kek[i]);
	}
	for (int i = 0; i <= shag; i++)
	{
		ans = lagrange(size, &x, kek[i], f);
		fprintf(ff, "%e\n", ans);
	}
	fprintf(ff, "%e", eps(&x, size, f));*/
	fclose(ff);
}
