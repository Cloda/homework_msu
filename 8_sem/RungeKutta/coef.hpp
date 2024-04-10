typedef void (*func)(double x, double *y, int n, double *temporary);

void K(func f, double x, double *y, double h, int n, double *k);

void Yn(func f, double x, double *y, double h, int n, double *y_n, double *k1, double *k2, double *k3, double *k4);

void En(func f, double x, double *y, double h, int n, double *E_n, double *k1, double *k2, double *k3, double *k4);

double L2_h_norm(double *x, double *y, double h, int n);

double L0_norm(double *x, int n);

double L0_norm(double *x, double *y, int n);

double L2_h_diff_norm(double *x, double *y, double h, int n);