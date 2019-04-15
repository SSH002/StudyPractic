#include "csr.hpp"
using namespace std;

csr::csr(const unsigned int n, const unsigned int m)
{
	uint32_t i;
	this->cols = n;
	this->rowindexes = m;
	this->array = new double *[lines];
	for (i = 0; i < lines - 1; ++i) {
		this->array[i] = new double[n];
	}
	this->array[i] = new double[rowindexes];
}

void csr::print_csr()
{
	uint32_t i, j;

	for (i = 0; i < lines - 1; ++i) {
		for (j = 0; j < this->cols; ++j) {
			cout << this->array[i][j] << " ";
		}
		cout << endl;
	}
	for (j = 0; j < this->rowindexes; ++j) {
		cout << this->array[i][j] << " ";
	} cout << endl;
}

uint8_t csr::read_csr(const char *filename)
{
	uint32_t i, j;
	ifstream file(filename);

	if (!file) {
		file.close();
		return 1;
	}

	for (i = 0; i < lines - 1; ++i) {
		for (j = 0; j < this->cols; ++j) {
			file >> this->array[i][j];
		}
	}
	for (j = 0; j < this->rowindexes; ++j) {
		file >> this->array[i][j];
	}

	file.close();
	return 0;
}

uint8_t csr::write_csr(const char *filename)
{
	uint32_t i, j;
	ofstream file(filename);

	if (!file) {
		file.close();
		return 1;
	}

	for (i = 0; i < lines - 1; ++i) {
		for (j = 0; j < this->cols; ++j) {
			file << this->array[i][j] << " ";
		}
		file << endl;
	}
	for (j = 0; j < this->rowindexes; ++j) {
		file << this->array[i][j] << " ";
	}

	file.close();
	return 0;
}

csr::~csr()
{

}