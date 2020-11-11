#include<iostream>
#include <chrono>
#include <immintrin.h>
#include <omp.h>
#include<string>
#include<cblas.h>
using namespace std;

struct Matrix {
	long row_num, column_num;
	long row_num_true, column_num_true;
	long step;
	float **matrix;
	/*
public:
	~Matrix() {
		for (int i = 0; i < row_num; i++) {
			delete[] matrix[i];
		}
	}
	*/
};

bool testNum(string str) {
	if (str.length() < 1) {
		return false;
	}
	int num = 0;
	if (str.at(0) == '-') {
		num = 1;
	}
	int count = 0;
	for (; num < str.length(); num++) {
		if (str.at(num) <= '9' || str.at(num) >= '0' || str.at(num) == '.') {
			if (str.at(num) == '.') {
				count++;
			}
		}
		else {
			return false;
		}
	}
	if (count > 1) {
		return false;
	}
	return true;
}

bool testMatrix(string str) {
	int test = 0;
	int i = 0;
	int length = str.length();
	if (str.at(0) != '[') {
		cout << "The expression should begin with [" << endl;
		return false;
	}
	while (i < length) {
		if (test == 0) {
			i++;
			if (((str.at(i) <= '9'&&str.at(i) >= '0') || str.at(i) == '-') && i < length) {
				test = 1;
			}
			else {
				cout << "The character [ should be followed with a float" << endl;
				return false;
			}
		}
		else if (test == 1) {
			string str1 = "";
			while (((str.at(i) <= '9'&&str.at(i) >= '0') || str.at(i) == '.' || str.at(i) == '-') && i < length) {
				str1 += str.at(i);
				i++;
			}
			if (!testNum(str1)) {
				cout << "The type of the float is wrong" << endl;
				return false;
			}
			if (str.at(i) == ',') {
				test = 2;
			}
			else if (str.at(i) == ';') {
				test = 3;
			}
			else if (str.at(i) == ']') {
				if (i = length - 1) {
					return true;
				}
				cout << "The expression should end with ]" << endl;
				return false;
			}
			else {
				cout << "The expression contain illegal character" << endl;
				return false;
			}
		}
		else if (test == 2) {
			i++;
			if (((str.at(i) <= '9'&&str.at(i) >= '0') || str.at(i) == '-') && i < length) {
				test = 1;
			}
			else {
				cout << "The character , should be followed with a float" << endl;
				return false;
			}
		}
		else if (test == 3) {
			i++;
			if (((str.at(i) <= '9'&&str.at(i) >= '0') || str.at(i) == '-') && i < length) {
				test = 1;
			}
			else {
				cout << "The character ; should be followed with a float" << endl;
				return false;
			}
		}
	}
}

void showMatrix(Matrix matrix) {
	for (int i = 0; i < matrix.row_num_true; i++) {
		for (int j = 0; j < matrix.column_num_true; j++) {
			cout << matrix.matrix[i][j] << ' ';
		}
		cout << endl;
	}
}

float getMatrixNum(Matrix matrix, int rowNum, int columnNum) {
	if (rowNum < matrix.row_num_true&&columnNum < matrix.column_num_true) {
		return matrix.matrix[rowNum][columnNum];
	}
	else {
		cout << "Out of Bound" << endl;
		return 0;
	}
}

int getrowNum(string str) {
	int length = str.length();
	int result = 1;
	for (int i = 0; i < length; i++) {
		if (str.at(i) == ';') {
			result++;
		}
	}
	return result;
}

int testSameLength(string str,int rowNum) {
	int n = 0;
	int length = str.length();
	int lengthNum = 0;
	if (rowNum > 1) {
		for (int i = 0; i < length; i++) {
			if (str.at(i) == ';') {
				if (lengthNum == 0) {
					lengthNum = n + 1;
					n = 0;
				}
				else {
					if (lengthNum != n + 1) {
						return -1;
					}
					else {
						n = 0;
					}
				}
			}
			if (str.at(i) == ',') {
				n++;
			}
		}

		if (lengthNum != n + 1) {
			return -1;
		}
	}
	else {
		for (int i = 0; i < length; i++) {
			if (str.at(i) == ',') {
				n++;
			}
		}
		lengthNum = n + 1;
	}
	return lengthNum;
}

Matrix soToMatrix(string str) {
	int rowNum = getrowNum(str);
	int columnNum = testSameLength(str,rowNum);
	float **p = new float *[rowNum];
	for (int i = 0; i < rowNum; i++) {
		p[i] = new float[columnNum];
	}
	int i = 1;
	int k = 0;
	int j = 0;
	int length = str.length();
	while (i < length) {
		string str0 = "";
		while (i < length&&str.at(i) != ',' && str.at(i) != ';'&&str.at(i)!=']') {
			str0 += str.at(i);
			i++;
		}
		p[k][j] = stof(str0);
		if (str.at(i) == ',') {
			j++;
			i++;
		}
		else if (str.at(i) == ';') {
			k++;
			j = 0;
			i++;
		}
		else {
			break;
		}
	}
	return Matrix{ rowNum, columnNum, rowNum, columnNum, 1, p };

}

float **creatMatrix(int row_num, int column_num) {
	float **p = new float *[row_num];
	for (int i = 0; i < row_num; i++) {
		p[i] = new float[column_num];
	}
	return p;
}

Matrix creatMatrixwithMod(int row_num, int column_num) {
	int row_num_mod, column_num_mod;
	if (row_num % 8 != 0) {
		row_num_mod = (row_num / 8 + 1) * 8;
	}
	else {
		row_num_mod = row_num;
	}
	if (column_num % 8 != 0) {
		column_num_mod = (column_num / 8 + 1) * 8;
	}
	else {
		column_num_mod = column_num;
	}
	float **p = new float *[row_num_mod];
	for (int i = 0; i < row_num_mod; i++) {
		p[i] = new float[column_num_mod];
	}
	for (int i = 0; i < row_num_mod; i++) {
		for (int j = 0; j < column_num_mod; j++) {
			p[i][j] = 0;
		}
	}
	Matrix matrix = { row_num_mod, column_num_mod, row_num, column_num, 1, p };
	return matrix;
}

float **creatMatrixwithNum(int row_num, int column_num, float num) {
	float **p = new float *[row_num];
	for (int i = 0; i < row_num; i++) {
		p[i] = new float[column_num];
	}
	for (int i = 0; i < row_num; i++) {
		for (int j = 0; j < column_num; j++) {
			p[i][j] = num;
		}
	}
	return p;
}

Matrix creatMatrixwithNumwithMod(int row_num, int column_num, float num) {
	int row_num_mod, column_num_mod;
	if (row_num % 8 != 0) {
		row_num_mod = (row_num / 8 + 1) * 8;
	}
	else {
		row_num_mod = row_num;
	}
	if (column_num % 8 != 0) {
		column_num_mod = (column_num / 8 + 1) * 8;
	}
	else {
		column_num_mod = column_num;
	}
	float **p = new float *[row_num_mod];
	for (int i = 0; i < row_num_mod; i++) {
		p[i] = new float[column_num_mod];
	}
	for (int i = 0; i < row_num_mod; i++) {
		for (int j = 0; j < column_num_mod; j++) {
			if (i < row_num&&j < column_num) {
				p[i][j] = num;
			}
			else {
				p[i][j] = 0;
			}
		}
	}
	Matrix matrix = { row_num_mod, column_num_mod, row_num, column_num, 1, p };
	return matrix;
}

Matrix matrixDot1(Matrix matrix1, Matrix matrix2) {
	int m = matrix1.row_num;
	int n = matrix2.column_num;
	if (matrix1.column_num != matrix2.row_num) {
		std::cout << "The column of matrix1 is not equal to the row of matrix 2" << endl;
		Matrix matrix3 = { 1, 1, 1, 1,1,creatMatrixwithNum(1, 1, 0) };
		return matrix3;
	}
	else {
		int k = matrix1.column_num;
		Matrix matrix3 = { m, n,m ,n,1,creatMatrixwithNum(m, n, 0) };
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				for (int p = 0; p < k; p++) {
					matrix3.matrix[i][j] += matrix1.matrix[i][p] * matrix2.matrix[p][j];
				}
			}
		}
		return matrix3;
	}
}

void Addmatrix1x4(int k, Matrix matrix1, Matrix matrix2, Matrix &matrix3, int i, int j) {
	//最开始优化过的1*4运算，使用了四个浮点寄存器来增加效率
	//由于矩阵由行储存，所以在矩阵1上使用了指针的方法减少内存访问的开销
	register float m3_00, m3_10, m3_20, m3_30, m2_p0;
	m3_00 = 0.0;
	m3_10 = 0.0;
	m3_20 = 0.0;
	m3_30 = 0.0;
	float *m1p0 = &(matrix1.matrix[i][0]);
	float *m1p1 = &(matrix1.matrix[i + 1][0]);
	float *m1p2 = &(matrix1.matrix[i + 2][0]);
	float *m1p3 = &(matrix1.matrix[i + 3][0]);


	for (int p = 0; p < k; p++) {
		m2_p0 = matrix2.matrix[p][j];
		m3_00 += m2_p0 * *m1p0++;
		m3_10 += m2_p0 * *m1p1++;
		m3_20 += m2_p0 * *m1p2++;
		m3_30 += m2_p0 * *m1p3++;
	}
	matrix3.matrix[i][j] += m3_00;
	matrix3.matrix[i + 1][j] += m3_10;
	matrix3.matrix[i + 2][j] += m3_20;
	matrix3.matrix[i + 3][j] += m3_30;
}

void Addmatrix4x4T(int k, Matrix matrix1, Matrix matrix2, Matrix &matrix3, int i, int j) {
	//使用4一次星计算16个位置的数据
	register float m3_00, m3_10, m3_20, m3_30, m3_01, m3_11, m3_21, m3_31, m3_02, m3_12, m3_22, m3_32, m3_03, m3_13, m3_23, m3_33;
	m3_00 = 0.0;
	m3_10 = 0.0;
	m3_20 = 0.0;
	m3_30 = 0.0;
	m3_01 = 0.0;
	m3_11 = 0.0;
	m3_21 = 0.0;
	m3_31 = 0.0;
	m3_02 = 0.0;
	m3_12 = 0.0;
	m3_22 = 0.0;
	m3_32 = 0.0;
	m3_03 = 0.0;
	m3_13 = 0.0;
	m3_23 = 0.0;
	m3_33 = 0.0;
	float *m1p0 = &(matrix1.matrix[i][0]);
	float *m1p1 = &(matrix1.matrix[i + 1][0]);
	float *m1p2 = &(matrix1.matrix[i + 2][0]);
	float *m1p3 = &(matrix1.matrix[i + 3][0]);
	float *m2p0 = &(matrix2.matrix[j][0]);
	float *m2p1 = &(matrix2.matrix[j + 1][0]);
	float *m2p2 = &(matrix2.matrix[j + 2][0]);
	float *m2p3 = &(matrix2.matrix[j + 3][0]);
	for (int p = 0; p < k; p++) {
		m3_00 += *m2p0  * *m1p0;
		m3_10 += *m2p0  * *m1p1;
		m3_20 += *m2p0  * *m1p2;
		m3_30 += *(m2p0++)  * *m1p3;
		m3_01 += *m2p1  * *m1p0;
		m3_11 += *m2p1  * *m1p1;
		m3_21 += *m2p1  * *m1p2;
		m3_31 += *(m2p1++)  * *m1p3;
		m3_02 += *m2p2  * *m1p0;
		m3_12 += *m2p2  * *m1p1;
		m3_22 += *m2p2  * *m1p2;
		m3_32 += *(m2p2++)  * *m1p3;
		m3_03 += *m2p3  * *m1p0++;
		m3_13 += *m2p3  * *m1p1++;
		m3_23 += *m2p3  * *m1p2++;
		m3_33 += *(m2p3++)  * *m1p3++;
	}
	matrix3.matrix[i][j] += m3_00;
	matrix3.matrix[i + 1][j] += m3_10;
	matrix3.matrix[i + 2][j] += m3_20;
	matrix3.matrix[i + 3][j] += m3_30;
	matrix3.matrix[i][j + 1] += m3_01;
	matrix3.matrix[i + 1][j + 1] += m3_11;
	matrix3.matrix[i + 2][j + 1] += m3_21;
	matrix3.matrix[i + 3][j + 1] += m3_31;
	matrix3.matrix[i][j + 2] += m3_02;
	matrix3.matrix[i + 1][j + 2] += m3_12;
	matrix3.matrix[i + 2][j + 2] += m3_22;
	matrix3.matrix[i + 3][j + 2] += m3_32;
	matrix3.matrix[i][j + 3] += m3_03;
	matrix3.matrix[i + 1][j + 3] += m3_13;
	matrix3.matrix[i + 2][j + 3] += m3_23;
	matrix3.matrix[i + 3][j + 3] += m3_33;

}

void multi6kernel(Matrix c, Matrix matrix1, Matrix matrix2, int i, int j, int k) {
	//使用16个寄存器进行地4*4矩阵乘法运算，matrix是根据行储存的，即同一行数据的地址是连续的.
	//为了AVX2 8位float寄存器的使用，matrix2经过转置，来使得要被操作的地址是连续的
	float sum[8] = { 0 };
	__m256 c00, c01, c02, c03, c10, c11, c12, c13, c20, c21, c22, c23, c30, c31, c32, c33, a0, a1, a2, a3, b0, b1, b2, b3;
	c00 = _mm256_setzero_ps();
	c01 = _mm256_setzero_ps();
	c02 = _mm256_setzero_ps();
	c03 = _mm256_setzero_ps();
	c10 = _mm256_setzero_ps();
	c11 = _mm256_setzero_ps();
	c12 = _mm256_setzero_ps();
	c13 = _mm256_setzero_ps();
	c20 = _mm256_setzero_ps();
	c21 = _mm256_setzero_ps();
	c22 = _mm256_setzero_ps();
	c23 = _mm256_setzero_ps();
	c30 = _mm256_setzero_ps();
	c31 = _mm256_setzero_ps();
	c32 = _mm256_setzero_ps();
	c33 = _mm256_setzero_ps();
	float *m1p0 = &(matrix1.matrix[i][0]);
	float *m1p1 = &(matrix1.matrix[i + 1][0]);
	float *m1p2 = &(matrix1.matrix[i + 2][0]);
	float *m1p3 = &(matrix1.matrix[i + 3][0]);
	float *m2p0 = &(matrix2.matrix[j][0]);
	float *m2p1 = &(matrix2.matrix[j + 1][0]);
	float *m2p2 = &(matrix2.matrix[j + 2][0]);
	float *m2p3 = &(matrix2.matrix[j + 3][0]);
	int p = 0;
	for (; p < k ; p += 8)
	{
		a0 = _mm256_load_ps(m1p0 + p);
		a1 = _mm256_load_ps(m1p1 + p);
		a2 = _mm256_load_ps(m1p2 + p);
		a3 = _mm256_load_ps(m1p3 + p);
		b0 = _mm256_load_ps(m2p0 + p);
		b1 = _mm256_load_ps(m2p1 + p);
		b2 = _mm256_load_ps(m2p2 + p);
		b3 = _mm256_load_ps(m2p3 + p);
		c00 = _mm256_add_ps(c00, _mm256_mul_ps(a0, b0));
		c01 = _mm256_add_ps(c01, _mm256_mul_ps(a0, b1));
		c02 = _mm256_add_ps(c02, _mm256_mul_ps(a0, b2));
		c03 = _mm256_add_ps(c03, _mm256_mul_ps(a0, b3));
		c10 = _mm256_add_ps(c10, _mm256_mul_ps(a1, b0));
		c11 = _mm256_add_ps(c11, _mm256_mul_ps(a1, b1));
		c12 = _mm256_add_ps(c12, _mm256_mul_ps(a1, b2));
		c13 = _mm256_add_ps(c13, _mm256_mul_ps(a1, b3));
		c20 = _mm256_add_ps(c20, _mm256_mul_ps(a2, b0));
		c21 = _mm256_add_ps(c21, _mm256_mul_ps(a2, b1));
		c22 = _mm256_add_ps(c22, _mm256_mul_ps(a2, b2));
		c23 = _mm256_add_ps(c23, _mm256_mul_ps(a2, b3));
		c30 = _mm256_add_ps(c30, _mm256_mul_ps(a3, b0));
		c31 = _mm256_add_ps(c31, _mm256_mul_ps(a3, b1));
		c32 = _mm256_add_ps(c32, _mm256_mul_ps(a3, b2));
		c33 = _mm256_add_ps(c33, _mm256_mul_ps(a3, b3));
	}
	_mm256_store_ps(sum, c00);
	c.matrix[i][j] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c01);
	c.matrix[i][j + 1] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c02);
	c.matrix[i][j + 2] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c03);
	c.matrix[i][j + 3] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c10);
	c.matrix[i + 1][j] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c11);
	c.matrix[i + 1][j + 1] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c12);
	c.matrix[i + 1][j + 2] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c13);
	c.matrix[i + 1][j + 3] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c20);
	c.matrix[i + 2][j] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c21);
	c.matrix[i + 2][j + 1] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c22);
	c.matrix[i + 2][j + 2] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c23);
	c.matrix[i + 2][j + 3] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c30);
	c.matrix[i + 3][j] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c31);
	c.matrix[i + 3][j + 1] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c32);
	c.matrix[i + 3][j + 2] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c33);
	c.matrix[i + 3][j + 3] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];

}

void multi6kernel2(Matrix c, Matrix matrix1, float *m2p0, float *m2p1, float *m2p2, float *m2p3, int i, int j, int k) {
	//同为使用了AVX2指令集的4*4区块运算，与之不同的是，参与运算的四个matrix2变量使用了指针，在进入函数之前便进入连续空间单独储存
	//经过预热，效率相对于原版有了10%左右的提升
	float sum[8] = { 0 };
	__m256 c00, c01, c02, c03, c10, c11, c12, c13, c20, c21, c22, c23, c30, c31, c32, c33, a0, a1, a2, a3, b0, b1, b2, b3;
	c00 = _mm256_setzero_ps();
	c01 = _mm256_setzero_ps();
	c02 = _mm256_setzero_ps();
	c03 = _mm256_setzero_ps();
	c10 = _mm256_setzero_ps();
	c11 = _mm256_setzero_ps();
	c12 = _mm256_setzero_ps();
	c13 = _mm256_setzero_ps();
	c20 = _mm256_setzero_ps();
	c21 = _mm256_setzero_ps();
	c22 = _mm256_setzero_ps();
	c23 = _mm256_setzero_ps();
	c30 = _mm256_setzero_ps();
	c31 = _mm256_setzero_ps();
	c32 = _mm256_setzero_ps();
	c33 = _mm256_setzero_ps();
	float *m1p0 = &(matrix1.matrix[i][0]);
	float *m1p1 = &(matrix1.matrix[i + 1][0]);
	float *m1p2 = &(matrix1.matrix[i + 2][0]);
	float *m1p3 = &(matrix1.matrix[i + 3][0]);
	int p = 0;
	for (; p < k ; p += 8)
	{
		a0 = _mm256_load_ps(m1p0 + p);
		a1 = _mm256_load_ps(m1p1 + p);
		a2 = _mm256_load_ps(m1p2 + p);
		a3 = _mm256_load_ps(m1p3 + p);
		b0 = _mm256_load_ps(m2p0 + p);
		b1 = _mm256_load_ps(m2p1 + p);
		b2 = _mm256_load_ps(m2p2 + p);
		b3 = _mm256_load_ps(m2p3 + p);
		c00 = _mm256_add_ps(c00, _mm256_mul_ps(a0, b0));
		c01 = _mm256_add_ps(c01, _mm256_mul_ps(a0, b1));
		c02 = _mm256_add_ps(c02, _mm256_mul_ps(a0, b2));
		c03 = _mm256_add_ps(c03, _mm256_mul_ps(a0, b3));
		c10 = _mm256_add_ps(c10, _mm256_mul_ps(a1, b0));
		c11 = _mm256_add_ps(c11, _mm256_mul_ps(a1, b1));
		c12 = _mm256_add_ps(c12, _mm256_mul_ps(a1, b2));
		c13 = _mm256_add_ps(c13, _mm256_mul_ps(a1, b3));
		c20 = _mm256_add_ps(c20, _mm256_mul_ps(a2, b0));
		c21 = _mm256_add_ps(c21, _mm256_mul_ps(a2, b1));
		c22 = _mm256_add_ps(c22, _mm256_mul_ps(a2, b2));
		c23 = _mm256_add_ps(c23, _mm256_mul_ps(a2, b3));
		c30 = _mm256_add_ps(c30, _mm256_mul_ps(a3, b0));
		c31 = _mm256_add_ps(c31, _mm256_mul_ps(a3, b1));
		c32 = _mm256_add_ps(c32, _mm256_mul_ps(a3, b2));
		c33 = _mm256_add_ps(c33, _mm256_mul_ps(a3, b3));
	}
	_mm256_store_ps(sum, c00);
	c.matrix[i][j] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c01);
	c.matrix[i][j + 1] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c02);
	c.matrix[i][j + 2] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c03);
	c.matrix[i][j + 3] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c10);
	c.matrix[i + 1][j] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c11);
	c.matrix[i + 1][j + 1] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c12);
	c.matrix[i + 1][j + 2] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c13);
	c.matrix[i + 1][j + 3] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c20);
	c.matrix[i + 2][j] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c21);
	c.matrix[i + 2][j + 1] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c22);
	c.matrix[i + 2][j + 2] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c23);
	c.matrix[i + 2][j + 3] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c30);
	c.matrix[i + 3][j] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c31);
	c.matrix[i + 3][j + 1] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c32);
	c.matrix[i + 3][j + 2] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
	_mm256_store_ps(sum, c33);
	c.matrix[i + 3][j + 3] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
}

void multi6kernel3(Matrix c, Matrix matrix1, Matrix matrix2, int i, int j, int k) {
	//使用16个寄存器进行地4*4矩阵乘法运算，matrix是根据行储存的，即同一行数据的地址是连续的.
	//为了AVX2 8位float寄存器的使用，matrix2经过转置，来使得要被操作的地址是连续的
	float sum[8] = { 0 };
	__m256 c00, c01, c02, c03, c04, c05, c06, c07, a0, a1, a2, a3, a4,a5, a6, a7,b1;
	c00 = _mm256_setzero_ps();
	c01 = _mm256_setzero_ps();
	c02 = _mm256_setzero_ps();
	c03 = _mm256_setzero_ps();
	c04 = _mm256_setzero_ps();
	c05 = _mm256_setzero_ps();
	c06 = _mm256_setzero_ps();
	c07 = _mm256_setzero_ps();
	float *m1p0 = &(matrix1.matrix[i][0]);
	float *m1p1 = &(matrix1.matrix[i + 1][0]);
	float *m1p2 = &(matrix1.matrix[i + 2][0]);
	float *m1p3 = &(matrix1.matrix[i + 3][0]);
	float *m1p4 = &(matrix1.matrix[i+4][0]);
	float *m1p5 = &(matrix1.matrix[i + 5][0]);
	float *m1p6 = &(matrix1.matrix[i + 6][0]);
	float *m1p7 = &(matrix1.matrix[i + 7][0]);
	int p = 0;
	for (; p < k; p ++)
	{
		a0 = _mm256_set1_ps(*(m1p0 + i));
		a1 = _mm256_set1_ps(*(m1p1 + i));
		a2 = _mm256_set1_ps(*(m1p2 + i));
		a3 = _mm256_set1_ps(*(m1p3 + i));
		a4 = _mm256_set1_ps(*(m1p4 + i));
		a5 = _mm256_set1_ps(*(m1p5 + i));
		a6 = _mm256_set1_ps(*(m1p6 + i));
		a7 = _mm256_set1_ps(*(m1p7 + i));
		b1 = _mm256_load_ps(&matrix2.matrix[k][j]);
		c00 = _mm256_add_ps(c00, _mm256_mul_ps(a0, b1));
		c01 = _mm256_add_ps(c01, _mm256_mul_ps(a1, b1));
		c02 = _mm256_add_ps(c02, _mm256_mul_ps(a2, b1));
		c03 = _mm256_add_ps(c03, _mm256_mul_ps(a3, b1));
		c04 = _mm256_add_ps(c04, _mm256_mul_ps(a4, b1));
		c05 = _mm256_add_ps(c05, _mm256_mul_ps(a5, b1));
		c06 = _mm256_add_ps(c06, _mm256_mul_ps(a6, b1));
		c07 = _mm256_add_ps(c07, _mm256_mul_ps(a7, b1));
	}
	_mm256_store_ps(&c.matrix[i][j], c00);
	_mm256_store_ps(&c.matrix[i+1][j], c01);
	_mm256_store_ps(&c.matrix[i+2][j], c02);
	_mm256_store_ps(&c.matrix[i+3][j], c03);
	_mm256_store_ps(&c.matrix[i+4][j], c04);
	_mm256_store_ps(&c.matrix[i+5][j], c05);
	_mm256_store_ps(&c.matrix[i+6][j], c06);
	_mm256_store_ps(&c.matrix[i+7][j], c07);
}

Matrix matrixDot2(Matrix matrix1, Matrix matrix2)
//矩阵点乘的第二版，因为矩阵是行优先储存，所以改变了顺序
{
	int m = matrix1.row_num;
	int n = matrix2.column_num;
	if (matrix1.column_num != matrix2.row_num) {
		std::cout << "The column of matrix1 is not equal to the row of matrix 2" << endl;
		Matrix matrix3 = { 1, 1, 1,1 ,1,creatMatrixwithNum(1, 1, 0) };
		return matrix3;
	}
	else {
		int k = matrix1.column_num;
		Matrix matrix3 = { m, n, m,n,1, creatMatrixwithNum(m, n, 0) };
		for (int j = 0; j < n; j++) {
			for (int i = 0; i < m; i++) {
				for (int p = 0; p < k; p++) {
					matrix3.matrix[i][j] += matrix1.matrix[i][p] * matrix2.matrix[p][j];
				}
			}
		}
		return matrix3;
	}
}

Matrix matrixDot3(Matrix matrix1, Matrix matrix2) {
	//进行1*4矩阵操作的函数
	int m = matrix1.row_num;
	int n = matrix2.column_num;
	if (matrix1.column_num != matrix2.row_num) {
		std::cout << "The column of matrix1 is not equal to the row of matrix 2" << endl;
		Matrix matrix3 = { 1, 1, 1,1,1, creatMatrixwithNum(1, 1, 0) };
		return matrix3;
	}
	else {
		int k = matrix1.column_num;
		Matrix matrix3 = { m, n, m,n,1, creatMatrixwithNum(m, n, 0) };
		for (int i = 0; i < m; i += 4) {
			for (int j = 0; j < n; j++) {
				Addmatrix1x4(k, matrix1, matrix2, matrix3, i, j);
			}
		}
		return matrix3;
	}
}

Matrix matrixDot4(Matrix matrix1, Matrix matrix2) {
	//进行4*4矩阵操作的函数，由于是行优先储存，所以矩阵2经过了转置
	int m = matrix1.row_num;
	int n = matrix2.column_num;
	if (matrix1.column_num != matrix2.row_num) {
		std::cout << "The column of matrix1 is not equal to the row of matrix 2" << endl;
		Matrix matrix3 = { 1, 1, 1,1,1, creatMatrixwithNum(1, 1, 0) };
		return matrix3;
	}
	else {
		Matrix matrix4 = { matrix2.column_num, matrix2.row_num, matrix2.column_num,matrix2.row_num,1, creatMatrixwithNum(matrix2.column_num, matrix2.row_num, 0) };
		for (int i = 0; i < matrix2.row_num; i++) {
			for (int j = 0; j < matrix2.column_num; j++) {
				matrix4.matrix[j][i] = matrix2.matrix[i][j];
			}
		}
		int k = matrix1.column_num;
		Matrix matrix3 = { m, n, m,n,1, creatMatrixwithNum(m, n, 0) };
#pragma omp parallel for
		for (int i = 0; i < m; i += 4) {
			for (int j = 0; j < n; j += 4) {
				Addmatrix4x4T(k, matrix1, matrix4, matrix3, i, j);
			}
		}
		return matrix3;
	}
}

Matrix matrixDot5(Matrix matrix1, Matrix matrix2) {
	//使用寄存器进行4*4矩阵乘法的第一次尝试
	int m = matrix1.row_num;
	int n = matrix2.column_num;
	if (matrix1.column_num != matrix2.row_num) {
		std::cout << "The column of matrix1 is not equal to the row of matrix 2" << endl;
		Matrix matrix3 = { 1, 1, 1,1,1, creatMatrixwithNum(1, 1, 0) };
		return matrix3;
	}
	else {
		Matrix matrix4 = { matrix2.column_num, matrix2.row_num, matrix2.column_num,matrix2.row_num,1, creatMatrixwithNum(matrix2.column_num, matrix2.row_num, 0) };
		for (int i = 0; i < matrix2.row_num; i++) {
			for (int j = 0; j < matrix2.column_num; j++) {
				matrix4.matrix[j][i] = matrix2.matrix[i][j];
			}
		}
		int k = matrix1.column_num;
		Matrix matrix3 = { m, n, m,n,1, creatMatrixwithNum(m, n, 0) };
#pragma omp parallel for
		for (int i = 0; i < m; i += 4) {
			for (int j = 0; j < n; j += 4) {
				multi6kernel(matrix3, matrix1, matrix4, i, j, k);
			}
		}
		return matrix3;
	}
}

Matrix matrixDot6(Matrix matrix1, Matrix matrix2) {
	int m = matrix1.row_num;
	int n = matrix2.column_num;
	if (matrix1.column_num != matrix2.row_num) {
		std::cout << "The column of matrix1 is not equal to the row of matrix 2" << endl;
		Matrix matrix3 = { 1, 1, 1,1,1, creatMatrixwithNum(1, 1, 0) };
		return matrix3;
	}
	else {
		Matrix matrix3 = { m, n, m,n,1, creatMatrixwithNum(m, n, 0) };
		int k = matrix1.column_num;
		float *vector0 = new float[k];
		float *vector1 = new float[k];
		float *vector2 = new float[k];
		float *vector3 = new float[k];
#pragma omp parallel for
		for (int j = 0; j < n; j += 4) {
			//将矩阵二进行转置，把要进行操作的四个向量放入连续空间中，并且对要进行计算的部分进行预热
			for (int p = 0; p < k; p++) {
				vector0[p] = matrix2.matrix[p][j];
				vector1[p] = matrix2.matrix[p][j + 1];
				vector2[p] = matrix2.matrix[p][j + 2];
				vector3[p] = matrix2.matrix[p][j + 3];
			}
			for (int i = 0; i < m - 4; i += 4) {
				multi6kernel2(matrix3, matrix1, vector0, vector1, vector2, vector3, i, j, k);
			}
		}
		cout << endl;
		return matrix3;
	}
}

Matrix matrixDot7(Matrix matrix1, Matrix matrix2) {
	int m = matrix1.row_num;
	int n = matrix2.column_num;
	if (matrix1.column_num != matrix2.row_num) {
		std::cout << "The column of matrix1 is not equal to the row of matrix 2" << endl;
		Matrix matrix3 = { 1, 1, 1,1,1, creatMatrixwithNum(1, 1, 0) };
		return matrix3;
	}
	else {
		Matrix matrix3 = { m, n, m,n,1, creatMatrixwithNum(m, n, 0) };
		int k = matrix1.column_num;
		float *vector0 = new float[k];
		float *vector1 = new float[k];
		float *vector2 = new float[k];
		float *vector3 = new float[k];
#pragma omp parallel for
		for (int j = 0; j < n; j += 8) {
			//将矩阵二进行转置，把要进行操作的四个向量放入连续空间中，并且对要进行计算的部分进行预热
			for (int i = 0; i < m ; i += 8) {
				multi6kernel3(matrix3, matrix1, matrix2, i, j, k);
			}
		}
		cout << endl;
		return matrix3;
	}
}

int main() {
	while (true) {
		cout << "input 0 to test the normal matrix Dot, input 1 to test the time cost of two big matrix Dot: ";
		string str0;
		cin >> str0;
		if (str0.length() > 1) {
			cout << "You input a wrong experssion" << endl;
		}
		else {
			if (str0.at(0) == '0') {
				cout << "Enter your first Matrix([1,2;3,4]): ";
				string str1;
				cin >> str1;
				cout << "Enter your second Matrix: ";
				string str2;
				cin >> str2;
				if (testMatrix(str1) && testMatrix(str2)) {
					int num1 = getrowNum(str1);
					int num2 = getrowNum(str2);
					if (num1 > 1) {
						num1 = testSameLength(str1,num1);
					}
					if (num2 > 1) {
						num2 = testSameLength(str2,num2);
					}
					if (num1 > 0 && num2 > 0) {
						Matrix matrix1 = soToMatrix(str1);
						Matrix matrix2 = soToMatrix(str2);
						Matrix matrix3 = matrixDot1(matrix1, matrix2);
						cout << "Matirx 1 " << endl;
						showMatrix(matrix1);
						cout << "Matrix 2 " << endl;
						showMatrix(matrix2);
						cout << "Matrix 3 " << endl;
						showMatrix(matrix3);
					}
					else {
						cout << "矩阵每行元素个数不相同" << endl;
						
					}
				}
				else {
					cout << "输入的矩阵格式错误" << endl;
				}
			}
			else if (str0.at(0) == '1') {
				cout << "Enter a number to size your matrix(int)";
				string num;
				cin >> num;
				if (testNum(num)) {
					int n = stoi(num);
					cout << "The number n is " << n << endl;
					Matrix matrix0 = { 10000, 10000, 10000,10000,1, creatMatrixwithNum(10000, 10000, 1) };
					Matrix matrix1 = { 10000, 10000, 10000,10000,2, creatMatrixwithNum(10000, 10000, 2) };

					Matrix matrix3, matrix4, matrix5, matrix6;
					matrix3 = creatMatrixwithNumwithMod(n, n, 1);
					matrix4 = creatMatrixwithNumwithMod(n, n, 2);
					auto start = std::chrono::steady_clock::now();
					matrix5 = matrixDot1(matrix3, matrix4);
					auto end = std::chrono::steady_clock::now();
					auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
					std::cout << ", duration(基本乘法) = " << duration << std::endl;

					start = std::chrono::steady_clock::now();
					matrix5 = matrixDot2(matrix3, matrix4);
					end = std::chrono::steady_clock::now();
					duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
					std::cout << ", duration2(i j顺序调换) = " << duration << std::endl;

					start = std::chrono::steady_clock::now();
					matrix5 = matrixDot3(matrix3, matrix4);
					end = std::chrono::steady_clock::now();
					duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
					std::cout << ", duration3(1*4寄存器) = " << duration;
					std::cout << "  matrix5[0][0] " << matrix5.matrix[0][0] << endl;

					start = std::chrono::steady_clock::now();
					matrix5 = matrixDot4(matrix3, matrix4);
					end = std::chrono::steady_clock::now();
					duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
					std::cout << ", duration4(4*4寄存器) = " << duration << std::endl;
					std::cout << matrix5.matrix[0][30] << endl;
					
						start = std::chrono::steady_clock::now();
						matrix6 = matrixDot4(matrix0, matrix1);
						end = std::chrono::steady_clock::now();
						duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
						std::cout << ", duration5(4*4寄存器) = " << duration << std::endl;
						std::cout << matrix6.matrix[0][30]<<endl;
					
					start = std::chrono::steady_clock::now();
					matrix6 = matrixDot5(matrix0, matrix1);
					end = std::chrono::steady_clock::now();
					duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
					std::cout << ", duration6(AVX2寄存器) = " << duration << std::endl;
					std::cout << matrix6.matrix[0][30] << endl;

					start = std::chrono::steady_clock::now();
					matrix6 = matrixDot6(matrix0, matrix1);
					end = std::chrono::steady_clock::now();
					duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
					std::cout << ", duration7(AVX2寄存器预热) = " << duration << std::endl;
					std::cout << matrix6.matrix[0][30] << endl;
					float *matrix00 = new float[100000000];
					float *matrix01 = new float[100000000];
					float *matrix02 = new float[100000000];
					for (int i = 0; i < 100000000; i++) {
						matrix00[i] = 1;
						matrix01[i] = 2;
					}
					
					start = std::chrono::steady_clock::now();
					cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 10000, 10000, 10000, 1.0, matrix00, 10000, matrix01, 10000, 0.0, matrix02, 10000);
					end = std::chrono::steady_clock::now();
					duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
					std::cout << ", duration7(openblas库) = " << duration << std::endl;
					std::cout << matrix02[30] << endl;
					
					
				}
			}
			else {
				cout << "You input a wrong number" << endl;
			}
		}

	}
}

