#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "stdio.h"
#include <string>
#include "math.h"
#include "make_points.h"

// ___________________________________________
/*			  DEF FUNCTION         		*/
double u(double x, double y);
double seriesOfFurierAtPoint(int NUMBER_OF_DOTS, double *MATRIX_C_nk, double var_x, double var_y);



// ___________________________________________



// ___________________________________________
/*			  MAIN CONSTANT AND FUNC    		*/

const int NUMBER_OF_DOTS = 10;
const int TEST_FOR_CONVERGE = 4;



double u(double x, double y){
    return x*x*x*x - x*x*x + y*y*y*y - y*y*y;
    // return x*x*x*x - x*x*x;
    // return 4*sin(PI * x)*sin(PI * y);
//    return 1/(1+25*x*x) - 1/26;
    // return 1 ? x < 0.5 && x > 0.4: 0;
}
// ___________________________________________


int main(){
    int i, j, l, temp;
    double hForNorm, MaxForNorm, trash;
    std::string nameFile, GNUPLOT;
    std::ofstream outFile;
    double *MATRIX_C_nk;
    double *MATRIX_OF_U;
    double *_trashMatrix;

    double *_trashMassive_1;
    double *_trashMassive_2;
    double *MASSIVE_OF_U;
    double *MASSIVE_OF_DOTS;
    // -----
    double *MASSIVE_LOGNORM;
    double *MASSIVE_LOGHIGH;

    try {
        MASSIVE_LOGNORM = new double[TEST_FOR_CONVERGE];
        MASSIVE_LOGHIGH = new double[TEST_FOR_CONVERGE];
        MATRIX_C_nk = new double[TEST_FOR_CONVERGE*(NUMBER_OF_DOTS)*(NUMBER_OF_DOTS)+1];
        MATRIX_OF_U = new double[TEST_FOR_CONVERGE*(NUMBER_OF_DOTS)*(NUMBER_OF_DOTS)+1];
        _trashMatrix = new double [TEST_FOR_CONVERGE*(NUMBER_OF_DOTS)*(NUMBER_OF_DOTS)+1];

        _trashMassive_1 = new double[TEST_FOR_CONVERGE*(NUMBER_OF_DOTS) + 1];
        _trashMassive_2 = new double[TEST_FOR_CONVERGE*(NUMBER_OF_DOTS) + 1];
        MASSIVE_OF_U = new double[TEST_FOR_CONVERGE*(NUMBER_OF_DOTS) + 1];
        MASSIVE_OF_DOTS = new double[TEST_FOR_CONVERGE*(NUMBER_OF_DOTS) + 1];

        } catch(...){
		std::cout << "Some trouble with memory" << std::endl;
		return -2;
	}

    // _________________________________________________
    // заполнение массивов для тестов
    for(i = 1; i < TEST_FOR_CONVERGE + 1; i++){
        if(makePoints((NUMBER_OF_DOTS)*i, MASSIVE_OF_DOTS) != 1){
            std::cout << "ERROR IN make_points.cpp" << std::endl;
            delete [] MASSIVE_LOGHIGH;
            delete [] MASSIVE_LOGNORM;
            delete [] MATRIX_C_nk;
            delete [] MATRIX_OF_U;
            delete [] _trashMatrix;

            delete [] MASSIVE_OF_U;
            delete [] _trashMassive_1;
            delete [] _trashMassive_2;
            delete [] MASSIVE_OF_DOTS;

            return -3;
        }


        // заполнили U
        for(l = 0; l < i*(NUMBER_OF_DOTS) + 1; l++){
            for(j = 0; j < i*(NUMBER_OF_DOTS) + 1; j++){
                // добавить проверку на краевые условия
                temp = (l*(i*(NUMBER_OF_DOTS) + 1) + j);
                if(l == i*NUMBER_OF_DOTS || j == i*NUMBER_OF_DOTS){
                    MATRIX_OF_U[temp] = 0.;
                } else {
                    MATRIX_OF_U[temp] = u(MASSIVE_OF_DOTS[l], MASSIVE_OF_DOTS[j]);
                }
            }
        }


         // найдем коэфиценты в ряде
        makeAnalysis_C_nk(NUMBER_OF_DOTS*i, MASSIVE_OF_DOTS, _trashMatrix, _trashMassive_1, _trashMassive_2, MATRIX_OF_U, MATRIX_C_nk);


        hForNorm = 1 / ((double)(NUMBER_OF_DOTS * i));
        MaxForNorm = MACHINE_EPS;
        for (double x = 0; x < 1; x += hForNorm){
            for(double y= 0; y < 1; y += hForNorm){
                trash = seriesOfFurierAtPoint(NUMBER_OF_DOTS, MATRIX_C_nk, x, y) - u(x, y);
                if (abs(trash) > MaxForNorm)
                    MaxForNorm = abs(trash);
            }

        }
        MASSIVE_LOGNORM[i - 1] = log(1 / MaxForNorm);
        MASSIVE_LOGHIGH[i - 1] = log(1 / hForNorm);

    }
    

    

   

    // _________________________________________________
    // запись в файл

    nameFile = "out.txt";
    outFile.open(nameFile.c_str());
    if(outFile.is_open()){
        for(i = 0; i < TEST_FOR_CONVERGE; i++){
            outFile << std::setprecision(15)
                    << MASSIVE_LOGHIGH[i] << " " << MASSIVE_LOGNORM[i] << std::endl;
        }
    } else {
        std::cout << "ERROR: u cant create out.txt" << std::endl;
        delete [] MASSIVE_LOGHIGH;
        delete [] MASSIVE_LOGNORM;
        delete [] MATRIX_C_nk;
        delete [] MATRIX_OF_U;
        delete [] _trashMatrix;

        delete [] MASSIVE_OF_U;
        delete [] _trashMassive_1;
        delete [] _trashMassive_2;
        delete [] MASSIVE_OF_DOTS;
        return -4;
    }
    outFile.close();
   

    // _________________________________________________
    // отрисовка данных из файлов
    nameFile = "gnu.txt";
    
    outFile.open(nameFile.c_str());
    if(outFile.is_open()){
        // outFile << "set terminal png size 1000,1000 \n" << std::endl;
        // outFile << "set output \"test.png\" \n" << std::endl;
        outFile << "plot 'out.txt' u 1:2 w linesp title 'dependence' \\" << std::endl;
    } else {
        std::cout << "ERROR: u cant create gnu.txt" << std::endl;
        delete [] MASSIVE_LOGHIGH;
        delete [] MASSIVE_LOGNORM;
        delete [] MATRIX_C_nk;
        delete [] MATRIX_OF_U;
        delete [] _trashMatrix;

        delete [] MASSIVE_OF_U;
        delete [] _trashMassive_1;
        delete [] _trashMassive_2;
        delete [] MASSIVE_OF_DOTS;
        return -5;
    }
    outFile.close();

    GNUPLOT = "gnuplot -persist \"" + nameFile + "\"";
    FILE *pipe = popen(GNUPLOT.c_str() , "w");

    if (pipe != NULL){
        fflush(pipe);
        pclose(pipe);
    } else {
        std::cout << "ERROR: u have fail in terminal" << std::endl;
        delete [] MASSIVE_LOGHIGH;
        delete [] MASSIVE_LOGNORM;
        delete [] MATRIX_C_nk;
        delete [] MATRIX_OF_U;
        delete [] _trashMatrix;

        delete [] MASSIVE_OF_U;
        delete [] _trashMassive_1;
        delete [] _trashMassive_2;
        delete [] MASSIVE_OF_DOTS;
        return -6;
    }

    for(i = 1; i < TEST_FOR_CONVERGE; i++){
        if(abs(MASSIVE_LOGHIGH[i - 1] - MASSIVE_LOGHIGH[i]) < MACHINE_EPS){
            std::cout << "ERROR: u have zero value at log" << std::endl;
            delete [] MASSIVE_LOGHIGH;
            delete [] MASSIVE_LOGNORM;
            delete [] MATRIX_C_nk;
            delete [] MATRIX_OF_U;
            delete [] _trashMatrix;

            delete [] MASSIVE_OF_U;
            delete [] _trashMassive_1;
            delete [] _trashMassive_2;
            delete [] MASSIVE_OF_DOTS;
            return -7;
        } 
    }
    trash = 0;
    for(i = 1; i < TEST_FOR_CONVERGE; i+=2){
        trash += 0.5 * ((MASSIVE_LOGNORM[i] - MASSIVE_LOGNORM[i - 1]) / (MASSIVE_LOGHIGH[i] - MASSIVE_LOGHIGH[i - 1]));
    }

    std::cout << trash << std::endl;


    // ____________________________________________


    delete [] MASSIVE_LOGHIGH;
    delete [] MASSIVE_LOGNORM;
    delete [] MATRIX_C_nk;
    delete [] MATRIX_OF_U;
    delete [] _trashMatrix;

    delete [] MASSIVE_OF_U;
    delete [] _trashMassive_1;
    delete [] _trashMassive_2;
    delete [] MASSIVE_OF_DOTS;
    

    return 1;
}




// ____________________________________________

double seriesOfFurierAtPoint(int N, double *koef, double var_x, double var_y){
    double result = 0;
    int i, j;
    for(i = 1; i < N; i++){
        for(j = 1; j < N; j++){
            result += koef[i*(N+1) + j] * cos(PI * (i - (double)1./2.) * var_x) * cos(PI * (j - (double)1./2.) * var_y);
        }
    }
    return result;
}






































