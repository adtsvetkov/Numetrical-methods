#include "Matrix.h"

#define ERROR -1

Matrix& Matrix::operator +=(Matrix& A)
{
	if (A.heigth == heigth && A.length == length)
	{
		unsigned size = heigth * length;

		for (unsigned i = 0U; i < size; ++i)
			p[i] += A.p[i];
	}
	else
		throw ERROR;

	return *this;
}

Matrix& Matrix::operator +(Matrix& A)
{
	Matrix* res = new Matrix(*this);

	if (A.heigth == heigth && A.length == length)
	{
		(*res) += A;
	}
	else
		throw ERROR;

	return *res;
}

Matrix& Matrix::operator -=(Matrix& A)
{
	if (A.heigth == heigth && A.length == length)
	{
		unsigned size = heigth * length;

		for (unsigned i = 0U; i < size; ++i)
			p[i] -= A.p[i];
	}
	else
		throw ERROR;

	return *this;
}

Matrix& Matrix::operator -(Matrix & A)
{
	Matrix* res = new Matrix(*this);

	if (A.heigth == heigth && A.length == length)
	{
		(*res) -= A;
	}
	else
		throw ERROR;

	return *res;
}

Matrix& Matrix::operator *=(Matrix& A)
{
	if (A.heigth == length)
	{
		Matrix* res = new Matrix(heigth, A.length);

		for (unsigned i = 0U; i < heigth; ++i)
		{
			for (unsigned j = 0U; j < A.length; ++j)
			{
				long double a = 0.0L;
				
				for (unsigned k = 0U; k < length; ++k)
					a += pos(i, k) * A.pos(k, j);

				res->p[i * A.length + j] = a;
			}
		}

		this->~Matrix();

		*this = *res;
	}
	else
		throw ERROR;

	return *this;
}

Matrix& Matrix::operator *(Matrix& A)
{
	Matrix* res = new Matrix(*this);

	if (A.heigth == length)
	{
		(*res) *= A;
	}
	else
		throw ERROR;

	return *res;
}

Matrix::Matrix(unsigned dim)
{
	if (dim)
	{
		this->heigth = dim;
		this->length = dim;

		unsigned size = dim * dim;

		try
		{
			p = new long double[size];
		}
		catch (...)
		{
			throw ERROR;
		}

		for (unsigned i = 0U; i < size; ++i)
			p[i] = 0.0L;
	}
	else
		throw ERROR;
}

Matrix::Matrix(unsigned heigth, unsigned length)
{
	if (heigth && length)
	{
		this->heigth = heigth;
		this->length = length;

		unsigned size = heigth * length;

		this->p = new long double[size];

		for (unsigned i = 0U; i < size; ++i)
			p[i] = 0.0L;
	}
	else
		throw ERROR;
}

Matrix::Matrix(unsigned heigth, unsigned length, long double* p)
{
	this->heigth = heigth;
	this->length = length;
	this->p = p;
}

Matrix::Matrix(Matrix& A)
{
	unsigned size = A.length * A.heigth;

	heigth = A.heigth;
	length = A.length;
	p = new long double[size];

	memcpy(p, A.p, size * sizeof(long double));
}

static Matrix* CreateE(unsigned n)
{
	Matrix* E = new Matrix(n, n);

	long double* a = E->GetPtr();

	for (unsigned i = 0U, pos; i < n; ++i)
	{
		pos = i * n + i;
		a[pos] = 1.0L;
	}

	return E;
}

Matrix* Inverse(Matrix& src)
{
	unsigned n = src.GetHeigth();
	Matrix A(src);
	Matrix* B = CreateE(n);

	long double* a = A.GetPtr();
	long double* b = B->GetPtr();

	long double d, m;

	for (unsigned i = 0U, pos; i < n; ++i)
	{
		pos = i * n + i;

		d = A.pos(i, i);
		a[pos] = 1.0L;

		for (unsigned j = 0U; j <= i; ++j)
			b[i * n + j] /= d;

		for (unsigned j = i + 1U; j < n; ++j)
			a[i * n + j] /= d;

		for (unsigned k = i + 1U, j; k < n; ++k)
		{
			m = A.pos(k, i);

			for (j = 0U; j <= i; ++j)
				b[k * n + j] -= m * B->pos(i, j);

			a[k * n + j - 1U] = 0.0L;

			for (; j < n; ++j)
				a[k * n + j] -= m * A.pos(i, j);
		}
	}

	for (int i = n - 1; i > 0; --i)
	{
		for (int k = i - 1; k >= 0; --k)
		{
			m = A.pos(k, i);

			for (int j = n - 1; j >= 0; --j)
				b[k * n + j] -= m * B->pos(i, j);

			a[k * n + i] = 0U;
		}
	}
	return B;
}

Matrix* Transport(Matrix& src)
{
	unsigned h = src.GetHeigth();
	unsigned l = src.GetLength();
	Matrix* B = new Matrix(l, h);

	long double* b = B->GetPtr();

	for (unsigned i = 0; i < l; ++i)
	{
		for (unsigned j = 0; j < h; ++j)
		{
			b[i * h + j] = src.pos(j, i);
		}
	}
	return B;
}

long double Matrix::pos(unsigned i, unsigned j)
{
	return p[i * length + j];
}

void Matrix::PrintMatrix()
{
	for (unsigned i = 0U; i < heigth; ++i)
	{
		for (unsigned j = 0U; j < length; ++j)
		{
 			std::cout << pos(i, j) << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
