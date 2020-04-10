#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <limits.h>
#pragma warning (disable:4996)

int N;
double *x;
double *u;
double *v;
double *zu;
double *zv;

//вариант 1
/*#define a 0.2
#define t 2.0
#define b 1.0  
double A1 = 1.0;
double A2 = 0.0;
double A3 = 6.0; //условие для точки А
double B1 = 1.0;
double B2 = 0.0;
double B3; //условие для точки В

double f(double x)
{
	return x*x*(x + 1);
}
double fact(double x)
{
	return 1 + (double)1/x;
}
double FuncP(double x)
{
	return (double)-1/f(x);
}
double FuncQ(double x)
{
	return (double) -2/f(x);
}
double FuncF(double x)
{
	return (double) 1/(x*x*f(x));
}*/

//вариант 9
#define a 0.0
#define t 1.0/M_E
#define b 1.0
double A1 = 1.0;
double A2 = 0.0;
double A3 = 1.0; //условие для точки А
double B1 = 1.0;
double B2 = 0.0;
double B3; //условие для точки В
int d = 0;
double fact(double x)
{
	return pow(M_E, -x*x);
}
double FuncP(double x)
{
	return 4*x;
}
double FuncQ(double x)
{
	return 4*x*x+3;
}
double FuncF(double x)
{
	d++;
	return pow(M_E, -x*x);
}

long double eps = 0.0000000001;

void MasX(double h)
{
	for (int i = 0; i < N; i++)
	{
		x[i] = a + i * h;
	}
}
void Progonka(double **A, double *B, double *X) //метод прогонки - решаем слау с диагональной матрицей
{
	int N1 = N - 1; //не считаем первый и последний
	double y;
	double *aa = (double *)malloc(N*(sizeof(double)));
	double *B1 = (double *)malloc(N*(sizeof(double)));

	y = A[0][0];
	aa[0] = -A[0][1] / y; //матрица коэффициентов альфа
	B1[0] = B[0] / y; //матрица коэффициентов бета - по первой формуле с studfiles
	//прямой ход
	for (int i = 1; i < N1; i++) 
	{
		y = A[i][i] + A[i][i - 1] * aa[i - 1];
		aa[i] = -A[i][i + 1] / y;
		B1[i] = (B[i] - A[i][i - 1] * B1[i - 1]) / y;
	}
	X[N1] = (B[N1] - A[N1][N1 - 1] * B1[N1 - 1]) / (A[N1][N1] + A[N1][N1 - 1] * aa[N1 - 1]);
	//обратный ход ax+b
	for (int i = N1 - 1; i >= 0; i--)
	{
		X[i] = aa[i] * X[i + 1] + B1[i];
	}
}
void FiniteDifferences(double h, FILE *f) //метод конечных разностей
{
	double max=0;
	//матрица А, вектор В, ответ У
	double **A = (double **)malloc(N * sizeof(double*));
	double *B = (double *)malloc(N * sizeof(double));
	double *Y = (double *)malloc(N * sizeof(double));
	for (int i = 0; i < N; i++)
	{
		A[i] = (double *)malloc(sizeof(double)*N);
	}
	int i, j = 0, k;
	A[0][0] = A1; //y0
	for (i = 1; i < N; i++)
		A[0][i] = 0;
	for (i = 1; i < N - 1; i++)
	{
		for (k = 0; k < j; k++)
		{
			A[i][k] = 0;
		}
		A[i][j] = 1 - FuncP(x[i])*h / 2; //заполняем по формулам со студфайлс
		A[i][j + 1] = FuncQ(x[i])*h*h - 2;
		A[i][j + 2] = 1 + FuncP(x[i])*h / 2;
		for (k = j + 3; k < N; k++)
		{
			A[i][k] = 0;
		}
		j++;
	}
	A[N - 1][N - 2] = 0;
	A[N - 1][N - 1] = B1;
	B[0] = A3;
	for (i = 1; i < N - 1; i++)
	{
		B[i] = FuncF(x[i]) * h * h;
	}
	B[N - 1] = B3;
	Progonka(A, B, Y);
	for (i = 0; i < N; i++)
	{
		if ((fabs(Y[i] - fact(x[i])) > max)) max = fabs(Y[i] - fact(x[i]));
		//printf("%lf == %lf\n", Y[i], fact(x[i]));
		//fprintf(f, "%e ", Y[i] - fact(x[i]));
	}
	//printf("%e\n", max);
	//fprintf(f, "%e;", max);
	//fprintf(f, "%e ", max);
}
double CalculateU(double X1, double X2, double U1,double Z1,int i)
{
	//double Y2, y2, h, K, y1, x1;
	double uu, zz, uuu, zzz,U,Z,u4,z4;
	int m = 1, k = 1;
	double h;
	h = X2 - X1;
	uu = u[i - 1] + h * zu[i - 1];
	zz = zu[i - 1] + h * (-FuncP(X1) * zu[i - 1] - FuncQ(X1) * u[i - 1]);
	U = u[i - 1] + h * (zu[i - 1] + zz) / 2;
	Z = zu[i - 1] + h * (-FuncP(X1) * zu[i - 1] - FuncQ(X1) * u[i - 1] - FuncP(X2) * zz - FuncQ(X2) * uu) / 2;
	while (m < 100)  
	{
		uuu = U1;
		zzz = Z1;
		k = k * 2;
		h = (X2 - X1) / k;
		for (int j = 0; j < k; j++)
		{
			uu = uuu + h * zzz;
			zz = zzz + h * (-FuncP(X1 + h * j) * zzz - FuncQ(X1 + h * j) * uuu);
			u4 = uuu + h * (zzz + zz) / 2;
			z4 = zzz + h * (-FuncP(X1 + h * j) * zzz - FuncQ(X1 + h * j) * uuu - FuncP(X1 + h * (j + 1)) * zz - FuncQ(X1 + h * (j + 1)) * uu) / 2;
			zzz = z4;
			uuu = u4;
		}
		if (fabs(U - u4) < eps)
		{
			zu[i] = z4;
			U = u4;
			printf("U:%d\n", k);
			return u4;
		}
		U = u4;
		m++;
	}
	return u4;
}
void EylerU_2(double h)
{
	int i;
	u[0] = A2;
	zu[0] = -A1;
	for (i = 1; i < N; i++)
	{
		u[i] = CalculateU(x[i - 1], x[i], u[i - 1], zu[i - 1], i);
	}
}
void EylerU(double h)
{
	int i;
	double uu, zz;
	u[0] = A2;
	zu[0] = -A1;
	for (i = 1; i < N; i++)
	{
		uu = u[i - 1] + h * zu[i - 1];
		zz = zu[i - 1] + h * (-FuncP(x[i - 1]) * zu[i - 1] - FuncQ(x[i - 1]) * u[i - 1]);
		u[i] = u[i - 1] + h * (zu[i - 1] + zz) / 2;
		zu[i] = zu[i - 1] + h * (-FuncP(x[i - 1]) * zu[i - 1] - FuncQ(x[i - 1]) * u[i - 1] - FuncP(x[i]) * zz - FuncQ(x[i]) * u[i]);
	}
}
double CalculateV(double X1, double X2, double V1, double Z1, int i)
{
//	double Y2, y2, h, K, y1, x1;
	double vv, zz, vvv, zzz, V, Z, v4, z4;
	int m = 1, k = 1;
	double h;
	h = X2 - X1;
	vv = v[i - 1] + h * zv[i - 1];
	zz = zv[i - 1] + h * (-FuncP(X1) * zv[i - 1] - FuncQ(X1) * v[i - 1] + FuncF(x[i - 1]));
	V = v[i - 1] + h * (zv[i - 1] + zz) / 2;
	Z = zv[i - 1] + h * (-FuncP(X1) * zv[i - 1] - FuncQ(X1) * v[i - 1] + FuncF(X1) - FuncP(X2) * zz - FuncQ(X2) * vv + FuncF(X2)) / 2;
	while (m < 100)
	{
		vvv = V1;
		zzz = Z1;
		k = k * 2;
		h = (X2 -    X1) / k;
		for (int j = 0; j < k; j++)
		{
			vv = vvv + h * zzz;
			zz = zzz + h * (-FuncP(X1 + h * j) * zzz - FuncQ(X1 + h * j) * vvv + FuncF(X1 + h * j));
			v4 = vvv + h * (zzz + zz) / 2;
			z4 = zzz + h * (-FuncP(X1 + h * j) * zzz - FuncQ(X1 + h * j) * vvv + FuncF(X1 + h * j) - FuncP(X1 + h * (j + 1)) * zz - FuncQ(X1 + h * (j + 1)) * vv + FuncF(X1 + h * (j + 1))) / 2;
			zzz = z4;
			vvv = v4;
		}
		if (fabs(V - v4) < eps)
		{
			zv[i] = z4;
			V = v4;
			printf("V:%d\n", k);
			return v4;
		}
		V = v4;
		m++;
	}
	return v4;
}

void EylerV_2(double h)
{
	int i;
	//double vv, zz;
	v[0] = A3 / A1;
	zv[0] = 0;
	for (i = 1; i < N; i++)
	{
		v[i] = CalculateV(x[i - 1], x[i], v[i - 1], zv[i - 1],i);
	}
}

void EylerV(double h)
{
	int i;
	double vv, zz;
	v[0] = A3 / A1;
	zv[0] = 0;
	for (i = 1; i < N; i++)
	{
		vv = v[i - 1] + h * zv[i - 1];
		zz = zv[i - 1] + h * (-FuncP(x[i - 1]) * zv[i - 1] - FuncQ(x[i - 1]) * v[i - 1] + FuncF(x[i - 1]));
		v[i] = v[i - 1] + h * (zv[i - 1] + zz) / 2;
		zv[i] = zv[i - 1] + h * (-FuncP(x[i - 1]) * zv[i - 1] - FuncQ(x[i - 1]) * v[i - 1] + FuncF(x[i - 1])\
			- FuncP(x[i]) * zz - FuncQ(x[i]) * v[i] + FuncF(x[i])) / 2;
	}
}

void Koshi(double h)
{
	double max = 0;
	double AA; //формульно коэф. С
	double *y = (double *)malloc(sizeof(double)*N); //массив для ответа 
	EylerU_2(h); //массив где находим u для каждого xi
	EylerV_2(h); //массив гденаходим v для каждого xi 
	AA = (B3 - B1 * v[N - 1] - B2 * zv[N - 1]) / (B1*u[N - 1] + B2 * zu[N - 1]);
	for (int i = 0; i < N; i++)
	{
		y[i] = AA * u[i] + v[i]; //y=cu+v
	}
	for (int i = 0; i < N; i++)
	{
		if (i!=0 && i!=N-1 && (fabs(y[i] - fact(x[i])) > max)) max = fabs(y[i] - fact(x[i]));
		//printf("%lf == %lf\n", y[i], fact(x[i]));
	}
//	fprintf(f, "%e;", max);
	printf("%e\n", max);
	//fprintf(f, "%e ", d);
}
int main(void)
{
	N = 50;
	B3 = t;
	x = (double *)malloc(N*(sizeof(double)));
	u = (double *)malloc(N*(sizeof(double)));
	v = (double *)malloc(N*(sizeof(double)));
	zu = (double *)malloc(N*(sizeof(double)));
	zv = (double *)malloc(N*(sizeof(double)));
	double h = (b - a) / (N - 1);
	//FILE *f = fopen("kek1.csv", "w");
	MasX(h);
	//for (int i = 0; i < 11; i++)
	//{
		printf("\n\neps == %e\n", eps);
		Koshi(h);
		eps *= 0.1;
	//}
	/*printf("FiniteDifferences:\n");
	FiniteDifferences(h, f);
	printf("Koshi:\n");
	Koshi(h, f);
	fprintf(f, "\n");
	double l = 0.01;
	for (int i = 0; i < 10; i++)
	{
		B3 = 1.0 / M_E;
		A3 = 1.0;
		printf("%lf%%\n\n", l * 100);
		fprintf(f, "%e;", l);
		fprintf(f, "%e;", l * 100);
		printf("a:\n");
		A3 *= (1+l);
		printf("FiniteDifferences:\n");
		FiniteDifferences(h, f);
		printf("Koshi:\n");
		Koshi(h, f);

		printf("a,b:\n");
		B3 *= 1-l;
		printf("FiniteDifferences:\n");
		FiniteDifferences(h, f);
		printf("Koshi:\n");
		Koshi(h, f);

		printf("b:\n");
		A3 = 1.0;
		printf("FiniteDifferences:\n");
		FiniteDifferences(h, f);
		printf("Koshi:\n");
		Koshi(h, f);
		l *= 0.1;
		fprintf(f, "\n");
	}*/
	return 0;
}