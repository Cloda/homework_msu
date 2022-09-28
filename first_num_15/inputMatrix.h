#ifndef _MATRIX_OPETRATION
#define _MATRIX_OPETRATION

#include <iostream>
#include <fstream>

double makeEPS();
double checkAccurancy(); // residual norm
double _Max(double, double);
double _Module(double, double);
int multiMatrixOnVector(double *, double *, double *, int);  // multiply matrix on column
int createColumnB(double *, double *, int); // creare column from matrix in addition formule
int createMatrixFromFile(char *, double *, int); // create matrix in form
int createMatrixWithoutFile(double *, int, int); // create matrix without file
int printMatrix(double *, int, int); // output of matrix


#endif