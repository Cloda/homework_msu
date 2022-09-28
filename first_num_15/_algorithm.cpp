#include "_algorithm.h"


int findSolutionWithJordan(double *A, double *x, double *b, int n){
    int i, j, l, indexOfMaxInCol;
    double maxElem, trash;
    

    for(i = 0; i < n; i++){
        maxElem = A[i];
        indexOfMaxInCol = i;

        // find max in column
        for(j = i + 1; j < n; j++){
            if(maxElem < abs(A[j*n + i])){
                maxElem = A[j*n + i];
                indexOfMaxInCol = j;
            }
        }

        // check for equal to 0
        if(abs(maxElem) < EPS){
            return -1;
        }

        // renumarate index
        if(indexOfMaxInCol != i){
            for(j = 0; j < n; j++){
                trash = A[i*n + j];
                A[i*n + j] = A[indexOfMaxInCol*n + j];
                A[indexOfMaxInCol*n + j] = trash;
            }
            trash = b[i];
            b[i] = b[indexOfMaxInCol];
            b[indexOfMaxInCol] = trash;
        }
    
        for(j = i; j < n; j++){
            A[i*n + j] *= 1./A[i*n + j];
        }
        b[i] *= 1./A[i*n + j];

        for (j = 0; j < i; j++){
			trash = A[j * n + i];
			for (l = i; l < n; l++)
				A[j * n + l] -= A[i * n + l] * trash;
			b[j] -= b[i] * trash;
		}

        for (j = i + 1; j < n; j++){
			trash = A[j * n + i];
			for (l = i; l < n; l++)
				A[j * n + l] -= A[i * n + l] * trash;
			b[j] -= b[i] * trash;
		}
    }

    for(i = 0; i < n; i++){ x[i] = b[i]; }

    return 1;
}