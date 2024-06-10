#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <omp.h>
using namespace std;
int main()
{
	double n = 0;
	cin >> n;

	double k = M_PI / (2 * n);
	double* a1 = new double[n + 1];
	double t1 = omp_get_wtime();
	for (int i = 0; i <= n; ++i)
	{
		a1[i] = sin(i * k);
	}

	/*
	for (int i = 0; i <= (M_PI / 2) / k; ++i)
	{
		cout << a[i] << " ";
	}
	*/
	cout << "Time1: " << omp_get_wtime() - t1 << endl;


	double* a2 = new double[n + 1];
	double t2 = omp_get_wtime();
#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 0; i <= n / 2; ++i)
			{
				a2[i] = sin(i * k);
			}

		}
#pragma omp section
		{
			for (int i = n / 2 + 1; i <= n; ++i)
			{
				a2[i] = sin(i * k);
			}
		}
	}

	cout << "Time2: " << omp_get_wtime() - t2 << endl;



	double* a3 = new double[n + 1];
	double t3 = omp_get_wtime();
#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 0; i <= n / 4; ++i)
			{
				a3[i] = sin(i * k);
			}

		}
#pragma omp section
		{
			for (int i = n / 4 + 1; i <= n / 2; ++i)
			{
				a3[i] = sin(i * k);
			}
		}
#pragma omp section
		{
			for (int i = n / 2 + 1; i <= n / 2 + n / 4; ++i)
			{
				a3[i] = sin(i * k);
			}
		}
#pragma omp section
		{
			for (int i = n / 2 + n / 4 + 1; i <= n; ++i)
			{
				a3[i] = sin(i * k);
			}
		}

	}
	cout << "Time3: " << omp_get_wtime() - t3 << endl;


	return EXIT_SUCCESS;
}