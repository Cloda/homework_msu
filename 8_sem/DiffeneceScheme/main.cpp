#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;

double *Method_1(double y_0, int N, double A)
{

    double *y = (double *)calloc(N, sizeof(double));

    y[0] = y_0;
    double h = 1 / (double)N;

    for (int i = 1; i < N; i++)
    {
        y[i] = (1 - A * h) * y[i - 1];
    }

    return y;
}

double *Method_2(double y_0, int N, double A)
{

    double *y = (double *)calloc(N, sizeof(double));

    y[0] = y_0;
    double h = 1 / (double)N;

    for (int i = 1; i < N; i++)
    {
        y[i] = y[i - 1] / (1 + A * h);
    }

    return y;
}

double *Method_3(double y_0, int N, double A)
{

    double *y = (double *)calloc(N, sizeof(double));

    y[0] = y_0;
    double h = 1 / (double)N;

    for (int i = 1; i < N; i++)
    {
        y[i] = (2 - A * h) * y[i - 1] / (2 + A * h);
    }

    return y;
}

double *Method_4(double y_0, double y_1, int N, double A)
{

    double *y = (double *)calloc(N, sizeof(double));

    y[0] = y_0;
    y[1] = y_1;
    double h = 1 / (double)N;

    for (int i = 2; i < N; i++)
    {
        y[i] = y[i - 2] - 2 * h * A * y[i - 1];
    }

    return y;
}

double *Method_5(double y_0, double y_1, int N, double A)
{

    double *y = (double *)calloc(N, sizeof(double));

    y[0] = y_0;
    y[1] = y_1;
    double h = 1 / (double)N;

    for (int i = 2; i < N; i++)
    {
        y[i] = (2 * y[i - 1] - 0.5 * y[i - 2]) / (1.5 + A * h);
    }

    return y;
}

double *Method_6(double y_0, double y_1, int N, double A)
{

    double *y = (double *)calloc(N, sizeof(double));

    y[0] = y_0;
    y[1] = y_1;
    double h = 1 / (double)N;

    for (int i = 2; i < N; i++)
    {
        y[i] = 2 * (2 * y[i - 1] - (1.5 - A * h) * y[i - 2]);
    }

    return y;
}

double *Method(int number_method, int N, double A)
{
    double *y = NULL;
    double h = 1 / (double)N;

    switch (number_method)
    {
    case 1:
        y = Method_1(1, N, A);
        break;
    case 2:
        y = Method_2(1, N, A);
        break;
    case 3:
        y = Method_3(1, N, A);
        break;
    case 4:
        y = Method_4(1, 1 - A * h, N, A);
        break;
    case 5:
        y = Method_5(1, 1 - A * h, N, A);
        break;
    case 6:
        y = Method_6(1, 1 - A * h, N, A);
        break;
    }

    return y;
}

double E_n(int number_method, int n, double A)
{
    int N = pow(10, n);

    double *y = Method(number_method, N, A);

    double max = fabs(y[0] - 1);

    for (int i = 0; i < N; i++)
    {
        if (max < fabs(y[i] - exp(-A * (i / (double)N))))
        {
            max = fabs(y[i] - exp(-A * (i / (double)N)));
        }
    }

    free(y);

    return max;
}

int main() {

	double A = 1;
	int n = 1;
	int number_method = 1;

	cout << "   Введите значение параметра А" << endl;
	cin >> A;

	cout << "   Введите значения порядка дробления узлов n" << endl;
	cin >> n;

	cout << "   Введите номер разностной схемы" << endl;
	cin >> number_method;

	cout << E_n(number_method, n, A) << endl;

	return 0;

}