#define _CRT_SECURE_NO_WARNINGS
#include "matrix.hpp"
#include "line.hpp"
using namespace std;

matrix::matrix(const uint32_t rows, const uint32_t cols)
{
	uint32_t i;
	this->rows = rows;
	this->cols = cols;
	this->array = new double *[this->rows];
	for (i = 0; i < this->rows; ++i) {
		this->array[i] = new double[this->cols];
	}
}

void matrix::gen_matrix()
{
	srand(time(NULL));
	uint32_t i, j, k;

	for (i = 0; i < this->rows; ++i) {
		for (j = 0; j < this->cols; ++j) {
			k = rand() % 10;
			switch (k) {
				case 0:
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
					this->array[i][j] = 0;
				break;
				case 6:
				case 7:
				case 8:
				case 9:
					this->array[i][j] = rand() % 10;
				break;
			}
		}
	}
}

void matrix::print_matrix()
{
	uint32_t i, j;

	for (i = 0; i < this->rows; ++i) {
		for (j = 0; j < this->cols; ++j) {
			cout << this->array[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

uint8_t matrix::read_matr(const char *filename)
{
	uint32_t i, j;
	ifstream file(filename);

	if (!file) {
		file.close();
		return 1;
	}

	for (i = 0; i < this->rows; ++i) {
		for (j = 0; j < this->cols; ++j) {
			file >> this->array[i][j];
		}
	}

	file.close();
	return 0;
}

uint8_t matrix::write_matr(const char *filename)
{
	uint32_t i, j;
	ofstream file(filename);

	if (!file) {
		file.close();
		return 1;
	}

	for (i = 0; i < lines; ++i) {
		for (j = 0; j < this->cols; ++j) {
			file << this->array[i][j] << " ";
		}
		file << endl;
	}

	file.close();
	return 0;
}


void matrix::matr_to_coo(coo *COO)
{
	uint32_t i, j, k;

	for (i = 0, k = 0; i < this->rows; ++i) {
		for (j = 0; j < this->cols; ++j) {
			if (this->array[i][j]) {
				COO->array[0][k] = this->array[i][j];
				COO->array[1][k] = i;
				COO->array[2][k] = j;
				++k;
			}
		}
	}
}

void matrix::matr_to_csr(csr *CSR)
{
	uint32_t i, j, k;

	for (i = 0, k = 0; i < this->rows; ++i) {
		CSR->array[2][i] = k;
		for (j = 0; j < this->cols; ++j) {
			if (this->array[i][j]) {
				CSR->array[0][k] = this->array[i][j];
				CSR->array[1][k] = i;
				++k;
			}
		}
	}

	CSR->array[2][i] = k;
}

matrix::~matrix()
{

}