#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

#include "Matrix.h"

using coeff_t = struct
{
	int n;
	long double* M;
	long double* Mu;
};

using grid_t = struct
{
	int n;
	long double* x;
	long double* y;
	long double* p;
	long double* h;
};

using res_t = struct
{
	int n;
	long double* x;
	long double* y;
	long double error;
};

grid_t* FillGrid(int n, long double x0, long double xn, long double w);

coeff_t SmoothingSpline(grid_t* grid);

res_t G(coeff_t* coeff, long double x0, long double xn, int n);
