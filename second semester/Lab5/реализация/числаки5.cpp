#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define start 1
#pragma warning (disable:4996)
using namespace std;
long double fact(long double x)
{
	return (sin(x) + cos(x));
}
long double f(long double x, long double y)
{
	return ((1/cos(x))-y*(sin(x))/(cos(x)));
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
long double sum(long double e, long double a, long double b, long double y) //возвращает значение для точки с заданной точностью
{
	long double y0_1, y0_2, y1, y2;
	do
	{
		y0_1 = y;
		y0_2 = y;
		long double h = (b - a) / k;
		for (int i = 0; i < k; i++)
		{
			y1 = calc(a + i*h, y0_1, h);
			y0_1 = y1;
		}
		for (int j = 0; j < 2 * k; j++)
		{
			y2 = calc(a + (j*h) / 2, y0_2, h / 2);
			y0_2 = y2;
		}
		k*=2;
	} while (fabs((y1 - y2))/3 > e);
	k = 1;
	return y2;
}
void koshi(long double e, long double a, long double b, long double h, long double y_start, FILE *f)
{
	long double y0 = y_start;
	long double y1;
	long double y;
	long double max;
	for (int i = 0; i < (b - a) / h; i++)
	{
		long double x1 = a + i*h;
		long double x2 = a + (i + 1)*h;
		y1 = sum(e, a, b, y0);
		y = fact(b);
		max = fabs(y - y1);
		if (max < fabs(y - y1)) max = fabs(y - y1);
	}
	printf("%e\n", max);
	//fprintf(f, "%.10f ", max);
}
/*void koshi1(long double e, long double a, long double b, long double h, long double y_start, FILE *f)
{
	hmin = ULLONG_MAX;
	hmax = 0;
	long double y0 = y_start;
	long double y1;
	yy_pogr[0] = y_start;
	//long double max=0;
	for (int i = 1; i <= (b - a) / h; i++)
	{
		y1 = sum(e, a + i*h, a + (i + 1)*h, y0);
		//if (max < fabs(fact(a + (i+1)*h) - y1)) max = fabs((fact(a + (i + 1)*h) - y1));
		y0 = y1;
		yy_pogr[i] = y1;
	}
}*/
void main()
{
	long double a = 0, b = 1.5, h = 0.1;
	long double e = 0.00000000001;
	long double l = 0.01;
	FILE *f;
	f = fopen("file6.txt", "w");
	//for (int i = 0; i < 9; i++)
	//{
		koshi(e, a, b, h, start, f);
		//e *= 0.1;
		//l *= 0.1;
	//}
	//fclose(f); 
}