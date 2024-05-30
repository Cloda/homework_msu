#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define UNUSED(x) (void)(x)
#define PI  3.141592653589793238462

double psi(int k, int n, int N);

double lambda_n(int n, int N, double p);

double Dn(int n, double * f, double p, int N);

void multMatrixByVector(const double *A, double *x, double *ans, int N);

double fourier_method(double * x, int N, double p, double * f);

double ErNorm(const double * A, const double * b, double * x, int N, double * mem);

void print_matrix(double * A, int N);

void print_vector(double * A, int N);