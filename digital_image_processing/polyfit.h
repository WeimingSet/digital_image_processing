#ifndef POLYFIT_H_
#define POLYFIT_H_


#include <iostream>  
#include <vector>  
#include <cmath>  

using namespace std;

void polyfit(int n, vector<double> x, vector<double> y, int poly_n, double a[]);
void gauss_solve(int n, double A[], double x[], double b[]);




#endif
