#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define start 3
#define N 2
#pragma warning (disable:4996)
using namespace std;
typedef struct kek
{
	long double y2;
	long double y3;
}kek;
long double yy[N + 1];
long double xx[N + 1];
long double p(long double e)
{
	int random;
	random = 1 + rand() % 20000;
	return e*random*0.001;
}
void masx(double h, double a, double b)
{
	for (int i = 0; i <= N; i++)
	{
		xx[i] = a + h*i;
	}
}
long double fact(long double x)
{
	return (sin(x) + cos(x));
}
long double f(long double x, long double y)
{
	return (-y + 3 * (x + 1)*(x + 1));
	//return ((1 / cos(x)) - y*(sin(x) / cos(x)));
}
long double calc(long double x, long double y, long double h)
{
	long double yy;
	long double ff;
	ff = f(x, y);
	yy = y + h*ff;
	return (y + h*(ff + f(x + h, yy)) / 2);
}
int k = 1; //количество отрезков, h - длина одного
kek RK(long double e, long double a, long double b, long double y) //возвращает значение для точки с заданной точностью
{
	kek krya;
	long double y0_1, y0_2, y1, y2, y3;
	k = 1;
	do
	{
		y0_1 = y;
		y0_2 = y;
		long double h = (b - a) / k;
		for (int i = 0; i < k; i++)
		{
			y1 = calc(a + i*h, y0_1, h);
			y1 = y0_1 + (h / 2.0)*(f(a + i*h, y0_1) + f(a + (i + 1)*h, y1));
			y0_1 = y1;
		}
		for (int j = 0; j < 2 * k; j++)
		{
			y2 = calc(a + (j*h) / 2, y0_2, h / 2);
			y3 = y2;
			y2 = y0_2 + (h / 4.0)*(f(a + j*(h/2.0), y0_2) + f(a + (j + 1)*(h/2.0), y2));
			y0_2 = y2;
		}
		k *= 2;
	} while (fabs((y1 - y2)) > e);
	krya.y2 = y2;
	krya.y3 = y3;
	return krya;
}
void adams(long double e, long double a, long double b, long double h, long double y_start, FILE *F)
{
	kek t;
	long double max = 0;
	int min = INT_MAX;
	long double y3;
	yy[0] = y_start;
	for (int n = 1; n <= N; n++)
	{
		if (k < min) min = k;
		t = RK(e, xx[n - 1], xx[n], yy[n - 1]); //по р-к находится точка
		yy[n] = t.y2;
		//yy[n] = yy[n - 1] + (h / 2.0)*(f(xx[n], yy[n]) + f(xx[n - 1], yy[n - 1]));
		long double pogr = fabs(fact(xx[n]) - yy[n]);
		if (max < pogr)
		{
			max = pogr;
			y3 = fabs(fact(xx[n]) - t.y3);
		}
	}
	//printf("K = %i ", min);
	printf("%e\n", max);
	//fprintf(F, "%e ", y3);
}
void main()
{
	long double a = 0, b = 1;
	long double e;
	long double l = 0.1;
	long double h = (b - a) / (double) N;
	FILE *f;
	f = fopen("file5.txt", "w");
	masx(h, a, b);
	e = 0.1;
	/*for (int i = 0; i < 10; i++)
	{
		fprintf(f, "%e ", l);
		l *= 0.1;
	}
	fprintf(f, "\n*/
	e = pow(10, -5);
	for (int i = 0; i < 10; i++)
	{
		adams(e, a, b, h, start, f);
		//e *= 0.1;
		l *= 0.1;
	}
	//fprintf(f, "\n");
	fclose(f);
}