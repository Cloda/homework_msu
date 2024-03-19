#include <iostream>
#include <math.h>

double y_k(int k, int m, int N)
{
    return sin((M_PI * (2*m - 1) * (N - k)) / (2*N - 1));
}

double lambda_m(double p, int m, int N)
{
    return (2*N - 1)*(2*N - 1)*sin((M_PI*(2*m - 1))/(4*N - 2))*sin((M_PI*(2*m - 1))/(4*N - 2));
}

int main()
{
    int N = 10;
    double p = 0.1;
    double h = 1. / ((double)N - 0.5);

    double lambda = 0.;
    double value_right = 0.;
    double value_left = 0.;

    for (int m = 0; m < N; m++)
    {
        lambda = lambda_m(p, m, N);

        for (int k = 1; k < N; k++)
        {
            value_right = (y_k(k + 1, m, N) - 2 * y_k(k, m, N) + y_k(k - 1, m, N)) / (h * h);
            value_left = -lambda * y_k(k, m, N);

            if (fabs(value_right - value_left) > 1e-7)
            {
                std::cout << "Fail" << std::endl;
                break;
            }
        }
    }

    return 1;
}
