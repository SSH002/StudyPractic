#include "matrix.hpp"
#include "coo.hpp"
using namespace std;

//����������� ������ COO
coo::coo(const uint32_t size)
{
	uint8_t i;
	this->size = size;
	this->values = new double[this->size];
	this->indexes = new uint16_t *[lines];

	for (i = 0; i < lines; ++i) {
		this->indexes[i] = new uint16_t[this->size];
	}
}

//����� COO-������� �� �����
void coo::print_coo()
{
	uint32_t i, j;

	cout << endl;
	for (i = 0; i < this->size; ++i) {
		cout << this->values[i] << " ";
	} cout << endl;
	for (i = 0; i < lines; ++i) {
		for (j = 0; j < this->size; ++j) {
			cout << this->indexes[i][j] << " ";
		}
		cout << endl;
	}

}

//���������� COO-������� �� �����
void coo::read_coo(const char *filename)
{
	uint32_t i, j;
	ifstream file(filename);

	file >> i;								//�������
	//���������� COO-�������
	for (i = 0; i < this->size; ++i) {
		file >> this->values[i];
	}

	for (i = 0; i < lines; ++i) {
		for (j = 0; j < this->size; ++j) {
			file >> this->indexes[i][j];
		}
	}

	//���������� ������
	file.close();
}

//������ � ���� ���-�������
void coo::write_coo(const char *filename)
{
	uint32_t i, j;
	ofstream file(filename);

	//������ ������� COO-�������
	file << this->size << " \n";

	//������ � ���� ���-�������
	for (i = 0; i < this->size; ++i) {
		file << this->values[i];
	} file << endl;

	for (i = 0; i < lines; ++i) {
		for (j = 0; j < this->size; ++j) {
			file << this->indexes[i][j] << " ";
		}
		file << endl;
	}

	//���������� ������
	file.close();
}

//���������� ���-�� �������� � ����������� �������
uint16_t coo::coo_colsize()
{
	uint32_t i, size = 0;

	for (i = 0; i < this->size; ++i) {
		if (this->indexes[0][i] > size) {
			size = this->indexes[0][i];
		}
	}
	
	return ++size;
}

//���������� ���-�� ����������� �������� � ���-�������
uint16_t coo::coo_rowsize(uint16_t index)
{
	uint32_t i = index, size = 1;

	while (this->indexes[1][i] == this->indexes[1][i + 1]) {
		++size;
		++i;
	}

	return size;
}

//����������� ���-������� � ����������� ���
void coo::coo_to_matrix(matrix *Matr)
{
	uint32_t i, j, k;

	for (i = 0, k = 0; i < Matr->rows; ++i) {
		for (j = 0; j < Matr->cols; ++j) {
			if ((j == this->indexes[0][k]) && (i == this->indexes[1][k])) {
				Matr->values[i][j] = this->values[k];
				++k;
			} else {
				Matr->values[i][j] = 0;
			}
		}
	}
}

//���������� ����� ������, ���������� ��� ����������� �������
void coo::matrix_size(uint16_t *rows, uint16_t *cols)
{
	*rows = this->indexes[1][this->size - 1] + 1;
	*cols = this->coo_colsize();
}

//���������� ����� ������, ���������� ��� CSR
void coo::csr_size(uint32_t *size, uint32_t *rowindexes)
{
	*size = this->size;
	*rowindexes = this->indexes[1][this->size - 1] + 2;
}

//
//���������� ����� ������, ���������� ��� BSR
void coo::bsr_size(uint32_t *size, uint32_t *colindexes, uint16_t *rowindexes, const uint8_t bs)
{
	uint32_t a, b;
	uint16_t c, rows, cols;

	this->matrix_size(&rows, &cols);
	matrix *Buffer = new matrix(rows, cols);
	this->coo_to_matrix(Buffer);

	Buffer->bsr_size(&a, &b, &c, bs);
	*size = a;
	*colindexes = b;
	*rowindexes = c;

	delete Buffer;
}

//����������� ���-������� � ������ CSR
void coo::coo_to_csr(csr *CSR)
{
	uint32_t i, j;

	//���������� ������� �������� � ������� cols
	CSR->values = this->values;
	CSR->indexes[0] = this->indexes[0];

	//���������� ������� rowindexes
	for (i = 0, j = 0; i < CSR->rowindexes; ++i, j += this->coo_rowsize(j)) {
		CSR->indexes[1][i] = j;
	}
}

//�� �����������
//����������� ���-������� � ������ BSR
void coo::coo_to_bsr(bsr *BSR)
{
	uint16_t rows, cols;

	this->matrix_size(&rows, &cols);
	matrix *Buffer = new matrix(rows, cols);
	this->coo_to_matrix(Buffer);
	//delete this;
	Buffer->matrix_to_bsr(BSR);

	delete Buffer;
}

//���������� ������ COO
coo::~coo()
{

}