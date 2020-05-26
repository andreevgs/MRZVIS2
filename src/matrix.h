#pragma once
#include "vector"
class Matrix
{
private:
	int m_;
	int n_;
	std::vector<std::vector<double>> matrix_;
public:
	Matrix();
	Matrix(int, int);
	Matrix(const Matrix&);
	friend void summ(std::vector<double>, std::vector<double>, int, Matrix&);
	friend void diff(std::vector<double>, std::vector<double>, int, Matrix&);
	friend void comp(std::vector<std::vector<double>>, std::vector<std::vector<double>>, int, Matrix&);
	friend void divi(std::vector<int>, std::vector<int>, int, Matrix&);
	void getMatrix();
	Matrix operator+(Matrix);
	Matrix operator-(Matrix);
	Matrix operator*(Matrix);
	Matrix operator/(Matrix);
	void operator=(Matrix);
	std::vector<std::vector<double>> getmatrix();
	void setmatrix(std::vector<double>, int);
};

