#include <iostream>
#include <cmath>
#include <fstream>

void SchemaFirst(double *y, double y_0, int N, double A)
{
    y[0] = y_0;
    double h = 1 / static_cast<double>(N);

    for (int i = 1; i < N; i++)
    {
        y[i] = (1 - A * h) * y[i - 1];
    }
}

void SchemaSecond(double *y, double y_0, int N, double A)
{
    y[0] = y_0;
    double h = 1 / static_cast<double>(N);

    for (int i = 1; i < N; i++)
    {
        y[i] = y[i - 1] / (1 + A * h);
    }
}

void SchemaThird(double *y, double y_0, int N, double A)
{
    y[0] = y_0;
    double h = 1 / (double)N;

    for (int i = 1; i < N; i++)
    {
        y[i] = (2 - A * h) * y[i - 1] / (2 + A * h);
    }
}

void SchemaFourth(double *y, double y_0, double y_1, int N, double A)
{
    y[0] = y_0;
    y[1] = y_1;
    double h = 1 / (double)N;

    for (int i = 2; i < N; i++)
    {
        y[i] = y[i - 2] - 2 * h * A * y[i - 1];
    }
}

void SchemaFifth(double *y, double y_0, double y_1, int N, double A)
{
    y[0] = y_0;
    y[1] = y_1;
    double h = 1 / (double)N;

    for (int i = 2; i < N; i++)
    {
        y[i] = (2 * y[i - 1] - 0.5 * y[i - 2]) / (1.5 + A * h);
    }
}

void SchemaSixth(double *y, double y_0, double y_1, int N, double A)
{
    y[0] = y_0;
    y[1] = y_1;
    double h = 1 / (double)N;

    for (int i = 2; i < N; i++)
    {
        y[i] = 2 * (2 * y[i - 1] - (1.5 - A * h) * y[i - 2]);
    }
}

void chooseSchema(double *y, int regime, int N, double A)
{
    double h = 1 / static_cast<double>(N);

    switch (regime)
    {
        case 1:
            SchemaFirst(y, 1, N, A);
            break;
        case 2:
            SchemaSecond(y, 1, N, A);
            break;
        case 3:
            SchemaThird(y, 1, N, A);
            break;
        case 4:
            SchemaFourth(y, 1, 1 - A * h, N, A);
            break;
        case 5:
            SchemaFifth(y, 1, 1 - A * h, N, A);
            break;
        case 6:
            SchemaSixth(y, 1, 1 - A * h, N, A);
            break;
    }
}

double findMaximumDifference(int regime, int n, double A, double left_dot, double right_dot)
{
    int N = std::pow(10, n);
    double *y = new double[N];
    chooseSchema(y, regime, N, A);

    double max = std::fabs(y[0] - 1);

    for (int i = 0; i < N; i++)
    {
        double diff = std::fabs(y[i] - std::exp(-A * (right_dot - left_dot) * (i / static_cast<double>(N))));
        if (max < diff)
        {
            max = diff;
        }
    }

    delete[] y;

    return max;
}

int main()
{
    int listFor_A[3] = {1, 10, 1000};
    int amountOfSchems = 6;
    int listFor_n[4] = {1, 2, 3, 6};
    double left = 0.;
    double right_1 = 1.;
    double right_2 = 0.1;

    // double A = 10;
    // double n = 10;
    // double schema = 1;
    // std::cout << findMaximumDifference(schema, n, A, left, right_1) << std::endl;


    std::ofstream big_interval("big_interval.txt");
    std::ofstream small_interval("small_interval.txt");

    if (!big_interval || !small_interval) {
        std::cerr << "Ошибка при открытии файла для записи." << std::endl;
        return -1;
    }

    big_interval << "№ " << "E1 " << "E2 " << "E2 " 
                 << "E3 " << "E6 " << "m " << "A "
                 << std::endl;

    small_interval << "№ " << "E1 " << "E2 " << "E2 " 
                   << "E3 " << "E6 " << "m " << "A "
                   << std::endl;

    // Schemas
    for(int i = 0; i < amountOfSchems; i++)
    {
        // A
        for(int j = 0; j < 3; j++)
        {
            big_interval << i << " ";
            small_interval << i << " ";
            // E_n
            for(int k = 0; k < 4; k++)
            {
                big_interval << findMaximumDifference(i, listFor_n[k], listFor_A[j], left, right_1) << " ";
                small_interval << findMaximumDifference(i, listFor_n[k], listFor_A[j], left, right_2) << " ";

            }
            big_interval << "m " << listFor_A[j] << std::endl;
            small_interval << "m " << listFor_A[j] << std::endl;
        }
    }


    return 0;
}
