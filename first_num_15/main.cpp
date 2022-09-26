#include "inputMatrix.h"
#include <iostream>
#include <fstream>

int MethodJordan();

int MethodJordan(){
    return 1;
}


int main(int argc, char *argv[]){
	/*variable 
		n - dim of matrix
		m - num of output row and column
		k - option of input matrix(0 - from file)
		filename - file name which consist matrix
		mainMassive - main massive with matrix
	*/
	int n, m, k;
	char *filename;
	double *mainMassive; 

	try {
		n = atoi(argv[1]);
		m = atoi(argv[2]);
		k = atoi(argv[3]);
	} catch(...){
		std::cout << "your input incorrect, pls try again" << std::endl;
		return -1;
	}

	try {
		mainMassive = new double[n * n];
	} catch(...){
		std::cout << "some trouble with memory" << std::endl;
		return -2;
	}

	if(k == 0){
		try {
			filename = argv[4];
		} catch(...){
			std::cout << "your name of file incorrect, pls try again" << std::endl;
			return -3;
		}
		if(createMatrixFromFile(filename, mainMassive, n) != 1){
			delete [] mainMassive;
			return -4;
		}
	} else {
		if(createMatrixWithoutFile(mainMassive, n, k) != 1){
			delete [] mainMassive;
			return -5;
		}
	}

	if(printMatrix(mainMassive, n, m) != 1){
		delete [] mainMassive;
		return -6;
	}


	delete [] mainMassive;
	return 1;
}