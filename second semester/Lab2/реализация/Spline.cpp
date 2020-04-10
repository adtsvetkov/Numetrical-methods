#include "Spline.h"

#define N 50
#define F f2

double f1(long double x)
{
	return x * fabsl(cos(M_PI / x));
}

double f2(long double x)
{
	return x * cos(M_PI * x);
}

static Matrix* CreateA(unsigned n, const long double* h)
{
	unsigned size = n - 2U;
	Matrix* A = new Matrix(size, size);

	long double* a = A->GetPtr();

	size *= size;

	for (unsigned i = 0U, pos; i < n - 2U; ++i)
	{
		pos = i * n - i;

		if (pos)
			a[pos - 1U] = a[pos - n + 2U];

		a[pos] = (h[i] + h[i + 1U]) / 3.0L;

		if (pos < size)
			a[pos + 1U] = h[i + 1U] / 6.0L;
	}

	return A;
}

static Matrix* CreateH(unsigned n, const long double* h)
{
	Matrix* H = new Matrix(n - 2U, n);

	long double* a = H->GetPtr();

	for (unsigned i = 0U, pos; i < n - 2U; ++i)
	{
		pos = i * n + i;

		a[pos] =  1.0L / h[i];

		a[pos + 1U] = -(h[i] + h[i + 1U]) / (h[i] * h[i + 1U]);

		a[pos + 2U] = 1.0L / h[i + 1U];
	}

	return H;
}

static Matrix* CreateP(unsigned n, const long double* p)
{
	Matrix* P = new Matrix(n, n);

	long double* a = P->GetPtr();

	for (unsigned i = 0U; i < n; ++i)
		a[i * n + i] = p[i];

	return P;
}

grid_t* FillGrid(int n, long double x0, long double xn, long double w)
{
	long double delta = (xn - x0) / (n - 1.0L);
	grid_t* grid = new grid_t;

	grid->x = new long double[n];

	grid->n = n;
	for (int i = 0; i < n; ++i)
		grid->x[i] = x0 + delta * i;

	grid->y = new long double[n];
	grid->p = new long double[n];
	grid->h = new long double[n - 1];

	for (int i = 0; i < n; ++i)
		grid->y[i] = F(grid->x[i]);

	for (int i = 0; i < n; ++i)
		grid->p[i] = w;
	
	grid->p[1] = 1000.0L;
	//grid->p[3] = 1000.0L;

	for (int i = 1; i < n; ++i)
		grid->h[i - 1] = grid->x[i] - grid->x[i - 1];

	return grid;
}

coeff_t SmoothingSpline(grid_t* grid)
{
	unsigned n = grid->n;
	long double* h = grid->h;

	Matrix Y(n, 1, grid->y);
	//Y.PrintMatrix();

	Matrix* A = CreateA(n, h);
	//A->PrintMatrix();

	Matrix* P = CreateP(n, grid->p);
	//P->PrintMatrix();

	Matrix* invP = Inverse(*P);
	//invP->PrintMatrix();

	Matrix* H = CreateH(n, h);
	//H->PrintMatrix();

	Matrix* Ht = Transport(*H);
	//Ht->PrintMatrix();

	Matrix PHt = (*invP) * (*Ht);
	//PHt.PrintMatrix();


	Matrix tmp = (*H) * PHt;
	//tmp.PrintMatrix();
	tmp += (*A);
	//tmp.PrintMatrix();

	Matrix B = (*H) * Y;
	//B.PrintMatrix();

	Matrix* M = Inverse(tmp);
	//M->PrintMatrix();

	(*M) *= B;
	//M->PrintMatrix();

	Matrix* Mu = new Matrix(PHt);
	//Mu->PrintMatrix();
	
	(*Mu) *= (*M);
	//Mu->PrintMatrix();

	(*Mu) = Y - (*Mu);
	//Mu->PrintMatrix();

	coeff_t coeff;

	coeff.M = new long double[n];
	coeff.Mu = new long double[n];

	coeff.n = n;

	coeff.M[0] = 0;
	for (unsigned i = 1; i < n - 1; ++i)
		coeff.M[i] = M->pos(0, i - 1);
	coeff.M[n - 1] = 0;

	for (unsigned i = 0; i < n; ++i)
		coeff.Mu[i] = Mu->pos(i, 0);

//	A->~Matrix();
//	P->~Matrix();
//	invP->~Matrix();
//	H->~Matrix();
//	Ht->~Matrix();

	return coeff;
}

// only for regular grid
res_t G(coeff_t* coeff, long double x0, long double xn, int n)
{
	int size = n + (n - 1) * (N - 2);
	res_t res = { size };
	
	res.x = new long double[size];
	res.y = new long double[size];
	long double h = (xn - x0) / (n - 1.0L);
	long double delta = h / (N - 1.0L);
	long double y, x, x_i;
	long double d[2];
	long double max_err = 0, err;
	int i = 1, pos = 0;


	for (; i < n; ++i)
	{
		for (int j = 0; j < N - 1; ++j, ++pos)
		{
			x_i = x0 + i * h;
			x = x_i - h + j * delta;

			d[0] = x_i - x;
			d[1] = h - d[0];

			y = d[0] * d[0] * d[0] * coeff->M[i - 1] / (6 * h);
			y += d[0] * (coeff->Mu[i - 1] - coeff->M[i - 1] * h * h / 6) / h;

			y += d[1] * d[1] * d[1] * coeff->M[i] / (6 * h);
			y += d[1] * (coeff->Mu[i] - coeff->M[i] * h * h / 6) / h;

			//if (j != 0)
				//y *= -1;

			err = fabsl(y - F(x));

			if (err > max_err) { max_err = err; }

			res.x[pos] = x;
			res.y[pos] = y;
		}
	}

	--i;
	x_i = xn;
	x = xn;

	d[0] = x_i - x;
	d[1] = h - d[0];

	y = d[0] * d[0] * d[0] * coeff->M[i - 1] / (6 * h);
	y += d[0] * (coeff->Mu[i - 1] - coeff->M[i - 1] * h * h / 6) / h;
	//y += d[0] * coeff->Mu[i - 1] / h;

	y += d[1] * d[1] * d[1] * coeff->M[i] / (6 * h);
	y += d[1] * (coeff->Mu[i] - coeff->M[i] * h * h / 6) / h;
	//y += d[1] * coeff->Mu[i] / h;

	err = fabsl(y - F(x));

	if (err > max_err) { max_err = err; }

	res.x[pos] = x;
	res.y[pos] = y;

	res.error = max_err;

	return res;
}