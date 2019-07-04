#include "csr.hpp"
using namespace std;

//Конструктор класса CSR
csr::csr(const unsigned int size, const unsigned int rowindexes)
{
	this->size = size;
	this->rowindexes = rowindexes;

	this->values = new double [this->size];
	this->indexes = new uint16_t *[lines];
	this->indexes[0] = new uint16_t[this->size];
	this->indexes[1] = new uint16_t[this->rowindexes];
}

//Вывод CSR-матрицы на экран
void csr::print_csr()
{
	uint32_t i;

	cout << endl;
	for (i = 0; i < this->size; ++i) {
		cout << this->values[i] << " ";
	} cout << endl;
	for (i = 0; i < this->size; ++i) {
		cout << this->indexes[0][i] << " ";
	} cout << endl;
	for (i = 0; i < this->rowindexes; ++i) {
		cout << this->indexes[1][i] << " ";
	} cout << endl;
}

//Считывание CSR-матрицы из файла
void csr::read_csr(const char *filename)
{
	uint32_t i;
	ifstream file(filename);

	file >> i;						//Костыль
	file >> i;						//Костыль

	//Заполнение CSR-матрицы
	for (i = 0; i < this->size; ++i) {
		file >> this->values[i];
	}
	for (i = 0; i < this->size; ++i) {
		file >> this->indexes[0][i];
	}
	for (i = 0; i < this->rowindexes; ++i) {
		file >> this->indexes[1][i];
	}

	//Завершение работы
	file.close();
}

//Запись в файл СSR-матрицы
void csr::write_csr(const char *filename)
{
	uint32_t i;
	ofstream file(filename);

	//Запись размеров СSR-матрицы
	file << this->size << " " << this->rowindexes << " \n";

	//Запись в файл
	for (i = 0; i < this->size; ++i) {
		file << this->values[i] << " ";
	} file << endl;
	for (i = 0; i < this->size; ++i) {
		file << this->indexes[0][i] << " ";
	} file << endl;
	for (i = 0; i < this->rowindexes; ++i) {
		file << this->indexes[1][i] << " ";
	} file << endl;

	//Завершение работы
	file.close();
}

//Сравнение двух csr-матриц по размерам и элементам
uint8_t csr::csr_equals(csr* CSR)
{
	uint32_t i;

	if (this->size == CSR->size && this->rowindexes == CSR->rowindexes) {
		for (i = 0; i < this->size; ++i) {
			if (this->values[i] != CSR->values[i]) {
				return 1;
			}
			if (this->indexes[0][i] != CSR->indexes[0][i]) {
				return 1;
			}
		}
		for (i = 0; i < this->rowindexes; ++i) {
			if (this->indexes[1][i] != CSR->indexes[1][i]) {
				return 1;
			}
		}
		return 0;
	}

	return 1;
}

//Деструктор класса CSR
csr::~csr()
{

}