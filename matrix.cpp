#define _CRT_SECURE_NO_WARNINGS
#include "matrix.hpp"
#include "line.hpp"
using namespace std;

//����������� ������ matrix
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

//��������� ���������� �������
void matrix::gen_matrix()
{
	//������ ���
	srand(time(NULL));
	uint32_t i, j, k, l;

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
					this->array[i][j] = 0;							//���������� ������
				break;
				case 6:
				case 7:
				case 8:
				case 9:
					l = rand() % 2;
					switch (l) {
						case 0:
							this->array[i][j] = rand() % 10;		//���������� ������� �� 0 �� 9
						break;
						case 1:
							this->array[i][j] = -1 * rand() % 10;	//���������� ������� �� 0 �� -9
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
	uint32_t i, j;

	for (i = 0; i < this->rows; ++i) {
		for (j = 0; j < this->cols; ++j) {
			cout << this->array[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//���������� ����������� ������� �� �����
uint8_t matrix::read_matr(const char *filename)
{
	uint32_t i, j;
	ifstream file(filename);

	//��������, ������ �� ����
	if (!file) {
		file.close();
		return 1;
	}

	//���������� �������
	for (i = 0; i < this->rows; ++i) {
		for (j = 0; j < this->cols; ++j) {
			file >> this->array[i][j];
		}
	}

	//���������� ������
	file.close();
	return 0;
}

//������ ����������� ������� � ����
uint8_t matrix::write_matr(const char *filename)
{
	uint32_t i, j;
	ofstream file(filename);

	//��������, ������ �� ����
	if (!file) {
		file.close();
		return 1;
	}

	//������ ������� � ����
	for (i = 0; i < lines; ++i) {
		for (j = 0; j < this->cols; ++j) {
			file << this->array[i][j] << " ";
		}
		file << endl;
	}

	//���������� ������
	file.close();
	return 0;
}

//������� ������� C��-�������
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

//������� ������� CSR-�������
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

//������� ������� BSR-�������
void matrix::bsr_size(uint32_t *size, uint32_t *size_col, uint32_t *size_row, const uint8_t bs)
{
	uint32_t i, j, k, l, full = 0;

	for (i = 0, *size_col = 0;  i < this->rows; i += bs) {
		for (j = 0; j < this->cols; j += bs) {
			for (k = i; k < bs + i; ++k) {
				for (l = j; l < bs + j; ++l) {
					if (this->array[k][l]) {
						full++;
					}
				}
			}
			if (full) {					//��������, ���� �� �������� ��������� ��������
				++(*size_col);
				full = 0;
			}
		}
	}
	
	*size = (*size_col) * pow(bs, 2);
	*size_row = (this->rows / bs) + 1;
}

//�������������� ������� � ������ COO
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

//�������������� ������� � ������ CSR
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

	//���������� ���-�� ��������
	CSR->array[2][i] = k;
}

//�������������� ������� � ������ BSR
void matrix::matr_to_bsr(bsr *BSR)
{
	uint32_t i, j, k, l, count, n = 0, full = 0;

	for (i = 0, count = 0; i < this->rows; i += BSR->blocksize) {
		BSR->array[2][i / BSR->blocksize] = count;
		for (j = 0; j < this->cols; j += BSR->blocksize) {
			for (k = i; k < BSR->blocksize + i; ++k) {
				for (l = j; l < BSR->blocksize + j; ++l) {
					if (this->array[k][l]) {
						full++;
					}
				}
			}
			if (full) {					//��������, ���� �� �������� ��������� ��������
				BSR->array[1][count] = j / BSR->blocksize;
				++count;
				for (k = i; k < BSR->blocksize + i; ++k) {
					for (l = j; l < BSR->blocksize + j; ++l) {
						BSR->array[0][n] = this->array[k][l];
						++n;
					}
				}
				full = 0;
			}
		}
	}

	//���������� ���-�� ������
	BSR->array[2][i / BSR->blocksize] = count;
}

//���������� ������ matrix
matrix::~matrix()
{

}