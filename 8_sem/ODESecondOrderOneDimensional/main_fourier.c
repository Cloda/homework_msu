#include "FourierMethod.h"

double f(double x){ 
    UNUSED(x); 
    return 1.0; 
}

double coef_b(double * b, double (*f)(double), int N){
    double delta = 0;
    double h = (double)(1 / N);
    for(int j = 0; j < N; j++) {
        b[j] = f(delta);
        delta += h;
    }
    return 0.;
}

void analytical_solution(double * y_exact, double * x, int N)
{
    // для p==0 f==1
    // for (int i = 0; i < N + 1; i++)
    // {
    //     y_exact[i] = x[i] * (1 - x[i]) / 2.0;
    // }
    
    // для p==1 f==1
    double C = -1 / (exp(1) + 1);
    for (int i = 0; i < N + 1; i++)
    {
        y_exact[i] = C * exp(x[i]) - (1 + C) * exp(-x[i]) + 1; 
    }
    
}

void draw_plots(const char *filename, const char *outputfile) {
    FILE *gnuplot = popen("gnuplot -persistent", "w");
    if (gnuplot == NULL) {
        fprintf(stderr, "Error: Unable to open pipe to Gnuplot.\n");
        exit(1);
    }

    fprintf(gnuplot, "set terminal pngcairo size 800,600 enhanced font 'Verdana,10'\n");
    fprintf(gnuplot, "set output '%s'\n", outputfile);
    fprintf(gnuplot, "set title 'Difference between Numerical and Analytical Solutions'\n");
    fprintf(gnuplot, "set xlabel 'x'\n");
    fprintf(gnuplot, "set ylabel 'Value'\n");
    fprintf(gnuplot, "set grid\n");
    fprintf(gnuplot, "plot '%s' using 1:2 with lines title 'Numerical', \\\n", filename);
    fprintf(gnuplot, "     '%s' using 1:3 with points title 'Analytical'\n", filename);
}

void write_results_to_file(const char * filename, double * approx, double * exact, int N, double *x)
{
    FILE * file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "x\tNumerical\tAnalytical\tDifference\n");
    for (int i = 0; i < N + 1; i++)
    {
        double difference = approx[i] - exact[i];
        fprintf(file, "%lf\t%lf\t%lf\t%lf\n", x[i], approx[i], exact[i], difference);
    }

    fclose(file);
}

int main()
{
    int N = 6;  // Задаем количество точек
    double p = 1.;  // Задаем значение параметра p
    double *b;
    double *x;
    double *mem;
    double *x_values;
    double *exact;

    b = (double *)malloc((N + 1) * sizeof(double));
    x = (double *)malloc((N + 1) * sizeof(double));
    mem = (double *)malloc((N + 1) * sizeof(double));
    x_values = (double *)malloc((N + 1) * sizeof(double));
    exact = (double *)malloc((N + 1) * sizeof(double));
    
    for (int i = 0; i < N + 1; i++)
    {
        x_values[i] = (double)i / N;
    }

    coef_b(b, f, N);
    FourierMethod(x, N, p, b);
    analytical_solution(exact, x_values, N);

    // printf("ans: ");
    // print_vector(x, N + 1);
    // printf("exact: ");
    // print_vector(exact, N + 1);

    write_results_to_file("results.txt", x, exact, N, x_values);
    draw_plots("results.txt", "difference_plot.png");


    free(b);
    free(x);
    free(mem);
    free(x_values);
    free(exact);

    return 0;
}
