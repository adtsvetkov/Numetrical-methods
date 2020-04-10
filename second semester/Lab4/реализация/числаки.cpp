#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define fact -logl(2)+(1/4.0)
#define constant (2*sqrt(3))
#pragma warning (disable:4996)
using namespace std;
long double f(long double x)
{
	return (pow(x, 3) - 1 / (2 - x));
}
int t;
long double calc(long double x1, long double x2)
{
	t++;
	long double par1 = (x1 + x2) / 2.0;
	long double par2 = (x2 - x1) / constant;
	return (x2 - x1)*(f(par1 + par2) + f(par1 - par2)) / 2;

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
		k *= 2;
	} while (fabs(s2 - s1) > e);
}
void main()
{
	FILE *f;
	long double e = pow(10, -1);
	f = fopen("file.csv", "w");
	for (int i = 0; i < 13; i++)
	{
		fprintf(f, "%e;", e);
		e *= 0.1;
	}
	fprintf(f, "\n");
	e = pow(10, -1);
	for (int i = 0; i < 13; i++)
	{
		s1 = 0;
		s2 = 0;
		k = 1;
		t = 0;
		sum(0, 1, e);
		fprintf(f, "%e;", fabs(fact-s2));
		e *= 0.1;
	}
	fprintf(f, "\n");
	e = pow(10, -1);
	for (int i = 0; i < 13; i++)
	{
		s1 = 0;
		s2 = 0;
		k = 1;
		t = 0;
		sum(0, 1, e);
		fprintf(f, "%i;", k);
		e *= 0.1;
	}
	fprintf(f, "\n");
	e = pow(10, -1);
	for (int i = 0; i < 13; i++)
	{
		s1 = 0;
		s2 = 0;
		k = 1;
		t = 0;
		sum(0, 1, e);
		fprintf(f, "%i;", t);
		e *= 0.1;
	}
	printf("%e\n", fact - s2);
	printf("%i\n", t);
	printf("%i\n", k);
	fclose(f);
}