#include "inputMatrix.h"
#include "_algorithm.h"
#include <iostream>
#include <fstream>
#include <time.h>

int MethodJordan();

int MethodJordan(){
    return 1;
}


int main(int argc, char *argv[]){
	/* variable 
		n - dim of matrix
		m - num of output row and column
		k - option of input matrix(0 - from file)
		filename - file name which consist matrix
		mainMassive - main massive with matrix
	*/
	int n, m, k, i, errorInAlg;
	char *filename;
	double *mainMassive, *massiveB, *massiveX;
	clock_t t;

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
		massiveX = new double[n];
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
			delete [] massiveB;
			delete [] massiveX;
			return -4;
		}
	} else {
		if(createMatrixWithoutFile(mainMassive, n, k) != 1){
			delete [] mainMassive;
			delete [] massiveB;
			return -5;
		}
	}

// _________________________________________
/*			  PRINT MATRIX				*/
	std::cout << "MATRIX" << std::endl;
	if(printObject(mainMassive, n, m, 0) != 1){
		delete [] massiveB;
		delete [] mainMassive;
		delete [] massiveX;
		return -6;
	}
	std::cout << std::endl;
	
	createColumnB(mainMassive, massiveB, n);

/*_________________________________________________*/
	t = clock();
	// main function 
	errorInAlg = findSolutionWithJordan(mainMassive, massiveX, massiveB, n);
	// main function
	t = clock() - t;

	if(errorInAlg != 1){
		std::cout << "u have singular matrix" << std::endl;
		delete [] mainMassive;
		delete [] massiveB;
		delete [] massiveX;
		return -11;
	}
	
	printObject(massiveX, n, m, 1);
	std::cout << "Time score: " << t << std::endl;



/*_________________________________________________*/

// _________________________________________
/*			  PRINT ACCURACY				*/

	std::cout << checkAccurancy(mainMassive, massiveX, massiveB, n) << std::endl;

	delete [] mainMassive;
	delete [] massiveB;
	delete [] massiveX;
	return 1;
}