#include "bsr.hpp"
using namespace std;

bsr::bsr(const uint32_t count, const uint32_t colindexes, const uint32_t rowindexes, const uint8_t blocksize)
{
	unsigned int i;
	this->count = count;
	this->colindexes = colindexes;
	this->rowindexes = rowindexes;
	this->blocksize = blocksize;

	this->array = new double *[lines];
	this->array[0] = new double[this->count];
	this->array[1] = new double[this->colindexes];
	this->array[2] = new double[this->rowindexes];
}

void bsr::print_bsr()
{
	uint32_t i;

	//Вывод BSR-матрицы на экран
	for (i = 0; i < this->count; ++i) {
		cout << this->array[0][i] << " ";
	} cout << endl;
	for (i = 0; i < this->colindexes; ++i) {
		cout << this->array[1][i] << " ";
	} cout << endl;
	for (i = 0; i < this->rowindexes; ++i) {
		cout << this->array[2][i] << " ";
	} cout << endl;
}

//Считывание BSR-матрицы из файла
uint8_t bsr::read_bsr(const char *filename)
{
	uint32_t i;
	ifstream file(filename);

	if (!file) {
		file.close();
		return 1;
	}

	//Заполнение BSR-матрицы
	for (i = 0; i < this->count; ++i) {
		file >> this->array[0][i];
	}
	for (i = 0; i < this->colindexes; ++i) {
		file >> this->array[1][i];
	}
	for (i = 0; i < this->rowindexes; ++i) {
		file >> this->array[2][i];
	}

	file.close();
	return 0;
}

//Запись в файл BSR-матрицы
uint8_t bsr::write_bsr(const char *filename)
{
	uint32_t i;
	ofstream file(filename);

	if (!file) {
		file.close();
		return 1;
	}

	for (i = 0; i < this->count; ++i) {
		file << this->array[0][i] << " ";
	} file << endl;
	for (i = 0; i < this->colindexes; ++i) {
		file << this->array[1][i] << " ";
	} file << endl;
	for (i = 0; i < this->rowindexes; ++i) {
		file << this->array[2][i] << " ";
	}

	file.close();
	return 0;
}

bsr::~bsr()
{

}