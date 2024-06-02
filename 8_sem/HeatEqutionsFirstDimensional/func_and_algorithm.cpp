#include "func_and_algorithm.hpp"

double sol_(double t, double x) {
	t+=0;
	x+=0;
	//return sin(0.5 * M_PI * x) * exp(-0.25 * M_PI * M_PI * t);
	return (x * x - 2 * x) * (t + 1) ;
}

double f_(double t, double x) {
	t+=0;
	x+=0;
	//return sin(1.5 * M_PI * x) * exp(-2.25 * M_PI * M_PI * t) * x * x;
	//return 0.25 * M_PI * M_PI * sin(0.5 * M_PI * x);
	return (x * x - 2 * x) - 2 * (t + 1);
}

double u_0(double x) {
	x+=0;
	//return sin(1.5 * M_PI * x);
	//return -6*x;
	//return sin(0.5 * M_PI * x);
	return (x * x - 2 * x);
}

void sol_func(int N, int M, double tau, double h, double* u) {
	
	for (int i = 0; i < N + 1; i++) {
		for (int j = 0; j < M + 1; j++){
			u[i * (M + 1) + j] = sol_(i * tau, j * h);
		}
	}
	
}

void f_func(int N, int M, double tau, double h, double* f){
	
	for (int i = 0; i < N + 1; i++) {
		for (int j = 0; j < M + 1; j++){
			f[i * (M + 1) + j] = f_(i * tau, j * h);
		}
	}
	
}

void p_func(int M, double h, double* b){
	h +=0;
	UNUSED(h);
	for (int i = 0; i < M + 1; i++) {
		//b[i] = i * h * i * h;
		b[i] = 0;
	}
	
}

void exact(int N, int M, double tau, double h, double* u, double* b, double* f){
		
	for (int i = 0; i < N; i++) {
		for (int j = 1; j < M; j++){
			u[(i + 1) * (M + 1) + j] = u[i * (M + 1) + j] + tau * (1.0 / (h * h) * (u[i * (M + 1) + j + 1] - 2 * u[i * (M + 1) + j] + u[i * (M + 1) + j - 1]) - (b[j] * u[i * (M + 1) + j] - f[i * (M + 1) + j]));
			//printf("(%d, %d): %20.7e %20.7e %20.7e %20.7e\n", i + 1, j, u[i * (M + 1) + j - 1], u[i * (M + 1) + j], u[i * (M + 1) + j + 1], f[i * (M + 1) + j]);			
		}
		u[(i + 1) * (M + 1) + M] = u[i * (M + 1) + M] + tau * (f[i * (M + 1) + M] - (2.0/(h * h)) * (u[i * (M + 1) + M] - u[i * (M + 1) + M - 1]) - b[M] * u[i * (M + 1) + M]); //u[(i + 1) * (M + 1) + M - 1];//(2 * tau * h / (2 * tau + h * h + h * h * tau * b[M])) *(1/h * u[(i + 1) * (M + 1) + M - 1] + h / (2 * tau) * u[i * (M + 1) + M] + 0.5 * h * f[(i+1) * (M + 1) + M]) ;//u[i * (M + 1) + M] + tau * (f[i * (M + 1) + M] - (2.0/(h * h)) * (u[i * (M + 1) + M] - u[i * (M + 1) + M - 1]) - b[M] * u[i * (M + 1) + M]);
		
	}
}

int sweep(int N, double* y, double* f, double* a, double* b, double* c){
	
	double* al;
	double* bet;
	
	al = new double [N + 1];
	if (al == NULL) {
        printf("Не удалось выделить память под массив al!\n");
        return -1;
    }
	
	bet = new double [N + 1];
	if (bet == NULL) {
		delete[] al;
        printf("Не удалось выделить память под массив bet!\n");
        return -1;
    }
	al[0] = 0.0;
	bet[0] = 0.0;
	al[1] = b[0] / c[0];
	bet[1] = f[0] / c[0];
	
	for (int i = 1; i < N; i++) {
		al[i + 1] = b[i] / (c[i] - al[i] * a[i]);
		bet[i + 1] = (f[i] + a[i] * bet[i]) / (c[i] - al[i] * a[i]);
	}
	
	y[N] = (f[N] + a[N] * bet[N]) / (c[N] - al[N] * a[N]);
	for (int i = N - 1; i >= 0; i--) {
		y[i] = al[i + 1] * y[i + 1] + bet[i + 1]; 
	}
	
	delete[] al;
	delete[] bet;

	return 0;
}


double norm(int N, int M, double* sol, double* y) {
	double err = 0., tmp;
	
	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < M + 1; j++){
			tmp = fabs(sol[i * (M + 1) + j] - y[i * (M + 1) + j]);
			if (tmp > err) {
				err = tmp;
			}
		}
	}
	
	return err;
}




