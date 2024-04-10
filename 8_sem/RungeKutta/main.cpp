#include <fstream>
#include <iostream>
#include "coef.hpp"
#include "func.hpp"

typedef void (*type_func)(double x, double *y, int n);

void test(double x_0, double y_0, int steps, int n, func F, type_func g, std::ofstream& file);
void test(double x_0, double y_0, int steps, int n, func F, type_func g, std::ofstream& file)
{
    double h = 1.0 / static_cast<double>(steps);
    double *y = new double[n];
    double *y_n = new double[n];
    double *E_n = new double[n];

    double *k1 = new double[n];
    double *k2 = new double[n];
    double *k3 = new double[n];
    double *k4 = new double[n];

    double *real_y = new double[n];

    for (int i = 0; i < n; ++i)
    {
        y[i] = y_0;
    }
    
    double x = x_0;
	file << "x | " << "real_y | " << "approx_y | " << "Norm|y() - yh| | " << "Norm|E|" << std::endl;

    for (int i = 0; i < steps; ++i)
    {
        Yn(F, x, y, h, n, y_n, k1, k2, k3, k4);
        En(F, x, y, h, n, E_n, k1, k2, k3, k4);

        x += h;
        for (int j = 0; j < n; ++j)
        {
            y[j] = y_n[j];
        }

        file << x << " | ";

        g(x, real_y, n);

        for (int j = 0; j < n; ++j)
        {
            file << real_y[j] << " ";
        }
		file << " | ";

        for (int j = 0; j < n; ++j)
        {
            file << y[j] << " ";
        }
		file << " | ";

        file << L0_norm(y_n, real_y, n) << " | ";
        file << L0_norm(E_n, n) << std::endl << std::endl;

        // std::cout << y_n[0] << " ";
    }

    // std::cout << std::endl;

    delete[] y;
    delete[] real_y;
    delete[] y_n;
    delete[] E_n;
    delete[] k1;
    delete[] k2;
    delete[] k3;
    delete[] k4;
}


int main(void)
{

	int n = 1;
	int steps = 10;
	double x_0 = 0;
	double y_0 = 0;

    std::ofstream file1("res1.txt");
    std::ofstream file2("res2.txt");
    std::ofstream file3("res3.txt");
    std::ofstream file4("res4.txt");
    std::ofstream file5("res5.txt");
    std::ofstream file6("res6.txt");


	test(x_0, y_0, steps, n, F1, G1, file1);
    test(x_0, y_0, steps, n, F2, G2, file2);
    test(x_0, y_0, steps, n, F3, G3, file3);
    test(x_0, y_0, steps, n, F4, G4, file4);
    test(x_0, y_0, steps, n, F6, G6, file6);

    y_0 = 1;
    test(x_0, y_0, steps, n, F5, G5, file5);

	return 1;
}
