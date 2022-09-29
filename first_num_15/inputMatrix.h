#ifndef _MATRIX_OPETRATION
#define _MATRIX_OPETRATION
#define EPS 1e-99


#include <iostream>
#include <fstream>
#include <cmath>

double makeEPS();
double _Max(double a, double b);
double _Module(double a, double b);
int multiMatrixOnVector(double *matrix, double *vector, double *memoryForResult, int len);     // multiply matrix on column
int createColumnB(double *matrix, double *memoryForB, int len);                                // creare column from matrix in addition formule
double checkAccurancy(double *A, double *vector, double *B, int len);                          // residual norm
int createMatrixFromFile(char *fileName, double *memoryForElem, int len);                      // create matrix in form
int createMatrixWithoutFile(double *matrix, int len, int option);                              // create matrix without file
int printObject(double *matrix, int len, int endOfOutput, int mode);                                     // output of matrix


#endif