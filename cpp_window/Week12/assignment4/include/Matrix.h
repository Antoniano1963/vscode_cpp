#include<iostream>
#include<cblas.h>
#include <atomic>
#include<mutex>
#include<string>
using namespace std;
class Matrix {
private:
	mutex *mu;
	int row_num, column_num;
	long size;
	float *matrixdata;
	int *refcount;
public:
	Matrix(int row_num=1,int column_num=1);
	Matrix(float value,int row_num=1, int column_num = 1);
	Matrix(int num);
	Matrix(string str);
	Matrix(int num, float value);
	Matrix(const Matrix &rhs);
	~Matrix();
	Matrix &operator=(const Matrix &rhs);
	friend ostream &operator<< (ostream &os, Matrix &rhs);
	friend Matrix operator+(const Matrix& matrix1, const Matrix &matrix2);
	friend Matrix operator-(const Matrix &matrix1, const Matrix &matrix2);
	friend Matrix operator*(const Matrix &matrix1, const Matrix &matrix2);
	friend Matrix operator*(float mul, const Matrix &matrix2);
	friend Matrix operator*(const Matrix &matrix1, float mul);
	friend Matrix operator/(float mul, const Matrix &matrix2);
	friend Matrix operator/(const Matrix &matrix1, float mul);
	int getRefcount();
	float operator()(int rowNum, int columnNum);
	friend bool operator==(const Matrix &matrix1, const Matrix &matrix2);
	Matrix getSubMatrix(int rowStart, int rowEnd, int columnStart, int columnEnd);
};
Matrix creatMatWithString();