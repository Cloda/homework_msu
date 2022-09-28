#ifndef PARALLEG_H
#define PARALLEG_H

#include <iostream>
#include <fstream>

double makeEPS();
double checkAccurancy(); // residual norm
double _Max(double, double);
double _Module(double, double);
int createMatrixFromFile(char *, double *, int); // create matrix in form
int createMatrixWithoutFile(double *, int, int); // create matrix without file
int printMatrix(double *, int, int); // output of matrix


#endif