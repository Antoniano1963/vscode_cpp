#include<iostream>
#include <chrono>
using namespace std;

struct Matrix {
	long row_num, column_num;
	long step;
	float **matrix;
};

float **creatMatrix(int row_num, int column_num) {
	float **p = new float *[row_num];
	for (int i = 0; i < row_num; i++) {
		p[i] = new float[column_num];
	}
	return p;
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

Matrix matrixDot1(Matrix matrix1, Matrix matrix2) {
	int m = matrix1.row_num;
	int n = matrix2.column_num;
	if (matrix1.column_num != matrix2.row_num) {
		std::cout << "The column of matrix1 is not equal to the row of matrix 2" << endl;
		Matrix matrix3 = { 1, 1, 1, creatMatrixwithNum(1, 1, 0) };
		return matrix3;
	}
	else {
		int k = matrix1.column_num;
		Matrix matrix3 = { m, n, 1, creatMatrixwithNum(m, n, 0) };
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
void Addmatrix4x4T2(int k, Matrix matrix1, Matrix matrix2, Matrix &matrix3, int i, int j) {
	register float m3_00, m3_10, m3_20, m3_30, m3_01, m3_11, m3_21, m3_31, m3_02, m3_12, m3_22, m3_32, m3_03, m3_13, m3_23, m3_33;
	register float m2_p0, m2_p1, m2_p2, m2_p3;
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


	for (int p = 0; p < k; p++) {
		m2_p0 = matrix2.matrix[j][p];
		m2_p1 = matrix2.matrix[j + 1][p];
		m2_p2 = matrix2.matrix[j + 2][p];
		m2_p3 = matrix2.matrix[j + 3][p];
		m3_00 += m2_p0 * *m1p0;
		m3_10 += m2_p0 * *m1p1;
		m3_20 += m2_p0 * *m1p2;
		m3_30 += m2_p0 * *m1p3;
		m3_01 += m2_p1 * *m1p0;
		m3_11 += m2_p1 * *m1p1;
		m3_21 += m2_p1 * *m1p2;
		m3_31 += m2_p1 * *m1p3;
		m3_02 += m2_p2 * *m1p0;
		m3_12 += m2_p2 * *m1p1;
		m3_22 += m2_p2 * *m1p2;
		m3_32 += m2_p2 * *m1p3;
		m3_03 += m2_p3 * *m1p0++;
		m3_13 += m2_p3 * *m1p1++;
		m3_23 += m2_p3 * *m1p2++;
		m3_33 += m2_p3 * *m1p3++;
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

Matrix matrixDot2(Matrix matrix1, Matrix matrix2)
{
	int m = matrix1.row_num;
	int n = matrix2.column_num;
	if (matrix1.column_num != matrix2.row_num) {
		std::cout << "The column of matrix1 is not equal to the row of matrix 2" << endl;
		Matrix matrix3 = { 1, 1, 1, creatMatrixwithNum(1, 1, 0) };
		return matrix3;
	}
	else {
		int k = matrix1.column_num;
		Matrix matrix3 = { m, n, 1, creatMatrixwithNum(m, n, 0) };
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
	int m = matrix1.row_num;
	int n = matrix2.column_num;
	if (matrix1.column_num != matrix2.row_num) {
		std::cout << "The column of matrix1 is not equal to the row of matrix 2" << endl;
		Matrix matrix3 = { 1, 1, 1, creatMatrixwithNum(1, 1, 0) };
		return matrix3;
	}
	else {
		int k = matrix1.column_num;
		Matrix matrix3 = { m, n, 1, creatMatrixwithNum(m, n, 0) };
		for (int i = 0; i < m - 4; i += 4) {
			for (int j = 0; j < n; j++) {
				Addmatrix1x4(k, matrix1, matrix2, matrix3, i, j);
			}
		}
		return matrix3;
	}
}
Matrix matrixDot4(Matrix matrix1, Matrix matrix2) {
	int m = matrix1.row_num;
	int n = matrix2.column_num;
	if (matrix1.column_num != matrix2.row_num) {
		std::cout << "The column of matrix1 is not equal to the row of matrix 2" << endl;
		Matrix matrix3 = { 1, 1, 1, creatMatrixwithNum(1, 1, 0) };
		return matrix3;
	}
	else {
		Matrix matrix4 = { matrix2.column_num, matrix2.row_num, 1, creatMatrixwithNum(matrix2.column_num, matrix2.row_num, 0) };
		for (int i = 0; i < matrix2.row_num; i++) {
			for (int j = 0; j < matrix2.column_num; j++) {
				matrix4.matrix[j][i] = matrix2.matrix[i][j];
			}
		}
		int k = matrix1.column_num;
		Matrix matrix3 = { m, n, 1, creatMatrixwithNum(m, n, 0) };
		for (int i = 0; i < m - 4; i += 4) {
			for (int j = 0; j < n - 4; j += 4) {
				Addmatrix4x4T(k, matrix1, matrix4, matrix3, i, j);
			}
		}
		return matrix3;
	}
}
Matrix matrixDot5(Matrix matrix1, Matrix matrix2) {
	int m = matrix1.row_num;
	int n = matrix2.column_num;
	if (matrix1.column_num != matrix2.row_num) {
		std::cout << "The column of matrix1 is not equal to the row of matrix 2" << endl;
		Matrix matrix3 = { 1, 1, 1, creatMatrixwithNum(1, 1, 0) };
		return matrix3;
	}
	else {
		Matrix matrix4 = { matrix2.column_num, matrix2.row_num, 1, creatMatrixwithNum(matrix2.column_num, matrix2.row_num, 0) };
		for (int i = 0; i < matrix2.row_num; i++) {
			for (int j = 0; j < matrix2.column_num; j++) {
				matrix4.matrix[j][i] = matrix2.matrix[i][j];
			}
		}
		int k = matrix1.column_num;
		Matrix matrix3 = { m, n, 1, creatMatrixwithNum(m, n, 0) };
		for (int i = 0; i < m - 4; i += 4) {
			for (int j = 0; j < n - 4; j += 4) {
				Addmatrix4x4T2(k, matrix1, matrix4, matrix3, i, j);
			}
		}
		return matrix3;
	}
}


int main() {
	Matrix matrix0 = { 2000, 3000, 1, creatMatrixwithNum(2000, 3000, 1) };
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			std::cout << matrix0.matrix[i][j];
		}
		std::cout << endl;
	}
	Matrix matrix2 = { 3000, 2000, 2, creatMatrixwithNum(3000, 2000, 2) };

	Matrix matrix3, matrix4, matrix5, matrix6;
	auto start = std::chrono::steady_clock::now();
	//matrix3 = matrixDot1(matrix0, matrix2);
	auto end = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << ", duration = " << duration << std::endl;


	start = std::chrono::steady_clock::now();
	//matrix4 = matrixDot2(matrix0, matrix2);
	end = std::chrono::steady_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << ", duration2 = " << duration << std::endl;

	start = std::chrono::steady_clock::now();
	matrix5 = matrixDot3(matrix0, matrix2);
	end = std::chrono::steady_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << ", duration3 = " << duration << std::endl;
	std::cout << matrix5.matrix[0][0];

	start = std::chrono::steady_clock::now();
	matrix6 = matrixDot4(matrix0, matrix2);
	end = std::chrono::steady_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << ", duration3 = " << duration << std::endl;
	std::cout << matrix6.matrix[0][0];

	start = std::chrono::steady_clock::now();
	matrix6 = matrixDot5(matrix0, matrix2);
	end = std::chrono::steady_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << ", duration3 = " << duration << std::endl;
	std::cout << matrix6.matrix[0][0];
}
