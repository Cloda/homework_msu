#include "FourierMethod.h"

double f(double x){ 
    UNUSED(x); 
    return 1.0; 
}

double full_b_f(double * b, double (*f)(double), int N){
    double delta = 0;
    double h = (double)(1 / N);
    for(int j = 0; j < N; j++) {
        b[j] = f(delta);
        delta += h;
    }
    return 0.;
}

int main()
{
    int N = 6;  // Задаем количество точек
    double p = 0.;  // Задаем значение параметра p
    double *b;
    double *x;
    double *mem;

    b = (double *)malloc((N + 1) * sizeof(double));
    x = (double *)malloc((N + 1) * sizeof(double));
    mem = (double *)malloc((N + 1) * sizeof(double));
    
    full_b_f(b, f, N);
    FourierMethod(x, N, p, b);
    
    printf("b: ");
    print_vector(b, N + 1);
    printf("ans: ");
    print_vector(x, N + 1);

    free(b);
    free(x);
    free(mem);

    return 0;
}
