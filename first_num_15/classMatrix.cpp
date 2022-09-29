#include "classMatrix.h"

int Matrix::printMatrix(int sizeToPrint){
    if(_isMemory){
        int i, len = _size;
    
        if(sizeToPrint < 0){
            std::cout << "Matrix error: u enter m < 0" << std::endl;
            return -1;
        }

        if(_size > sizeToPrint){
            len = sizeToPrint;
        }

        std::cout << "(";
        for(i = 0; i < len * len; i++){
            if(i % _size == 0 && i != 0 && i != _sizeInSquare - 1){
                std::cout << ")" << std::endl << "(";
            }
            printf("%10.3e", _matrix[i]);
        }
        std::cout << ")" << std::endl;
    }

    return 1;
}

int Matrix::copyMatrixInMassive(double *to){
    int i;
    for(i = 0; i < _sizeInSquare; i++){
        try{
            to[i] = _matrix[i];
        } catch(...) {
            std::cout << "Matrix errors: fail in your massive" << std::endl;
        }
    }
}

double Matrix::makeEPS(){
    double e = 1;
    int n = 0;
	while(0 < 0 + e){ e /= 2; n++; }
	e = 1;
	for(; n > 1; n--){ e /= 2; }
    return e;
}

double Matrix::_Max(double a, double b){
    return (a - b >= MACHINE_EPS) ? a : b;
}

double Matrix::_Module(double a, double b){
    return (a - b >= MACHINE_EPS) ? a - b : b - a;
}

Matrix::Matrix(int size){
    MACHINE_EPS = makeEPS();
    _size = size;
    _sizeInSquare = _size * _size;
    if(size){
        try{
		    _matrix = new double[_sizeInSquare];
            _isMemory = 1;
	    } catch(...){
		    std::cout << "Matrix errors: some trouble with memory" << std::endl;
            _isMemory = 0;
	    }
    } else {
        _isMemory = 0;
        std::cout << "Matrix message: u make empty matrix" << std::endl;
    }
    _isEmpty = 0;
}

int Matrix::makeMatrixWithFormule(int modeGenerate){
    if(_isMemory){
        if(!_isEmpty){
            int i, j; // i - column, j - row

            for(i = 0; i < _size; i++){
                for(j = 0; j < _size; j++){
                    if(modeGenerate == 1){
                        _matrix[i*_size + j] = _size - _Max(i + 1, j + 1) + 1;
                        continue;
                    }
                    if(modeGenerate == 2){
                        _matrix[i*_size + j] = _Max(i + 1, j + 1);
                        continue;
                    }
                    if(modeGenerate == 3){
                        _matrix[i*_size + j] = _Module(i + 1, j + 1);
                        continue;
                    }
                    if(modeGenerate == 4){
                        _matrix[i*_size + j] = 1./(i + j + 1);
                        continue;
                    }
                    else {
                        std::cout << "Matrix message: u enter option k > 4" << std::endl;
                        _isEmpty = 0;
                        return -1;
                    }
                }
            }

            _isEmpty = 1;
        } else {
            std::cout << "Matrix message: u have a full matrix^ pls make new object" << std::endl;
        }
    }

    return 1;
}

int Matrix::makeMatrixWithFile(char *nameFile){
    if(_isMemory){
        if(!_isEmpty){
            std::ifstream fp(nameFile);
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

            if(i != _sizeInSquare){
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

            _isEmpty = 1;
            for(i = 0; i < _sizeInSquare; i++){
                fp >> _matrix[i];
            }
            
            fp.close();
        } else {
            std::cout << "Matrix message: u have a full matrix^ pls make new object" << std::endl;
        }
    }

    return 1;
}

Matrix::Matrix(const Matrix &a){
	int i;
	_size = a._size;
    _sizeInSquare = a._sizeInSquare;
    if(_size){
        try{
		    _matrix = new double[_sizeInSquare];
	    } catch(...){
		    std::cout << "Matrix errors: some trouble with memory in copy" << std::endl;
            _isMemory = 0;
            _isEmpty = 0;
	    }
    } else {
        _isMemory = 0;
        _isEmpty = 0;
        std::cout << "Matrix message: u make empty matrix in copy" << std::endl;
    }
	
	for(i = 0; i < _sizeInSquare; i++){
		_matrix[i] = a._matrix[i];
	}

    _isMemory = 1;
    _isEmpty = 1;
}

const Matrix & Matrix::operator=(const Matrix &a){
	int i;
	_size = a._size;
    _sizeInSquare = a._sizeInSquare;
    if(_size){
        try{
		    _matrix = new double[_sizeInSquare];
	    } catch(...){
		    std::cout << "Matrix errors: some trouble with memory in =" << std::endl;
            _isMemory = 0;
            _isEmpty = 0;
	    }
    } else {
        _isMemory = 0;
        _isEmpty = 0;
        std::cout << "Matrix message: u make empty matrix in =" << std::endl;
    }
	
	for(i = 0; i < _sizeInSquare; i++){
		_matrix[i] = a._matrix[i];
	}

    _isMemory = 1;
    _isEmpty = 1;
}