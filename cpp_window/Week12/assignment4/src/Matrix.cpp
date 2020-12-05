#include"Matrix.h"


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
		if ((str.at(num) <= '9' && str.at(num) >= '0') || str.at(num) == '.') {
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
	if (str.at(length - 1) != ']') {
		cout << "The expression should end with ]" << endl;
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
				if (i == length - 1) {
					return true;
				}
				cout << "中括号不应该在中间出现" << endl;
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

int testSameLength(string str, int rowNum) {
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

Matrix::Matrix(int row_num, int column_num) {
	this->size = row_num * column_num;
	this->column_num = column_num;
	this->row_num = row_num;
	this->mu = new mutex();
	if (this->size > 0) {
		this->matrixdata = new float[this->size];
		for (int i = 0; i < this->size; i++) {
			this->matrixdata[i] = 0;
		}
		this->refcount = new int(1);
	}
	else {
		this->matrixdata = NULL;
		cout << "The number you input is wrong";
	}
}
Matrix::Matrix(float value, int row_num, int column_num) {
	this->size = row_num * column_num;
	this->column_num = column_num;
	this->row_num = row_num;
	this->mu = new mutex();
	if (this->size > 0) {
		this->matrixdata = new float[this->size];
		for (int i = 0; i < this->size; i++) {
			this->matrixdata[i] = value;
		}
		this->refcount = new int(1);
	}
	else {
		this->matrixdata = NULL;
		cout << "The number you input is wrong";
	}
}
Matrix::Matrix(string str) {

	int rowNum = getrowNum(str);
	int columnNum = testSameLength(str, rowNum);
	this->size = rowNum * columnNum;
	this->row_num = rowNum;
	this->column_num = columnNum;
	this->refcount = new int(1);
	this->mu = new mutex();
	this->matrixdata = new float[this->size];
	int i = 1;
	int j = 0;
	int length = str.length();
	while (i < length) {
		string str0 = "";
		while (i < length&&str.at(i) != ',' && str.at(i) != ';'&&str.at(i) != ']') {
			str0 += str.at(i);
			i++;
		}
		this->matrixdata[j] = stof(str0);
		if (str.at(i) == ',') {
			j++;
			i++;
		}
		else if (str.at(i) == ';') {
			j++;
			i++;
		}
		else {
			break;
		}
	}

}

Matrix::Matrix(int num) {
	this->size = num * num;
	this->column_num = num;
	this->row_num = num;
	this->mu = new mutex();
	if (this->size > 0) {
		this->matrixdata = new float[this->size];
		for (int i = 0; i < this->size; i++) {
			this->matrixdata[i] = 0;
		}
		this->refcount = new int(1);
	}
	else {
		this->matrixdata = NULL;
		cout << "The number you input is wrong";
	}
}
Matrix::Matrix(int num, float value) {
	this->size = num * num;
	this->column_num = num;
	this->row_num = num;
	this->mu = new mutex();
	if (this->size > 0) {
		this->matrixdata = new float[this->size];
		for (int i = 0; i < this->size; i++) {
			this->matrixdata[i] = value;
		}
		this->refcount = new int(1);
	}
	else {
		this->matrixdata = NULL;
		cout << "The number you input is wrong";
	}
}
Matrix::Matrix(const Matrix &rhs) {
	this->matrixdata = rhs.matrixdata;
	this->column_num = rhs.column_num;
	this->row_num = rhs.row_num;
	this->size = rhs.size;
	this->mu = rhs.mu;
	(*mu).lock();
	this->refcount = rhs.refcount;
	*(this->refcount)=(*this->refcount)+1;
	(*mu).unlock();
}
Matrix::~Matrix() {
	(*mu).lock();
	if (*(this->refcount) < 2) {
		delete[] this->matrixdata;
		delete this->refcount;
	}
	else {
		(*this->refcount)=(*this->refcount)-1;
	}
	(*mu).unlock();
}
Matrix &Matrix::operator=(const Matrix &rhs) {
	if (this != &rhs) {
		this->column_num = rhs.column_num;
		this->row_num = rhs.row_num;
		this->matrixdata = rhs.matrixdata;
		this->mu = rhs.mu;
		(*mu).lock();
		this->refcount = rhs.refcount;
		(*this->refcount)++;
		(*mu).unlock();
	}
	return *this;
}
ostream &operator<< (ostream &os, Matrix &rhs) {
	int columnNum = rhs.column_num;
	for (int i = 0; i < rhs.row_num; i++) {
		os << "| ";
		for (int j = 0; j < rhs.column_num; j++) {
			os << rhs.matrixdata[i*columnNum + j] << ' ';
		}
		os << "|" << endl;
	}
	return os;
}
Matrix operator+(const Matrix& matrix1, const Matrix &matrix2) {
	if (matrix1.column_num == matrix2.column_num&&matrix1.row_num == matrix2.column_num) {
		int rowNum = matrix1.row_num;
		int columnNum = matrix1.column_num;
		Matrix matrix3 = Matrix(matrix1.row_num, matrix1.column_num);
		for (int i = 0; i < rowNum*columnNum; i++) {
			matrix3.matrixdata[i] = matrix1.matrixdata[i] + matrix2.matrixdata[i];
		}
		return matrix3;
	}
	cout << "两个矩阵大小不同，方法会返回一个大小是1的方阵" << endl;
	return Matrix(1,1);
}
Matrix operator-(const Matrix &matrix1, const Matrix &matrix2) {
	if (matrix1.column_num == matrix2.column_num&&matrix1.row_num == matrix2.column_num) {
		int rowNum = matrix1.row_num;
		int columnNum = matrix1.column_num;
		Matrix matrix3 = Matrix(matrix1.row_num, matrix1.column_num);
		for (int i = 0; i < rowNum*columnNum; i++) {
			matrix3.matrixdata[i] = matrix1.matrixdata[i] - matrix2.matrixdata[i];
		}
		return matrix3;
	}
	cout << "两个矩阵大小不同，方法会返回一个大小是1的方阵" << endl;
	return Matrix(1, 1);
}
Matrix  operator*(const Matrix &matrix1, const Matrix &matrix2) {
	if (matrix1.column_num == matrix2.row_num) {
		int rowNum = matrix1.row_num;
		int columnNum = matrix1.column_num;
		Matrix matrix3 = Matrix(matrix1.row_num, matrix2.column_num);
		const int M = matrix1.row_num;
		const int N = matrix2.column_num;
		const int K = matrix1.column_num;
		const int ida = K;
		const int idb = N;
		const int idc = N;
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, M, N, K, 1, matrix1.matrixdata, ida, matrix2.matrixdata, idb, 0.0, matrix3.matrixdata, idc);
		return matrix3;
	}
	cout << "两个矩阵大小不同，方法会返回一个大小是1的方阵" << endl;
	Matrix matrix3 = Matrix(1, 1);
	return matrix3;
}
Matrix operator*(float mul, const Matrix &matrix2) {
	Matrix matrix3 = Matrix(matrix2.row_num, matrix2.column_num);
	for (int i = 0; i < matrix2.size; i++) {
		matrix3.matrixdata[i] = mul * matrix2.matrixdata[i];
	}
	return matrix3;
}
Matrix operator*(const Matrix &matrix1, float mul) {
	Matrix matrix3 = Matrix(matrix1.row_num, matrix1.column_num);
	for (int i = 0; i < matrix1.size; i++) {
		matrix3.matrixdata[i] = mul * matrix1.matrixdata[i];
	}
	return matrix3;
}
Matrix operator/(float mul, const Matrix &matrix2) {
	Matrix matrix3 = Matrix(matrix2.row_num, matrix2.column_num);
	for (int i = 0; i < matrix2.size; i++) {
		matrix3.matrixdata[i] = mul / matrix2.matrixdata[i];
	}
	return matrix3;
}
Matrix operator/(const Matrix &matrix1, float mul) {
	Matrix matrix3 = Matrix(matrix1.row_num, matrix1.column_num);
	for (int i = 0; i < matrix1.size; i++) {
		matrix3.matrixdata[i] = matrix1.matrixdata[i] / mul;
	}
	return matrix3;
}
int Matrix::getRefcount() {
	return *(this->refcount);
}
float Matrix::operator()(int rowNum, int columnNum) {
	if (rowNum > this->row_num||rowNum<=0) {
		cout << "rowNum is wrong, will return a -1" << endl;
		return -1;
	}
	if (columnNum > this->column_num || columnNum <= 0) {
		cout << "rowNum is wrong, will return a -1" << endl;
		return -1;
	}
	return this->matrixdata[(rowNum-1)*this->column_num + columnNum - 1];
}
bool operator==(const Matrix &matrix1, const Matrix &matrix2) {
	if (matrix1.column_num != matrix2.column_num || matrix1.row_num != matrix2.row_num) {
		return false;
	}
	if (matrix1.matrixdata != matrix2.matrixdata) {
		return false;
	}
	return true;
}


Matrix creatMatWithString() {
	cout << "Enter your Matrix in form([1,2;3,4]): ";
	string str1;
	cin >> str1;
	if (testMatrix(str1)) {
		int num1 = getrowNum(str1);
		if (num1 > 1) {
			num1 = testSameLength(str1, num1);
		}
		if (num1 > 0) {
			Matrix matrix = Matrix(str1);
			return matrix;
		}
		else {
			cout << "矩阵每行元素个数不相同（返回一个1*1矩阵）" << endl;
		}
	}
	else {
		cout << "输入的矩阵格式错误（返回一个1*1矩阵）" << endl;
	}
	return Matrix(0, 1, 1);

}
Matrix creatMatWithString(string str) {
	if (testMatrix(str)) {
		int num1 = getrowNum(str);
		if (num1 > 1) {
			num1 = testSameLength(str, num1);
		}
		if (num1 > 0) {
			Matrix matrix = Matrix(str);
			return matrix;
		}
		else {
			cout << "矩阵每行元素个数不相同（返回一个1*1矩阵）" << endl;
		}
	}
	else {
		cout << "输入的矩阵格式错误（返回一个1*1矩阵）" << endl;
	}
	return Matrix(0, 1, 1);
}
Matrix Matrix::getSubMatrix(int rowStart, int rowEnd, int columnStart, int columnEnd) {
	if (rowStart <= 0 || columnStart <= 0) {
		cout << "parameter is wrong, return a matrix(1*1)with 0" << endl;
		return Matrix(0, 1, 1);
	}
	if (rowEnd > this->row_num || columnEnd > this->column_num) {
		cout << "parameter is wrong, return a matrix(1*1)with 0" << endl;
		return Matrix(0, 1, 1);
	}
	if (rowEnd <= rowStart || columnEnd <= columnStart) {
		cout << "parameter is wrong, return a matrix(1*1)with 0" << endl;
		return Matrix(0, 1, 1);
	}
	Matrix matrix = Matrix(0, (rowEnd - rowStart), (columnEnd - columnStart));
	int k = columnStart - 1;
	int j = 0;
	for (int i = rowStart - 1; i < rowEnd-1; i++) {
		while (k<columnEnd-1)
		{
			matrix.matrixdata[j] = this->matrixdata[i*this->column_num + k];
			k++;
			j++;
		}
		k = columnStart-1;
	}
	return matrix;
}