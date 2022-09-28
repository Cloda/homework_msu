#ifndef _MATRIX_OPETRATION
#define _MATRIX_OPETRATION

#include <iostream>
#include <fstream>
#include <cmath>

double makeEPS();
double _Max(double, double);
double _Module(double, double);
int multiMatrixOnVector(double *, double *, double *, int);     // multiply matrix on column
int createColumnB(double *, double *, int);                     // creare column from matrix in addition formule
double checkAccurancy(double *, double *, double *, int);       // residual norm
int createMatrixFromFile(char *, double *, int);                // create matrix in form
int createMatrixWithoutFile(double *, int, int);                // create matrix without file
int printMatrix(double *, int, int);                            // output of matrix


#endif