#define _CRT_SECURE_NO_WARNINGS
#include "matrix.hpp"
using namespace std;

//����������� ������ matrix
matrix::matrix(const uint16_t rows, const uint16_t cols)
{
	uint32_t i;
	this->rows = rows;
	this->cols = cols;
	this->values = new double *[this->rows];
	for (i = 0; i < this->rows; ++i) {
		this->values[i] = new double[this->cols];
	}
}

//��������� ���������� �������
void matrix::gen_matrix()
{
	//������ ���
	srand(time(0));
	uint16_t i, j, k, l;

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
				case 6:
					this->values[i][j] = 0;							//���������� ������
				break;
				case 7:
				case 8:
				case 9:
					l = rand() % 2;
					switch (l) {
						case 0:
							this->values[i][j] = rand() % 10;		//���������� ������� �� 0 �� 9
						break;
						case 1:
							this->values[i][j] = -1 * rand() % 10;	//���������� ������� �� -9 �� 0
						break;
					}
				break;
			}
		}
	}
}

//����� ������� �� �����
void matrix::print_matrix()
{
	uint16_t i, j;

	cout << endl;
	for (i = 0; i < this->rows; ++i) {
		for (j = 0; j < this->cols; ++j) {
			cout << this->values[i][j] << " ";
		}
		cout << endl;
	}
}

//���������� ����������� ������� �� �����
void matrix::read_matrix(const char *filename)
{
	uint16_t i, j;
	ifstream file(filename);


	file >> i;							//�������
	file >> i;							//�������

	//���������� �������
	for (i = 0; i < this->rows; ++i) {
		for (j = 0; j < this->cols; ++j) {
			file >> this->values[i][j];
		}
	}

	//���������� ������
	file.close();
}

//������ ����������� ������� � ����
void matrix::write_matrix(const char *filename)
{
	uint16_t i, j;
	ofstream file(filename);

	//������ � ���� ���������� �����
	file << this->rows << " ";
	//������ � ���� ���������� ��������
	file << this->cols << " \n";

	//������ ������� � ����
	for (i = 0; i < this->rows; ++i) {
		for (j = 0; j < this->cols; ++j) {
			file << this->values[i][j] << " ";
		}
		file << endl;
	}

	//���������� ������
	file.close();
}

//���������� ���������� ����� �������
uint16_t matrix::get_rows()
{
	return this->rows;
}

//���������� ���������� �������� �������
uint16_t matrix::get_cols()
{
	return this->cols;
}

//���������� ����� ������, ���������� ��� COO
void matrix::coo_size(uint32_t *size)
{
	uint16_t i, j;

	for (i = 0, *size = 0; i < this->rows; ++i) {
		for (j = 0; j < this->cols; ++j) {
			if (this->values[i][j]) {
				++(*size);
			}
		}
	}
}

//���������� ����� ������, ���������� ��� CSR
void matrix::csr_size(uint32_t *size, uint32_t *size_row)
{
	uint16_t i, j;

	for (i = 0, *size = 0; i < this->rows; ++i) {
		for (j = 0; j < this->cols; ++j) {
			if (this->values[i][j]) {
				++(*size);
			}
		}
	}

	*size_row = this->rows + 1;
}

//���������� ����� ������, ���������� ��� BSR
void matrix::bsr_size(uint32_t *size, uint32_t *size_col, uint16_t *rowindexes, const uint8_t bs)
{
	uint32_t i, j, k = 0, l = 0, fullness = 0;

	for (i = 0, *size_col = 0;  i < this->rows; i += bs) {
		for (j = 0; j < this->cols; j += bs) {
			for (k = i; k < bs + i; ++k) {
				for (l = j; l < bs + j; ++l) {
					if (this->values[k][l]) {
						fullness++;
					}
				}
			}
			if (fullness) {					//��������, ���� �� �������� ��������� ��������
				++(*size_col);
				fullness = 0;
			}
		}
	}

	*size = (*size_col) * (uint32_t) pow(bs, 2);
	*rowindexes = (this->rows / bs) + 1;
}

//�������������� ������� � ������ COO
void matrix::matrix_to_coo(coo *COO)
{
	uint32_t i, j, k;

	for (i = 0, k = 0; i < this->rows; ++i) {
		for (j = 0; j < this->cols; ++j) {
			if (this->values[i][j]) {
				COO->values[k] = this->values[i][j];
				COO->indexes[0][k] = j;
				COO->indexes[1][k] = i;
				++k;
			}
		}
	}
}

//�������������� ������� � ������ CSR
void matrix::matrix_to_csr(csr *CSR)
{
	uint32_t i, j, k;

	for (i = 0, k = 0; i < this->rows; ++i) {
		CSR->indexes[1][i] = k;
		for (j = 0; j < this->cols; ++j) {
			if (this->values[i][j]) {
				CSR->values[k] = this->values[i][j];
				CSR->indexes[0][k] = j;
				++k;
			}
		}
	}

	//���������� ���-�� ��������
	CSR->indexes[1][i] = k;
}

//�������������� ������� � ������ BSR
void matrix::matrix_to_bsr(bsr *BSR)
{
	uint32_t i, j, k, l, count, n = 0, fullness = 0;

	for (i = 0, count = 0; i < this->rows; i += BSR->blocksize) {
		BSR->indexes[1][i / BSR->blocksize] = count;
		for (j = 0; j < this->cols; j += BSR->blocksize) {
			for (k = i; k < BSR->blocksize + i; ++k) {
				for (l = j; l < BSR->blocksize + j; ++l) {
					if (this->values[k][l]) {	//���� ������� �� ����� ����
						fullness++;
					}
				}
			}
			if (fullness) {						//��������, ���� �� �������� ��������� ��������
				BSR->indexes[0][count] = j / BSR->blocksize;
				++count;
				for (k = i; k < BSR->blocksize + i; ++k) {
					for (l = j; l < BSR->blocksize + j; ++l) {
						BSR->values[n] = this->values[k][l];
						++n;
					}
				}
				fullness = 0;
			}
		}
	}

	//���������� ���-�� ������
	BSR->indexes[1][i / BSR->blocksize] = count;
}

uint8_t matrix::matrix_equal(matrix *Matr)
{
	uint16_t i, j;

	if (this->rows == Matr->rows && this->cols == Matr->cols) {
		for (i = 0; i < this->rows; ++i) {
			for (j = 0; j < this->cols; ++j) {
				if (this->values[i][j] != Matr->values[i][j]) {
					return 1;
				}
			}
		}
	} else {
		return 1;
	}

	return 0;
}

//���������� ������ matrix
matrix::~matrix()
{

}