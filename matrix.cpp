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

void matrix::coo_size(uint32_t *size)
{
	uint32_t i, j;

	for (i = 0, *size = 0; i < this->rows; ++i) {
		for (j = 0; j < this->cols; ++j) {
			if (this->array[i][j]) {
				++(*size);
			}
		}
	}
}

void matrix::csr_size(uint32_t *size, uint32_t *size_row)
{
	uint32_t i, j;

	for (i = 0, *size = 0; i < this->rows; ++i) {
		for (j = 0; j < this->cols; ++j) {
			if (this->array[i][j]) {
				++(*size);
			}
		}
	}

	*size_row = this->rows + 1;
}

void matrix::bsr_size(uint32_t *size, uint32_t *size_col, uint32_t *size_row, const uint8_t bs)
{
	uint32_t i, j;

	for (i = 0, *size_col = 0;  i < this->rows; i += bs) {
		for (j = 0; j < this->cols; j += bs) {
			if ((this->array[i][j]) || (this->array[i + 1][j]) ||
				(this->array[i][j + 1]) || (this->array[i+ 1][j + 1])) {
				++(*size_col);
			}
		}
	}
	
	*size = (*size_col) * pow(bs, 2);
	*size_row = (this->rows / bs) + 1;
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

void matrix::matr_to_bsr(bsr *BSR)
{
	uint32_t i, j, k, l, m, count, n = 0;

	for (i = 0, m = 0, count = 0; i < this->rows; i += BSR->blocksize, ++m) {
		BSR->array[2][m] = count;
		for (j = 0; j < this->cols; j += BSR->blocksize) {
			if ((this->array[i][j]) || (this->array[i + 1][j]) ||
				(this->array[i][j + 1]) || (this->array[i+ 1][j + 1])) {
				BSR->array[1][count] = j / BSR->blocksize;
				++count;
				for (k = i; k < BSR->blocksize + i; ++k) {
					for (l = j; l < BSR->blocksize + j; ++l) {
						BSR->array[0][n] = this->array[k][l];
						++n;
					}
				}
			}
		}
	}

	//Записываем кол-во блоков
	BSR->array[2][m] = count;
}

matrix::~matrix()
{

}