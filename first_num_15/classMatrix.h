#ifndef __CLASS_OF_MATRIX_
#define __CLASS_OF_MATRIX__

#include <iostream>
#include <fstream>
#include <cmath>


class Matrix{

    private:

        double MACHINE_EPS; 
        double *_matrix, *_vector;
        int _isMemory; // 1 - have memory
        int _isEmpty;  // 1 - have info
        int _size, _sizeInSquare;
        
        double __makeEPS();
        double __Max(double a, double b);
        double __Module(double a, double b);

        int __makeVectorFromMatrix();

    public:
        Matrix();
        Matrix(int size);
        ~Matrix();

        int makeMatrixWithFormule(int modeGenerate);
        int makeMatrixWithFile(char *nameFile);
        int copyMatrixInMassive(double *to);
        int printMatrix(int sizeToPrint);
        int printVector(int sizeToPrint);

        int findSolutionWithJordan(double *A, double *x, double *b, int n);

        int checkCalulcation(double *A, double *x, double *b, int n);

        const Matrix & operator=(const Matrix &b);
        Matrix(const Matrix &a);
};

Matrix::Matrix(){
    std::cout << "Matrix message: u make empty matrix" << std::endl;
    _isEmpty = 0;
    _isMemory = 0;
}

Matrix::~Matrix(){
    if(_isMemory){
        delete [] _matrix;
    }
}


#endif