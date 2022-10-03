#include "inputMatrix.h"

double makeEPS(){
    double e = 1;
    int n = 0;
	while(0 < 0 + e){ e /= 2; n++; }
	e = 1;
	for(; n > 1; n--){ e /= 2; }
    return e;
}

double _Max(double a, double b, double e){
    return (a - b >= e) ? a : b;
}

double _Module(double a, double b, double e){
    return (a - b >= e) ? a - b : b - a;
}

int multiMatrixOnVector(double *matrix, double *vector, double *result, int len){
    int i = 0, j = 0;
    for(i = 0; i < len; i++){
        result[i] = 0;
        for(j = 0; j < len; j++){
            result[i] += matrix[i*len + j] * vector[i];
        }
    }
    return 1;
}

int createColumnB(double *matrixForB, double *B, int len){
    int i = 0, j = 0;
    for(i = 0; i < len; i++){
        B[i] = 0;
        for(j = 0; j < len; j += 2){
            B[i] += matrixForB[i*len + j];
        }
    }
    return 1;
}

double checkAccurancy(double *matrix, double *vector, double *B, int len){
    int i;
	double result = 0., *matrix_ON_vector;

    try{
        matrix_ON_vector = new double[len];
    } catch(...){
        std::cout << "Matrix error: u haven't enough memory" << std::endl;
        return -10;
    }
    
    multiMatrixOnVector(matrix, vector, matrix_ON_vector, len);

    for(i = 0; i < len; i++){
		result += matrix_ON_vector[i] * matrix_ON_vector[i] - B[i]; 
	}

    delete [] matrix_ON_vector;
	return sqrt(result);
}

int createMatrixWithoutFile(double *mainMas, int n, int k){
    double MACHINE_EPS = makeEPS();
    int i, j, l; // i - column, j - row
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(k == 1){
                mainMas[i*n + j] = n - _Max(l, j, MACHINE_EPS) + 1;
                continue;
            }
            if(k == 2){
                mainMas[i*n + j] = _Max(l, j, MACHINE_EPS);
                continue;
            }
            if(k == 3){
                mainMas[i*n + j] = _Module(l, j, MACHINE_EPS);
                continue;
            }
            if(k == 4){
                // что делать с делением на ноль!!!!!!!!!!!!
                mainMas[i*n + j] = 1./(l + j - 1);
            }
            else {
                std::cout << "Matrix error: u enter k > 4" << std::endl;
                return -1;
            }
        }
    }

    return 1;
}

int createMatrixFromFile(char *nameFile, double *mainMas, int n){
    std::ifstream fp(nameFile);
	int lenOfMas = n * n;
    int i;
    double trash;

    // dont exict file
    if(!fp.is_open()){
        std::cout << "Matrix error: your file is broken" << std::endl;
        return -1;
    }    
    
    while(fp >> trash){ i++; }

    // not the end of file 
    if(!fp.eof()){
        // type incorret 
        if(fp.fail()){
            std::cout << "Matrix error: type incorrect" << std::endl;
            fp.close();
            return -2;
        }
        std::cout << "Matrix error: some fall" << std::endl;
        fp.close();
        return -3;
    }   

    if(i != lenOfMas){
        std::cout << "Matrix error: not enough elements" << std::endl;
        fp.close();
        return -4;
    }

    try{
        fp.clear();
        fp.seekg(0);
    } catch(...){
		fp.close();
        std::cout << "Matrix error: incorrect operation in change of cursor" << std::endl;
        return -5;
    }    

    for(i = 0; i < lenOfMas; i++){
        fp >> mainMas[i];
    }
	
	fp.close();
    return 1;
}

int printObject(double *mainMas, int n, int m, int mode){
    int i, len;
    
    if(m < 0){
        std::cout << "Matrix error: u enter m < 0" << std::endl;
        return -1;
    }

    if(n > m && m >= 0){
        n = m;
    }

    if(mode){
        len = n;
    } else {
        len = n*n;
    }
    
    std::cout << "(";
    for(i = 0; i < len; i++){
        if(i % n == 0 && i != 0 && i != n * n - 1){
            std::cout << ")" << std::endl << "(";
        }
        printf("%10.3e", mainMas[i]);
    }
    std::cout << ")" << std::endl;

    return 1;
}