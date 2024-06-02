#include <iostream>
#include <cmath>
#include <cstring>
#include "func_and_algorithm.hpp"




int main() {

    int N, M, flag;
	double h, tau;
	double* u;
	double* sol;
	double* p;
	double* f;
	double* b1;
	double* a1;
	double* c1;
	double* cup;
	double* tmp;
	FILE* fout;
	FILE* fout1;


    // printf("Введите N (количество точек по t), M (количество точек по x):\n");
	// scanf("%d", &N);
	// scanf("%d", &M);
	// printf("Введите номер схемы (1 - явная, 2 - неявная):\n");
	// scanf("%d", &m);
	N = 10;
	M = 10;
	flag = 2;


	
	if(N < 1 || M < 1){
		printf("Error!\n");
		return -1;
	}
	
	h = 1.0 / M;
	tau = 1.0 / N;
	
	u = new double [(N + 1) * (M + 1)];

    if (u == NULL) {
        printf("Не удалось выделить память под массив u!\n");
        return -1;
    }
	
	p = new double [M + 1];

    if (p == NULL) {
		delete[] u;
        printf("Не удалось выделить память под массив b!\n");
        return -1;
    }
	
	f = new double [(N + 1) * (M + 1)];

    if (f == NULL) {
		delete[] u;
		delete[] p;
        printf("Не удалось выделить память под массив f!\n");
        return -1;
    }
	
	sol = new double [(N + 1) * (M + 1)];

    if (sol == NULL) {
		delete[] u;
		delete[] p;
		delete[] f;
        printf("Не удалось выделить память под массив sol!\n");
        return -1;
    }
	
	a1 = new double [M + 1];

    if (a1 == NULL) {
		delete[] u;
		delete[] p;
		delete[] f;
		delete[] sol;
        printf("Не удалось выделить память под массив sol!\n");
        return -1;
    }
	
	b1 = new double [M + 1];

    if (b1 == NULL) {
		delete[] u;
		delete[] p;
		delete[] f;
		delete[] sol;
		delete[] a1;
        printf("Не удалось выделить память под массив sol!\n");
        return -1;
    }
	
	c1 = new double [M + 1];

    if (c1 == NULL) {
		delete[] u;
		delete[] p;
		delete[] f;
		delete[] sol;
		delete[] a1;
		delete[] b1;
        printf("Не удалось выделить память под массив sol!\n");
        return -1;
    }
	
	cup = new double [M + 1];

    if (cup == NULL) {
		delete[] u;
		delete[] p;
		delete[] f;
		delete[] sol;
		delete[] a1;
		delete[] b1;
		delete[] c1;
        printf("Не удалось выделить память под массив sol!\n");
        return -1;
    }
	
	tmp = new double [M + 1];

    if (tmp == NULL) {
		delete[] u;
		delete[] p;
		delete[] f;
		delete[] sol;
		delete[] a1;
		delete[] b1;
		delete[] c1;
		delete[] cup;
        printf("Не удалось выделить память под массив sol!\n");
        return -1;
    }
	
	
	for (int i = 0; i < (N + 1) * (M + 1); i++){
		u[i] = 0.;
		sol[i] = 0.;
		f[i] = 0.;
	}
	
	for (int i = 0; i < M + 1; i++){
		p[i] = 0.;
		b1[i] = 0.;
		a1[i] = 0.;
		c1[i] = 0.;
		cup[i] = 0.;
		tmp[i] = 0.;
	}
	
	fout = fopen("output.txt", "w");
	if (fout == NULL) {
		delete[] u;
		delete[] p;
		delete[] f;
		delete[] sol;
		delete[] a1;
		delete[] b1;
		delete[] c1;
		delete[] cup;
		delete[] tmp;
        printf("Can't open file!\n");
        return -1;
    }
	fout1 = fopen("output1.txt", "w");
	if (fout == NULL) {
		delete[] u;
		delete[] p;
		delete[] f;
		delete[] sol;
		delete[] a1;
		delete[] b1;
		delete[] c1;
		delete[] cup;
		delete[] tmp;
        printf("Can't open file!\n");
        return -1;
    }
	
	sol_func(N, M, tau, h, u);
	p_func(M, h, p);
	f_func(N, M, tau, h, f);
	
	for (int i = 1; i < M + 1; i++){
		sol[i] = u_0(i * h);
	}
	
	if (flag == 1) {
		if(tau > h * h * 0.5) {
			printf("Error tau and h: tau/h^2 = %lf!\n", tau/(h*h));
			delete[] u;
			delete[] p;
			delete[] f;
			delete[] sol;
			delete[] a1;
			delete[] b1;
			delete[] c1;
			delete[] cup;
			delete[] tmp;
			return -1;
		} else {
			scheme1(N, M, tau, h, sol, p, f);
		}
	}
	
	if (flag == 2) {
		b1[0] = 0.0;
		c1[0] = 1.0; 
		for (int i = 1; i < M; i++){
			a1[i] = 1 / (h * h);
			b1[i] = 1 / (h * h);
			c1[i] = 2 / (h * h) + p[i] + 1/tau;
		}
		a1[M] = 2 / (h * h);
		c1[M] = 2 / (h * h) + p[M] + 1/tau;
		for(int i = 0; i < N; i++) {
			for (int j = 1; j < M + 1; j++){
				cup[j] = f[(i + 1) * (M + 1) + j] + sol[i * (M + 1) + j] / tau;
			}
			for (int j = 0; j < M + 1; j++){
				//printf("%20.7e + %20.7e = %20.7e\n", f[(i + 1) * (M + 1) + j], sol[i * (M + 1) + j] / tau, cup[j]);
			}
			if (sweep(M, tmp, cup, a1, b1, c1) == -1) {
				printf("Не удалось выделить память под массив sol!\n");
				return -1;
			}
			for (int j = 0; j < M + 1; j++){
				sol[(i + 1) * (M + 1) + j] = tmp[j];
			}
		}
	}
	
	for (int i = 0; i < N + 1; i++) {
		for (int j = 0; j < M + 1; j++){
			fprintf(fout1, "%20.7e ", u[i * (M + 1) + j]);
			fprintf(fout, "%lf ", i * tau);
			fprintf(fout, "%lf ", j * h);
			fprintf(fout, "%20.7e ", u[i * (M + 1) + j]);
			fprintf(fout, "%20.7e", sol[i * (M + 1) + j]);
			fprintf(fout, "%20.7e\n", fabs(sol[i * (M + 1) + j] - u[i * (M + 1) + j]));
		}
		fprintf(fout1, "\n");
	}
	
	printf("Error:%e\n", norm(N, M, sol, u));
	
	delete[] u;
	delete[] p;
	delete[] f;
	delete[] sol;
	delete[] a1;
	delete[] b1;
	delete[] c1;
	delete[] cup;
	delete[] tmp;
	
	fclose(fout);
	fclose(fout1);
	
    return 0;
}
