#include <iostream>
#include <string>
#include <vector> 
#include <iomanip> 
#include <algorithm> 
#include <cmath>

class Matrix
{
private:
	std::vector <std::vector<double>> a;
public:
	Matrix(int n = 0, int m = 0) :
		a(n, std::vector<double>(m, 0)) {}

	int row() const  // ����� �����
	{
		return a.size();
	}

	int col() const // ����� ��������
	{
		return a[0].size();
	}

	double& operator () (int i, int j);
	//  ��������� � �������� ������� (������������� �������� ������ �������)
	const double& operator () (int i, int j) const;
	// ��� ����������� �������� 

	Matrix operator () (int i1, int i2, int j1, int j2) const;
	/*  �������� ������ ���������� (������������� �������� ������ �������)
	  � �������� ������ ����������� (������ � ����� ��������� �����,
	  ������ � ����� ��������� ��������) */

	Matrix operator* (double x) const;
	// ��������� ������� �� �����

	double MatrixNorm() const;  // ����� �������

	Matrix(const Matrix&) = default; // ����������� �����������
	// ���������� ������ ���, ������ �� ����������� ���� � 

	Matrix& operator=(const Matrix&) = default;  // ������������ ������
	// ���������� ������ ���, ������ �� ������������ ���� � 


	void transform();   // �����������
	Matrix simple_iter_method(Matrix& x_0, double prec); // ����������� 


	~Matrix() = default; // ����������
	// ���������� ������ ���, ������ �� ����������� ���� �

	friend Matrix operator*(const Matrix& a, const Matrix& b); // ��������� ������ 
	friend Matrix operator+(const Matrix& a, const Matrix& b); // �������� ������ 
	friend Matrix operator-(const Matrix& a, const Matrix& b);  // ��������� ������ 

	friend std::ostream& operator << (std::ostream& st, const Matrix& a); // ����� �������
	friend std::istream& operator >> (std::istream& st, Matrix& a); // ���� �������

	void MatrixTransform()
	{
		for (int i = 0; i <= a.size() - 1; i++)
		{
			a[i][a.size()] /= a[i][i];
			if (a[i][i] != 0)
			{
				double c = a[i][i];
				for (int j = 0; j <= a.size() - 1; j++)
				{
					a[i][j] /= (-c);
				}
			}
			a[i][i] = 0;
		}
	}

	Matrix MatrixSimple_Iter_Method(Matrix& X, double epsilon)
	{
		int n = a.size();
		Matrix B(n, n);
		for (int i = 0; i <= n - 1; i++)
		{
			for (int j = 0; j <= n - 1; j++)
			{
				B.a[i][j] = a[i][j];
			}
		}
		Matrix D(n, 1);
		for (int i = 0; i <= n - 1; i++)
		{
			D.a[i][0] = a[i][n];
		}
		double C = B.MatrixNorm() / (1 - B.MatrixNorm()) * ((B * X + D).MatrixNorm() - X.MatrixNorm());
		if (fabs(C) >= epsilon)
		{
			X = B * X + D;
			std::cout << X;
			MatrixSimple_Iter_Method(X, epsilon);
		}
		else
		{
			std::cout << B * X + D;
		}
		return 0;
	}
	
};


double& Matrix::operator () (int i, int j)
// ������������� �������� ������ �������  
{
	if (i < 0 || i > row() || j < 0 || j > col())
		throw "Invalid range";
	return a[i][j];
}

const double& Matrix::operator () (int i, int j) const
// ������������� �������� ������ �������  
{
	if (i < 0 || i > row() || j < 0 || j > col())
		throw "Invalid range";
	return a[i][j];
}

Matrix Matrix::operator () (int i1, int i2, int j1, int j2) const
{
	Matrix b;
	b.a.resize(i2 - i1 + 1);
	for (int i = 0; i < i2 - i1 + 1; ++i)
		b.a[i].resize(j2 - j1 + 1);

	for (int i = i1; i <= i2; ++i)
		copy(a[i].begin() + j1, a[i].begin() + j2 + 1, b.a[i - i1].begin());
	// ��������� copy --  ���������;  2-� �������� -- �������� �� 1 ������ 
	return b;
}

Matrix Matrix::operator* (double x) const // ��������� ������� �� �����
{
	Matrix res = (*this);
	for (int i = 0; i < row(); ++i)
		for (int j = 0; j < col(); ++j)
			res(i, j) *= x;
	return res;
}

Matrix operator*(const Matrix& a, const Matrix& b)
{
	if (a.col() != b.row())
		throw "Multiplication: incorrect sizes";

	Matrix c(a.row(), b.col());

	for (int i = 0; i < a.row(); ++i)
		for (int j = 0; j < b.col(); ++j)
			for (int k = 0; k < a.col(); ++k)
				c(i, j) += a(i, k) * b(k, j);
	return c;
}

Matrix operator+(const Matrix& a, const Matrix& b)
{
	if (a.row() != b.row() || a.col() != b.col())
		throw "incorrect sizes";

	Matrix c(a.row(), a.col());

	for (int i = 0; i < c.row(); ++i)
		for (int j = 0; j < c.col(); ++j)
			c(i, j) = a(i, j) + b(i, j);
	return c;
}

Matrix operator-(const Matrix& a, const Matrix& b)
{
	Matrix tmp = b * (-1);
	return a + tmp;
}

double Matrix::MatrixNorm() const
{
	double max = 0;
	for (int i = 0; i < a.size(); ++i)
	{
		double sum = 0;
		for (int j = 0; j < a[0].size(); ++j)
			sum += fabs(this->a[i][j]);

		if (max < sum)
			max = sum;
	}
	return max;
}

std::ostream& operator << (std::ostream& st, const Matrix& m)
{
	st << std::endl;
	for (int i = 0; i < m.a.size(); ++i)
	{
		for (int j = 0; j < m.a[0].size(); ++j)
			st << std::setw(15) << m(i, j);
		st << std::endl;
	}
	st << std::endl;
	return st;
}

std::istream& operator >> (std::istream& st, Matrix& m)
{
	int r, c;
	st >> r >> c;

	m.a.clear(); // �������� ������� ����������� �������  
	m.a.resize(r);
	for (int i = 0; i < r; ++i)
	{
		m.a[i].resize(c);
		for (int j = 0; j < c; ++j)
			st >> m(i, j);
	}
	return st;
}


int main()
{
	int n = 3;
	Matrix A(n, n + 1);
	Matrix x_0(n, 1), x(n, 1);
	/*
		A(0, 0) = 7;  A(0, 1) = 2;  A(0, 2) = 1;  A(0, 3) = 15;
		A(1, 0) = 4;  A(1, 1) = 9;  A(1, 2) = 1;  A(1, 3) = 26;
		A(2, 0) = 2;  A(2, 1) = 3;  A(2, 2) = 6;  A(2, 3) = 32;
	 */
	x_0(0, 0) = 0;  x_0(1, 0) = 0;  x_0(2, 0) = 0;

	// ����� 1 2 4


	A(0, 0) = 3.278164;  A(0, 1) = 1.046583;  A(0, 2) = -1.378574;  A(0, 3) = -0.527466;
	A(1, 0) = 1.046583;  A(1, 1) = 2.975937;  A(1, 2) = 0.934251;   A(1, 3) = 2.526877;
	A(2, 0) = -1.378574; A(2, 1) = 0.934251;  A(2, 2) = 4.836173;   A(2, 3) = 5.165441;
	// ����� ~  0.1  0.5  1


	std::cout << "x_0: " << std::endl;
	std::cout << x_0 << std::endl;

	A.MatrixTransform();
	std::cout << "H: " << A << std::endl;

	try
	{
		x = A.MatrixSimple_Iter_Method(x_0, 1e-6);
	}

	catch (std::string s)
	{
		std::cout << s << std::endl;
	}

	std::cout << "x: " << std::endl;
	std::cout << x << std::endl;
	return EXIT_SUCCESS;
}