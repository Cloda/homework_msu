#include "inputMatrix.h"
#include <iostream>
#include <fstream>
#include <chrono>

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
	int n, m, k, i;
	char *filename;
	double *mainMassive; 
	double *massiveB;

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
		massiveB = new double[n];
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

	std::cout << "MATRIX" << std::endl;
	if(printMatrix(mainMassive, n, m) != 1){
		delete [] mainMassive;
		return -6;
	}
	std::cout << std::endl;
	
	createColumnB(mainMassive, massiveB, n);




/*
_________________________________________________
	auto begin = std::chrono::steady_clock::now();

	// main function 
	checkAccurancy();
	// main function

	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	std::cout << "The time: " << elapsed_ms.count() << " ms\n";

_________________________________________________
*/





	delete [] mainMassive;
	return 1;
}