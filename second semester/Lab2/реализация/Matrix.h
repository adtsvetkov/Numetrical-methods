#pragma once

#include <cstring>
#include <iostream>

class Matrix
{
	unsigned heigth;
	unsigned length;
	long double* p;
public:
	Matrix(unsigned dim);
	Matrix(unsigned heigth, unsigned length);
	Matrix(unsigned heigth, unsigned length, long double* p);

	Matrix(Matrix& A);

	~Matrix() { delete[] p; };

	unsigned GetHeigth() { return heigth; };
	unsigned GetLength() { return length; };
	long double* GetPtr() { return p; };

	Matrix& operator +=(Matrix& A);
	Matrix& operator +(Matrix& A);

	Matrix& operator -=(Matrix& A);
	Matrix& operator -(Matrix& A);

	Matrix& operator *=(Matrix& A);
	Matrix& operator *(Matrix& A);

	long double pos(unsigned i, unsigned j);

	void PrintMatrix();
};

Matrix* Inverse(Matrix& src);

Matrix* Transport(Matrix& src);
