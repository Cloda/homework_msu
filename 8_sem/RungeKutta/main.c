#include "func.h"
#include "scheme.h"
#include <stdio.h>
#include <stdlib.h>

// Функция для ввода количества итераций
int getIterationCount() {
    // int iterations;
    // printf("Введите количество итераций: ");
    // scanf("%d", &iterations);
    // return iterations;
    return 100;
}

// Функция для теста 1
void test1(int iterations) {
    double x = 0;
    int N = 1;
    
    double *y = (double*) malloc(N * sizeof(double));
    double *ans = (double*) malloc(N * sizeof(double));
    double *realans = (double*) malloc(N * sizeof(double));
    double *mem = (double*) malloc(N * sizeof(double));
    double *mem1 = (double*) malloc(N * sizeof(double));
    double *mem2 = (double*) malloc(N * sizeof(double));
    double *mem3 = (double*) malloc(N * sizeof(double));

    y[0] = 1;

    FILE *file = fopen("out1.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file for writing.\n");
        return;
    }

    // Заголовки столбцов
    fprintf(file, "x realans0 y0\n");

    for(int j = 0; j < iterations; j++) {
        solution1(x, y, realans, N);
        yNext(x, y, ans, N, 0.01, calculateF1, mem, mem1, mem2, mem3);
        y[0] = ans[0];
        x += 0.01;
        fprintf(file, "%lf %lf %lf\n", x, y[0], realans[0]);
    }

    fclose(file);
    free(y);
    free(ans);
    free(mem);
    free(mem1);
    free(mem2);
    free(mem3);
    free(realans);

}

// Функция для синуса
void test2(int iterations) {
    double x = 0;
    int N = 1;
    
    double *y = (double*) malloc(N * sizeof(double));
    double *ans = (double*) malloc(N * sizeof(double));
    double *realans = (double*) malloc(N * sizeof(double));
    double *mem = (double*) malloc(N * sizeof(double));
    double *mem1 = (double*) malloc(N * sizeof(double));
    double *mem2 = (double*) malloc(N * sizeof(double));
    double *mem3 = (double*) malloc(N * sizeof(double));

    y[0] = 1;

    FILE *file = fopen("out2.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file for writing.\n");
        return;
    }

    // Заголовки столбцов
    fprintf(file, "x realans0 y0\n");

    for(int j = 0; j < iterations; j++) {
        solution2(x, y, realans, N);
        yNext(x, y, ans, N, 0.01, calculateF2, mem, mem1, mem2, mem3);
        y[0] = ans[0];
        x += 0.01;
        fprintf(file, "%lf %lf %lf\n", x, y[0], realans[0]);
    }

    fclose(file);
    free(y);
    free(ans);
    free(mem);
    free(mem1);
    free(mem2);
    free(mem3);
    free(realans);

}

// Функция для теста 3
void test3(int iterations) {
    double x = 0;
    int N = 2;

    double *y = (double*) malloc(N * sizeof(double));
    double *ans = (double*) malloc(N * sizeof(double));
    double *realans = (double*) malloc(N * sizeof(double));
    double *mem = (double*) malloc(N * sizeof(double));
    double *mem1 = (double*) malloc(N * sizeof(double));
    double *mem2 = (double*) malloc(N * sizeof(double));
    double *mem3 = (double*) malloc(N * sizeof(double));

    y[0] = 1;
    y[1] = -1;

    FILE *file = fopen("out3.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file for writing.\n");
        return;
    }


    // Заголовки столбцов
    fprintf(file, "x realans0 y0 realans1 y1\n");

    for(int j = 0; j < iterations; j++) {
        solution3(x, y, realans, N);
        yNext(x, y, ans, N, 0.01, calculateF3, mem, mem1, mem2, mem3);
        y[0] = ans[0];
        y[1] = ans[1];
        x += 0.01;
        fprintf(file, "%lf %lf %lf %lf %lf\n", x, realans[0], y[0], realans[1], y[1]);
    }

    fclose(file);
    free(y);
    free(ans);
    free(mem);
    free(mem1);
    free(mem2);
    free(mem3);
    free(realans);

}

// Функция для теста 4
void test4(int iterations) {
    double x = 0;
    double h = 1.0;
    int N = 2;

    double *y = (double*) malloc(N * sizeof(double));
    double *ans = (double*) malloc(N * sizeof(double));
    double *realans = (double*) malloc(N * sizeof(double));
    double *mem = (double*) malloc(N * sizeof(double));
    double *mem1 = (double*) malloc(N * sizeof(double));
    double *mem2 = (double*) malloc(N * sizeof(double));
    double *mem3 = (double*) malloc(N * sizeof(double));

    y[0] = 1;
    y[1] = -1;

    FILE *file = fopen("out4.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file for writing.\n");
        return;
    }

    // Заголовки столбцов
    fprintf(file, "x realans0 y0 realans1 y1 L0norm L0normOne En\n");

    for(int j = 0; j < iterations; j++) {
        solution4(x, y, realans, N);
        E(x, y, ans, N, h, calculateF4, mem, mem1, mem2, mem3);
        fprintf(file, "%e %e %e %e %e %e %e\n", x, realans[0], y[0], realans[1], y[1], calculateL0norm(realans, y, N), calculateL0normOne(ans, N));
        yNext(x, y, ans, N, h, calculateF4, mem, mem1, mem2, mem3);
        y[0] = ans[0];
        y[1] = ans[1];
        x += h;
    }

    fclose(file);
    free(y);
    free(ans);
    free(mem);
    free(mem1);
    free(mem2);
    free(mem3);
    free(realans);
}

// Функция для теста 5
void test5(int iterations) {
    double x = 0;
    // double h = 1.0;
    double h = 0.01;

    int N = 2;

    double *y = (double*) malloc(N * sizeof(double));
    double *ans = (double*) malloc(N * sizeof(double));
    double *realans = (double*) malloc(N * sizeof(double));
    double *mem = (double*) malloc(N * sizeof(double));
    double *mem1 = (double*) malloc(N * sizeof(double));
    double *mem2 = (double*) malloc(N * sizeof(double));
    double *mem3 = (double*) malloc(N * sizeof(double));

    y[0] = 1;
    y[1] = 0;

    FILE *file = fopen("out5.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file for writing.\n");
        return;
    }

    // Заголовки столбцов
    fprintf(file, "x realans0 y0 realans1 y1 L0norm L0normOne\n");

    for(int j = 0; j < iterations; j++) {
        solution5(x, y, realans, N);
        E(x, y, ans, N, h, calculateF5, mem, mem1, mem2, mem3);
        fprintf(file, "%e %e %e %e %e %e %e\n", x, realans[0], y[0], realans[1], y[1], calculateL0norm(realans, y, N), calculateL0normOne(ans, N));
        yNext(x, y, ans, N, h, calculateF5, mem, mem1, mem2, mem3);
        y[0] = ans[0];
        y[1] = ans[1];
        x += h;
    }

    fclose(file);
    free(y);
    free(ans);
    free(mem);
    free(mem1);
    free(mem2);
    free(mem3);
    free(realans);
}

// Функция для рисования графиков с помощью Gnuplot
void plot_results(const char *filename, const char *outputfile) {
    FILE *gnuplot = popen("gnuplot -persistent", "w");
    if (gnuplot == NULL) {
        fprintf(stderr, "Error: Unable to open pipe to Gnuplot.\n");
        exit(1);
    }

    // Настройка Gnuplot
    fprintf(gnuplot, "set terminal pngcairo size 800,600 enhanced font 'Verdana,10'\n");
    fprintf(gnuplot, "set output '%s'\n", outputfile);
    fprintf(gnuplot, "set title 'Results Plot'\n");
    fprintf(gnuplot, "set xlabel 'x'\n");
    fprintf(gnuplot, "set ylabel 'y'\n");
    fprintf(gnuplot, "set grid\n");
    fprintf(gnuplot, "plot '%s' using 1:2 with lines title 'realans[0]', \\\n", filename);
    fprintf(gnuplot, "     '%s' using 1:3 with lines title 'y[0]', \\\n", filename);
    fprintf(gnuplot, "     '%s' using 1:4 with lines title 'realans[1]', \\\n", filename);
    fprintf(gnuplot, "     '%s' using 1:5 with lines title 'y[1]'\n", filename);

    pclose(gnuplot);
}

int main(void) {
    int iterations;

    printf("Running test 1...\n");
    iterations = getIterationCount();
    test1(iterations);

    printf("Running test 2...\n");
    iterations = getIterationCount();
    test2(iterations);

    printf("Running test 3...\n");
    iterations = getIterationCount();
    test3(iterations);

    printf("Running test 4...\n");
    iterations = getIterationCount();
    test4(iterations);

    printf("Running test 5...\n");
    iterations = getIterationCount();
    test5(iterations);

    // Рисование графиков
    printf("Plotting results for out1.txt...\n");
    plot_results("out1.txt", "results1.png");

    printf("Plotting results for out2.txt...\n");
    plot_results("out2.txt", "results2.png");

    printf("Plotting results for out3.txt...\n");
    plot_results("out3.txt", "results3.png");

    printf("Plotting results for out4.txt...\n");
    plot_results("out4.txt", "results4.png");

    printf("Plotting results for out5.txt...\n");
    plot_results("out5.txt", "results5.png");

    return 0;
}
