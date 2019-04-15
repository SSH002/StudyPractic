#include "matrix.hpp"
#include "coo.hpp"
using namespace std;

coo::coo(const uint32_t n)
{
	uint32_t i;
	this->cols = n;
	this->array = new double *[lines];
	for (i = 0; i < lines; ++i) {
		this->array[i] = new double[n];
	}
}

void coo::print_coo()
{
	uint32_t i, j;

	for (i = 0; i < lines; ++i) {
		for (j = 0; j < this->cols; ++j) {
			cout << this->array[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

uint8_t coo::read_coo(const char *filename)
{
	uint32_t i, j;
	ifstream file(filename);

	if (!file) {
		file.close();
		return 1;
	}

	for (i = 0; i < lines; ++i) {
		for (j = 0; j < this->cols; ++j) {
			file >> this->array[i][j];
		}
	}
	file.close();

	return 0;
}

uint8_t coo::write_coo(const char *filename)
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

void coo::coo_to_matr(matrix *matr)
{
	uint32_t i, j, k;

	for (i = 0, k = 0; i < matr->rows; ++i) {
		for (j = 0; j < matr->cols; j++) {
			if ((j == this->array[1][k]) && (i == this->array[2][k])) {
				matr->array[i][j] = this->array[0][k];
				++k;
			} else {
				matr->array[i][j] = 0;
			}
		}
	}
}

void coo_to_csr(csr *CSR)
{
	uint32_t i, j, k;

}

coo::~coo()
{

}