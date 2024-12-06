#include "pch.h"  // 仅在使用预编译头的项目中需要
#include "polyfit.h"  // 包含 polyfit.h

#include <iostream>  
#include <vector>  
#include <cmath>  
using namespace std;


void polyfit(int n, vector <double> x, vector <double> y, int poly_n, double a[]);
void gauss_solve(int n, double A[], double x[], double b[]);

void polyfit(int n, vector <double> x, vector <double> y, int poly_n, double a[])//点数，X、Y坐标，次数，系数
{
	int i, j;
	double* tempx, * tempy, * sumxx, * sumxy, * ata;

	tempx = new double[n];
	sumxx = new double[poly_n * 2 + 1];
	tempy = new double[n];
	sumxy = new double[poly_n + 1];
	ata = new double[(poly_n + 1) * (poly_n + 1)];

	for (i = 0; i < n; i++)
	{
		tempx[i] = 1;
		tempy[i] = y[i];
	}
	for (i = 0; i < 2 * poly_n + 1; i++)
		for (sumxx[i] = 0, j = 0; j < n; j++)
		{
			sumxx[i] += tempx[j];
			tempx[j] *= x[j];
		}
	for (i = 0; i < poly_n + 1; i++)
		for (sumxy[i] = 0, j = 0; j < n; j++)
		{
			sumxy[i] += tempy[j];
			tempy[j] *= x[j];
		}
	for (i = 0; i < poly_n + 1; i++)
		for (j = 0; j < poly_n + 1; j++)
			ata[i * (poly_n + 1) + j] = sumxx[i + j];
	gauss_solve(poly_n + 1, ata, a, sumxy);

	delete[] tempx;
	tempx = NULL;
	delete[] sumxx;
	sumxx = NULL;
	delete[] tempy;
	tempy = NULL;
	delete[] sumxy;
	sumxy = NULL;
	delete[] ata;
	ata = NULL;
}

void gauss_solve(int n, double A[], double x[], double b[])
{
	int i, j, k, r;
	double max;
	for (k = 0; k < n - 1; k++)
	{
		max = fabs(A[k * n + k]); /*find maxmum*/
		r = k;
		for (i = k + 1; i < n - 1; i++)
			if (max < fabs(A[i * n + i]))
			{
				max = fabs(A[i * n + i]);
				r = i;
			}
		if (r != k)
			for (i = 0; i < n; i++) /*change array:A[k]&A[r] */
			{
				max = A[k * n + i];
				A[k * n + i] = A[r * n + i];
				A[r * n + i] = max;
			}
		max = b[k]; /*change array:b[k]&b[r] */
		b[k] = b[r];
		b[r] = max;
		for (i = k + 1; i < n; i++)
		{
			for (j = k + 1; j < n; j++)
				A[i * n + j] -= A[i * n + k] * A[k * n + j] / A[k * n + k];
			b[i] -= A[i * n + k] * b[k] / A[k * n + k];
		}
	}

	for (i = n - 1; i >= 0; x[i] /= A[i * n + i], i--)
		for (j = i + 1, x[i] = b[i]; j < n; j++)
		{
			x[i] -= A[i * n + j] * x[j];
		}

}