#include "matrix.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <iomanip>

std::mutex mut;

Matrix::Matrix() {
	n_ = 1 + std::rand() % 5;
	m_ = 1 + std::rand() % 5;
	for (auto i = 0; i < n_; i++) {
		std::vector<double> vec;
		for (int j = 0; j < m_; j++) {
			vec.push_back((std::rand() % 3 - 1) / 100.0);
		}
		matrix_.push_back(vec);
	}
}

Matrix::Matrix(int n, int m) {
	n_ = n;
	m_ = m;
	for (auto i = 0; i < n_; i++) {
		std::vector<double> vec;
		for (int j = 0; j < m_; j++) {
			vec.push_back((std::rand() / (double)RAND_MAX) * (2) - 1);
		}
		matrix_.push_back(vec);
	}
}

Matrix::Matrix(const Matrix& matrix) {
	this->n_ = matrix.n_;
	this->m_ = matrix.m_;
	for (auto i = 0; i < n_; i++) {
		std::vector<double> vec;
		for (int j = 0; j < m_; j++) {
			vec.push_back(matrix.matrix_[i][j]);
		}
		matrix_.push_back(vec);
	}
}

void Matrix::getMatrix() {
	for (auto i = 0; i < n_; i++) {
		for (int j = 0; j < m_; j++) {
			std::cout << std::setw(10) << matrix_[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void summ(std::vector<double> A, std::vector<double> B, int num, Matrix& rez) {
	std::vector<double> vec;
	for (int i = 0; i < A.size() && i < B.size(); i++) {
		vec.push_back(A[i] + B[i]);
	}
	mut.lock();
	rez.matrix_[num] = vec;
	mut.unlock();
}

void diff(std::vector<double> A, std::vector<double> B, int num, Matrix& rez) {
	std::vector<double> vec;
	for (int i = 0; i < A.size() && i < B.size(); i++) {
		vec.push_back(A[i] - B[i]);
	}
	mut.lock();
	rez.matrix_[num] = vec;
	mut.unlock();
}

void comp(std::vector<std::vector<double>> A, std::vector<std::vector<double>> B, int num, Matrix& rez) {
	std::vector<double> vec;
	for (int i = 0; i < A.size() && i < B.size(); i++) {
	}
	mut.lock();
	rez.matrix_[num] = vec;
	mut.unlock();
}

void divi(std::vector<int> A, std::vector<int> B, int num, Matrix& rez) {
	std::vector<double> vec;
	for (int i = 0; i < A.size() && i < B.size(); i++) {
		vec.push_back(A[i] / B[i]);
	}
	mut.lock();
	rez.matrix_[num] = vec;
	mut.unlock();
}

Matrix Matrix::operator+(Matrix B) {
	Matrix matrixC(this->n_, this->m_);
	for (int i = 0; i < this->n_ && i < B.n_; i++) {
		std::thread th(summ, this->matrix_[i], B.matrix_[i], i, std::ref(matrixC));
		if (i + 1 == this->n_ || i + 1 == B.n_) {
			th.join();
		}
		else {
			th.detach();
		}
	}
	return matrixC;
}

Matrix Matrix::operator-(Matrix B) {
	Matrix matrixC(this->n_, this->m_);
	for (int i = 0; i < this->n_ && i < B.n_; i++) {
		std::thread th(diff, this->matrix_[i], B.matrix_[i], i, std::ref(matrixC));
		if (i + 1 == this->n_ || i + 1 == B.n_) {
			th.join();
		}
		else {
			th.detach();
		}
	}
	return matrixC;
}

Matrix Matrix::operator*(Matrix B) {
	Matrix matrixC(this->n_, B.m_);
	if (this->m_ == B.n_) {
		for (int i = 0; i < this->n_ && i < B.n_; i++) {
			//std::thread th(comp, this->matrix_, B.matrix_, i, std::ref(matrixC));
			if (i + 1 == this->n_ || i + 1 == B.n_) {
				//th.join();
			}
			else {
				//th.detach();
			}
		}
		return matrixC;
	}
	else {
		std::cout << "Данные матрицы невозможно пперемножить" << std::endl;
		return matrixC;
	}
}

Matrix Matrix::operator/(Matrix B) {
	Matrix matrixC(this->n_, this->m_);
	for (int i = 0; i < this->n_ && i < B.n_; i++) {
		//std::thread th(comp, this->matrix_[i], B.matrix_[i], i, std::ref(matrixC));
		if (i + 1 == this->n_ || i + 1 == B.n_) {
			//th.join();
		}
		else {
			//th.detach();
		}
	}
	return matrixC;
}

void Matrix::operator=(Matrix B) {
	this->n_ = B.n_;
	this->m_ = B.m_;
	for (auto i = 0; i < n_; i++) {
		for (int j = 0; j < m_; j++) {
			this->matrix_[i][j] = B.matrix_[i][j];
		}
	}
}

std::vector<std::vector<double>> Matrix::getmatrix() {
	return this->matrix_;
}

void Matrix::setmatrix(std::vector<double> vec, int num) {
	this->matrix_[num] = vec;
}