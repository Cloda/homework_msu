#include "scheme.h"
#include "func.h"

// k1 функция
void k1(double x, double *y, double *ans, int n, double h, void (*function)(double, double*, double*, int)) {
    function(x, y, ans, n);
    for(int k = 0; k < n; k++) {
        ans[k] *= h;
    }
}

// k2 функция
void k2(double x, double *y, double *ans, int n, double h, void (*function)(double, double*, double*, int), double *mem) {
    UNUSED(mem);
    k1(x, y, ans, n, h, function);
    for(int k = 0; k < n; k++) {
        ans[k] = y[k] + ans[k] / 3;
    }
    function(x + h / 3, ans, ans, n);
    for(int k = 0; k < n; k++) {
        ans[k] *= h;
    }
}

// k3 функция
void k3(double x, double *y, double *ans, int n, double h, void (*function)(double, double*, double*, int), double *mem, double *mem1) {
    UNUSED(mem1);
    k1(x, y, ans, n, h, function);
    k2(x, y, mem, n, h, function, mem1);
    for(int k = 0; k < n; k++) {
        mem[k] = y[k] + (-1./3.)*ans[k] + mem[k];
        // mem[k] = y[k] + (ans[k] + mem[k]) / 6;
    }
    function(x + (2.*h) / 3, mem, ans, n);
    // function(x + h / 3, mem, ans, n);
    for(int k = 0; k < n; k++) {
        ans[k] *= h;
    }
}

// k4 функция
void k4(double x, double *y, double *ans, int n, double h, void (*function)(double, double*, double*, int), double *mem, double *mem1, double *mem2) {
    UNUSED(mem2);
    k3(x, y, mem, n, h, function, mem1, mem2);
    k2(x, y, mem2, n, h, function, mem1);
    k1(x, y, mem1, n, h, function);
    for(int k = 0; k < n; k++) {
        // mem1[k] = y[k] + (mem1[k] + 3 * mem[k]) / 8;
        mem1[k] = y[k] + mem1[k] - mem2[k] + mem[k];
    }
    // function(x + h / 2, mem1, ans, n);
    function(x + h, mem1, ans, n);
    for(int k = 0; k < n; k++) {
        ans[k] *= h;
    }
}

// E функция
void E(double x, double *y, double *ans, int n, double h, void (*function)(double, double*, double*, int), double *mem, double *mem1, double *mem2, double *mem3) {
    UNUSED(mem3);
    k4(x, y, mem1, n, h, function, mem2, mem3, ans);
    k3(x, y, mem, n, h, function, mem2, mem3);
    k2(x, y, mem3, n, h, function, mem2);
    k1(x, y, mem2, n, h, function);
    for(int k = 0; k < n; k++) {
        ans[k] = (2.0 / 3.0)*(mem2[k] - mem2[k] - mem[k] + mem1[k]);
    }
}

// yNext функция
void yNext(double x0, double *y0, double *ans, int n, double h, void (*function)(double, double*, double*, int), double *mem, double *mem1, double *mem2, double *mem3) {
    k4(x0, y0, mem1, n, h, function, mem2, mem3, ans);
    k3(x0, y0, mem, n, h, function, mem2, mem3);
    k2(x0, y0, mem3, n, h, function, mem2);
    k1(x0, y0, mem2, n, h, function);
    for(int k = 0; k < n; k++) {
        // ans[k] = y0[k] + (mem2[k] + 4 * mem1[k] + mem[k]) / 6;
        ans[k] = y0[k] + (mem2[k]+3*mem3[k] + 3*mem[k] + mem1[k]) / 8.;
    }
}
