#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <omp.h>
using namespace std;

double f(double x)
{
	return 1 / (1 + x * x);
}

double arctg(double a, double b, int n, int t, int m)
{
	double sum = 0;
	for (int i = t; i <= n; ++i)
	{
		sum += (1. / m) * f(a + (b - a) * (2 * i - 1) / (2 * m));
	}

	return sum;
}
int main()
{
	int n = 0;
	cin >> n;
	double pi1 = 0;
	double t1 = omp_get_wtime();

	pi1 = arctg(0, 1, n, 1, n) * 4;
	std::cout << "Time1: " << omp_get_wtime() - t1 << endl;
	std::cout << pi1 << endl;

	double pi2 = 0;
	double k1 = 0;
	double k2 = 0;
	double t2 = omp_get_wtime();
#pragma omp parallel sections
	{
#pragma omp section
		{

			k1 = arctg(0, 1, n / 2, 1, n) * 4;
		}

#pragma omp section
		{

			k2 = arctg(0, 1, n, n / 2 + 1, n) * 4;
		}
	}

	pi2 = k1 + k2;

	std::cout << "Time2: " << omp_get_wtime() - t2 << endl;
	std::cout << pi2 << endl;

	double pi3 = 0;
	double l1 = 0;
	double l2 = 0;
	double l3 = 0;
	double l4 = 0;
	double t3 = omp_get_wtime();
#pragma omp parallel sections
	{
#pragma omp section
		{

			l1 = arctg(0, 1, n / 4, 1, n) * 4;
		}

#pragma omp section
		{

			l2 = arctg(0, 1, n / 2, n / 4 + 1, n) * 4;
		}
#pragma omp section
		{

			l3 = arctg(0, 1, 3 * n / 4, n / 2 + 1, n) * 4;
		}
#pragma omp section
		{

			l4 = arctg(0, 1, n, 3 * n / 4 + 1, n) * 4;
		}
	}

	pi3 = l1 + l2 + l3 + l4;

	std::cout << "Time3: " << omp_get_wtime() - t3 << endl;
	std::cout << pi3 << endl;
	return EXIT_SUCCESS;
}