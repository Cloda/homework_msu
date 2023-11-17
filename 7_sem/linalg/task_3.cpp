 
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include "_lib.h"


int main(){
    double p;
    int N, i;

    double tau = 0.1;
    double eps = 1e-12;
    int step_for_iter = 500;
    int finish_for_conv = 700;
    double result_norm_resid;
    double q = 1;
    double dq = 1;
    double resid_for_x_0;


    char config[] = "config_1.txt";
    char out[] = "out_3_conv.txt";
    char gnu[] = "gnu_3.txt";
    std::ifstream config_file;
    std::ofstream outFile_1;
    double *A, *B, *b, *x, *_trash;
    // double m, M;
    FILE *pipe;



    // CONFIG READ
    // ___________________________________________
    config_file.open(config);
    config_file >> N >> p;
    std::cout << "N = " << N << "; p = " << p << ";" << std::endl;
    config_file.close();
    // ___________________________________________

    try {
        A = new double[(N+1)*(N+1)];
        B = new double[(N+1)*(N+1)];
        b = new double[N+1];
        x = new double[N+1];
        _trash = new double[N+1];
        } catch(...){
                std::cout << "Some trouble with memory" << std::endl;
                return -2;
        }


    // ___________________________________________
    // ___________________________________________
    // ЗАДАНИЕ 3

    __fillMatrix(B, N, p, true, true);
    printf("matrix B = ");
    print_matrix(B, N);

     __fillMatrix(A, N, p, true, false);
    printf("matrix A = ");
    print_matrix(A, N);

    __make_coef_b(A, N, b);
    printf("b = ");
    print_vector(b, N);

    result_norm_resid = BSolver(x, A, B, b, tau, N, eps, step_for_iter, _trash, p);

    // из требований просят вывести евклидовую норму
    printf("residual(infty) = %20.15lf \n", __euclid_calculate_norm_vec(_trash, b, N));

    // printf("result = ");
    // print_vector(_trash, N);
    printf("x = ");
    print_vector(x, N);
    printf("theory answer = \n");
    for(i = 0; i < N + 1; i++){
        if(i == 0 || i == N){
            printf("%20.15lf ", 0.);
            continue;
        } else if (i % 2 == 1){
            printf("%20.15lf ", 1.);
            continue;
        } else {
            printf("%20.15lf ", 0.);
        }
    }
    printf("\n");

    
    // ___________________________________________

    // надо найти q
    q = find_q_for_conv(A, N);
    printf("q = %lf \n", q);
    resid_for_x_0 = BSolver(x, A, B, b, tau, N, eps, 1, _trash, p);

    outFile_1.open(out);
    if(outFile_1.is_open()){
        for(i = 1; i < finish_for_conv; i+= 10){
            result_norm_resid = BSolver(x, A, B, b, tau, N, eps, i, _trash, p);
            outFile_1 << std::setprecision(15) << i << " " << result_norm_resid << " " << dq*resid_for_x_0 << std::endl;
            dq *= q; // геометрич прогр
        }
    } else {
        std::cout << "ERROR: u cant create out_3_conv.txt" << std::endl;
        delete [] A;
        delete [] b;
        delete [] x;
        delete [] _trash;
        return -5;
    }
    outFile_1.close();



    outFile_1.open(gnu);
    if(outFile_1.is_open()){
            // outFile_1 << "set terminal png size 1000,1000 \n" << std::endl;
            // outFile_1 << "set output \"plot_res.png\" \n" << std::endl;
            outFile_1 << "plot 'out_3_conv.txt' u 1:2 w linesp title 'result practice(norm = infty)', 'out_3_conv.txt' u 1:3 w linesp title 'result theory(norm = infty)' \\" << std::endl;
    } else {
        std::cout << "ERROR: u cant create out_3_conv.txt and out_3_conv.txt" << std::endl;
        delete [] A;
        delete [] b;
        delete [] x;
        delete [] _trash;
        return -5;
    }
    outFile_1.close();



    pipe = popen("gnuplot -persist 'gnu_3.txt'" , "w");

    if (pipe != NULL){
        fflush(pipe);
        pclose(pipe);
    } else {
        std::cout << "ERROR: u cant open gnu_3.txt" << std::endl;
        delete [] A;
        delete [] b;
        delete [] x;
        delete [] _trash;
        return -6;
    }

    delete [] A;
    delete [] b;
    delete [] x;
    delete [] _trash;
    return 1;
}

