// assignment4.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "Matrix.h"

int main()
{
	Matrix matrix1 = Matrix(1, 10, 2);
	cout << "matrix1" << endl;
	cout << matrix1;
	Matrix matrix2 = Matrix(2, 2, 10);
	cout << "matrix2 " << endl;
	cout << matrix2;
	Matrix matrix3 = matrix1 * matrix2;
	Matrix matrix4 = matrix1 * 2;
	Matrix matrix5 = matrix2 / 2;
	Matrix matrix6 = matrix1;
	cout << "matrix3=matrix1*matrix2" << endl;
	cout << matrix3;
	cout << "matrix4=natrix1*2" << endl;
	cout << matrix4;
	cout << "matrix5=matrix2/2" << endl;
	cout << matrix5;
	cout << "matrix6=matrix1" << endl;
	cout << "the refcout of matrix6 is " << matrix6.getRefcount() << endl;
	cout << "using string to create matrix7" << endl;
	Matrix matrix7 = creatMatWithString();
	cout << matrix7;
	
	Matrix matrixList[10000];
	cout << "下面进行refcount原子操作的演示" << endl;
#pragma omp parallel for
	for (int i = 0; i < 10000; i++) {
		matrixList[i] = matrix1;
	}
	cout << matrix1.getRefcount() << endl;;
	
	cout << "using matrix1(1,1) to get matrix1[1][1]" << endl;
	cout << matrix1(1, 1) << endl;
	cout << "using matrix(3,3) to get matrix1[3][2]" << endl;
	cout << matrix1(3, 3) << endl;
	cout << "Test matrix6==matrix1" << endl;
	bool T = matrix1 == matrix6;
	if (T) {
		cout << "True" << endl;
	}
	else {
		cout<<"False"<<endl;
	}
	Matrix matrix8 = matrix3.getSubMatrix(3, 5, 3, 5);
	cout << "matrix8=matrix3[3-5][3-5]" << endl;
	cout << matrix8 << endl;
	
	cout << "matrix9=matrix1[3-5][3-5](展示超限了会怎么样)" << endl;
	Matrix matrix9 = matrix1.getSubMatrix(3, 5, 3, 5);
	cout << matrix9 << endl;

	cout << "用内置字符串初始矩阵（[1,2;3,4]）" << endl;
	string str3 = "[1,2;3,4]";
	Matrix matrix10 = creatMatWithString(str3);
	cout << matrix10 << endl;
	
}