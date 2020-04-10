//#include <iostream>
#include <fstream>
using namespace std;

#include "Matrix.h"
#include "Spline.h"

#define NUM 5
#define WEIGHT 1L

#define X0_F1 0.4L
#define X0_F2 -2.0L
#define XN 2.0L
#define FILE_NAME_1 "grid_1.txt"
#define FILE_NAME_2 "grid_2.txt"
#define FILE_NAME_3 "grid_3.txt"
#define FILE_NAME_4 "grid_4.txt"
#define FILE_NAME_5 "grid_5_5.txt"
#define FILE_NAME_6 "grid_6_6.txt"
#define FILE_NAME_7 "grid_7_7.txt"
#define FILE_NAME_8 "grid_8_8.txt"

int main(void)
{
	long double a = X0_F2, b = XN;
	//int n[] = { 5, 6, 8, 10 };
	int n[] = { 5, 10, 25, 50, 100, 150, 250, 400 };
	long double w[] = { 100, 100, 100, 100, 100, 100, 100, 100 };
	//long double w[] = { 1, 1, 1, 1 };
	const char* file[] = { FILE_NAME_1, FILE_NAME_2, FILE_NAME_3, FILE_NAME_4, FILE_NAME_5, FILE_NAME_6, FILE_NAME_7, FILE_NAME_8 };
	
	cout.precision(10);
	for (int i = 0; i < 1; ++i)
	{
		ofstream fout(file[i]);
		long double h = (b - a) / (n[i]+1.0L);
		long double error = 0;
		/*for (int l = 0; l <= n[i]; l++)
		{
			long double x1 = a + h*l;
			long double x2 = a + h*(l+1);*/
			grid_t* grid = FillGrid(n[i], X0_F2, XN, w[i]);
			coeff_t coeff = SmoothingSpline(grid);
			res_t res = G(&coeff, X0_F2, XN, n[i]);
			for (int j = 0; j < res.n; ++j)
			{
				fout << res.x[j] << ' ';
				fout << res.y[j] << endl;
			}
			if (res.error > error) error = res.error;
			cout << "Error " << n[i] << ": ";
			cout << error << endl;
		//}
	}
	system("pause");
	return 0;
}
