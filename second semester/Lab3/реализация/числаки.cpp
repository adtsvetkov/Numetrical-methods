#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define fact -logl(3)
#define eps 0.0000001
#pragma warning (disable:4996)
using namespace std;
long double f(long double x)
{
	//return (pow(x, 3) - 1 / (2 - x));
	return sin(x);
}
int t;
long double calc(long double x1, long double x2)
{
	t++;
	return ((f(x1) + f(x2)) / 2)*(x2 - x1);
}
long double s1;
long double s2;
int k;
void sum(long double a, long double b, long double e)
{
	for (int i = 0; i < k; i++)
	{
		s2 += calc(a + i*(b - a) / k, a + (i + 1)*(b - a) / k);
	}
	do
	{
		s1 = s2;
		s2 = 0;
		for (int j = 0; j < 2 * k; j++)
		{
			s2 += calc(a + j*(b - a) / (2 * k), a + (j + 1)*(b - a) / (2 * k));
		}
		k*=2;
	} while (fabs((s2 - s1) / 3) > e);
}
void main()
{
	FILE *f;
	long double e=0.1;
	f = fopen("file31.txt", "w");
	printf("%.8f\n", fact);
	for (int i = 0; i < 10; i++)
	{
		fprintf(f, "%.10f ", e);
		e *= 0.1;
	}
	fprintf(f, "\n");
	e = 0.0001;
	for (int i = 0; i < 10; i++)
	{
		k = 1;
		t = 0;
		sum(0, M_PI, e);
		fprintf(f, "%i ", t);
		e *= 0.1;
	}
	fprintf(f, "\n");
	e = 0.1;
	for (int i = 0; i < 10; i++)
	{
		k = 1;
		sum(-1, 1, e);
		fprintf(f, "%i ", k/2);
		e *= 0.1;
	}
	/*for (int i = 0; i < 10; i++)
	{
		k = 1;
		sum(-1, 1, e);
		fprintf(f, "%i ", k);
		e *= 0.1;
	}*/
	/*for (int i = 0; i < 10; i++)
	{
		sum(-1, 1, e);
		fprintf(f, "%.10f ", fabs(fact - s1));
		e *= 0.1;
	}
	fprintf(f, "\n");
	e = 0.1;
	for (int i = 0; i < 10; i++)
	{
		sum(-1, 1, e);
		fprintf(f, "%.10f ", fabs(fact - s2));
		e *= 0.1;
	}
	fprintf(f, "\n");
	e = 0.1;
	for (int i = 0; i < 10; i++)
	{
		sum(-1, 1, e);
		fprintf(f, "%.10f ", fabs((s2 - s1) / 3));
		e *= 0.1;
	}
	fprintf(f, "\n");
	fclose(f);*/
	printf("%.8f\n", s2);
}