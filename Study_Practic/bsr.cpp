#include "bsr.hpp"
using namespace std;

//Конструктор класса BSR
bsr::bsr(const uint32_t size, const uint32_t cols, const uint16_t rowindexes, const uint16_t blocksize)
{
	this->size = size;
	this->cols = cols;
	this->rowindexes = rowindexes;
	this->blocksize = blocksize;

	this->values = new double[this->size];
	this->indexes = new uint16_t *[lines];
	this->indexes[0] = new uint16_t[this->cols];
	this->indexes[1] = new uint16_t[this->rowindexes];
}

//Вывод BSR-матрицы на экран
void bsr::print_bsr()
{
	uint32_t i;

	cout << endl;
	for (i = 0; i < this->size; ++i) {
		cout << this->values[i] << " ";
	} cout << endl;
	for (i = 0; i < this->cols; ++i) {
		cout << this->indexes[0][i] << " ";
	} cout << endl;
	for (i = 0; i < this->rowindexes; ++i) {
		cout << this->indexes[1][i] << " ";
	} cout << endl;
}

//Считывание BSR-матрицы из файла
void bsr::read_bsr(const char *filename)
{
	uint32_t i;
	ifstream file(filename);

	file >> i;						//Костыль
	file >> i;						//Костыль
	file >> i;						//Костыль
	file >> i;						//Костыль

	//Заполнение BSR-матрицы
	for (i = 0; i < this->size; ++i) {
		file >> this->values[i];
	}
	for (i = 0; i < this->cols; ++i) {
		file >> this->indexes[0][i];
	}
	for (i = 0; i < this->rowindexes; ++i) {
		file >> this->indexes[1][i];
	}

	//Завершение работы
	file.close();
}

//Запись в файл BSR-матрицы
void bsr::write_bsr(const char *filename)
{
	uint32_t i;
	ofstream file(filename);

	//Запись размеров массивов и размера блока
	file << this->size << " " << this->cols << " " << this->rowindexes << " " << this->blocksize << endl;

	//Запись в файл
	for (i = 0; i < this->size; ++i) {
		file << this->values[i] << " ";
	} file << endl;
	for (i = 0; i < this->cols; ++i) {
		file << this->indexes[0][i] << " ";
	} file << endl;
	for (i = 0; i < this->rowindexes; ++i) {
		file << this->indexes[1][i] << " ";
	}

	//Завершение работы
	file.close();
}

//Сравнение двух BSR-матриц по размерам и элементам
uint8_t bsr::bsr_equals(bsr *BSR)
{
	uint32_t i;

	if (this->size == BSR->size && this->cols == BSR->cols && this->rowindexes == BSR->rowindexes && this->blocksize == BSR->blocksize) {
		for (i = 0; i < this->size; ++i) {
			if (this->values[i] != BSR->values[i]) {
				return 1;
			}
		}
		for (i = 0; i < this->cols; ++i) {
			if (this->indexes[0][i] != BSR->indexes[0][i]) {
				return 1;
			}
		}
		for (i = 0; i < this->rowindexes; ++i) {
			if (this->indexes[1][i] != BSR->indexes[1][i]) {
				return 1;
			}
		}
		return 0;
	}

	return 1;
}

//Деструктор класса BSR
bsr::~bsr()
{

}