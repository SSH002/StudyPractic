#define _CRT_SECURE_NO_WARNINGS
#include "vector.hpp"
using namespace std;

//Конструктор класса vector
vector::vector(uint16_t size)
{
	this->size = size;
	this->values = new double[size];
}

//Генерации вектора
void vector::gen_vector()
{
	//Запуск ГСЧ
	srand(time(0));
	uint16_t i, j;

	for (i = 0; i < this->size; ++i) {
		j = rand() % 2;
		switch (j) {
			case 0:
				this->values[i] = rand() % 10;			//Заполнение цифрами от 0 до 9
			break;
			case 1:
				this->values[i] = -1 * rand() % 10;		//Заполнение цифрами от -9 до 0
			break;
		}
	}
}

//Вывод вектора на экран
void vector::print_vector()
{
	uint16_t i;

	cout << endl;
	for (i = 0; i < this->size; ++i) {
		cout << this->values[i] << " ";
	}
	cout << endl;
}

//Считывание вектора из файла
void vector::read_vector(const char *filename)
{
	uint16_t i;
	ifstream file(filename);

	file >> i;											//Заглушка
	for (i = 0; i < this->size; ++i) {
		file >> this->values[i];
	}

	//Завершение работы
	file.close();
}

//Запись в файл вектора
void vector::write_vector(const char *filename)
{
	uint16_t i;
	ofstream file(filename);

	//Записываем размер вектора
	file << this->size << " \n";
	//Заполнение вектора
	for (i = 0; i < this->size; ++i) {
		file << this->values[i] << " ";
	}

	//Завершение работы
	file.close();
}

//Возвращает размер вектора
uint16_t vector::get_size()
{
	return this->size;
}

//Умножение стандартной матрицы на вектор
void vector::multiple_matrix(matrix *Matr, vector *Result)
{
	uint16_t i, j;

	for (i = 0; i < Matr->rows; ++i) {
		Result->values[i] = 0;
		for (j = 0; j < Matr->cols; ++j) {
				Result->values[i] += Matr->values[i][j] * this->values[j];
		}
	}
}

//Умножение COO-матрицы на вектор
void vector::multiple_coo(coo *COO, vector *Result)
{
	uint32_t i, j, k, l, rowsize;

	for (i = 0, k = 0; i < Result->size; ++i, k += rowsize) {
		Result->values[i] = 0;
		rowsize = COO->coo_rowsize(k);
		for (j = k; j < rowsize + k; ++j) {
			for (l = 0; l < this->size; ++l) {
				if (COO->indexes[0][j] == l) {
					Result->values[i] += COO->values[j] * this->values[l];
				}
			}
		}
	}
}

//Умножение CSR-матрицы на вектор
void vector::multiple_csr(csr *CSR, vector *Result)
{
	uint32_t i, j, k, l;
	uint16_t rowsize;

	for (i = 0, k = 0; i < Result->size; ++i, k += rowsize) {
		Result->values[i] = 0;
		rowsize = CSR->indexes[1][i + 1] - CSR->indexes[1][i];
		for (j = k; j < rowsize + k; ++j) {
			for (l = 0; l < this->size; ++l) {
				if (CSR->indexes[0][j] == l) {
					Result->values[i] += CSR->values[j] * this->values[l];
				}
			}
		}
	}
}

//Умножение BSR-матрицы на вектор
void vector::multiple_bsr(bsr *BSR, vector *Result)
{
	uint16_t i, j, k, l, m, step, rowsize = 0;
	uint16_t *M = new uint16_t[Result->size];

	//Вычисление размеров буферных векторов
	for (i = 0; i < Result->size; i += BSR->blocksize) {
		//Вычисляем размер буферного вектора
		M[i] = (BSR->indexes[1][(i / BSR->blocksize) + 1] - BSR->indexes[1][i / BSR->blocksize]) * BSR->blocksize;
		//Присваиваем размер буфера другим строкам блочной строки
		for (j = i + 1; j < BSR->blocksize + i; ++j) {
			M[j] = M[i];
		}																																							//if (M[i] > 65535) { M[i] = (uint16_t)(16 >> M[i - BSR->blocksize]); }
	}

	for (i = 0, k = 0, step = 0; i < Result->size; ++i) {
		Result->values[i] = 0;
		double *buffer = new double [M[i]];
		uint16_t *cols = new uint16_t [M[i]];
		
		//Вычисляем индекс k, по которому будем обращаться к элементам BSR-матрицы
		if (!(i % BSR->blocksize)) {		//Перемещение между блочными строками
			for (j = 0; j < i; j += BSR->blocksize) {
				rowsize += M[j];
			}
	 		k = BSR->blocksize * rowsize;
			rowsize = 0;
			if (i) {
				step += M[i - 1] / BSR->blocksize;
			}
		} else {							//Перемещение внутри блочной строки
			k -= BSR->blocksize * (M[i] - 1);
		}

		//Заполнение буферного вектора и индексов элементов
		for (j = 0; j < M[i]; ++j, ++k) {
			buffer[j] = BSR->values[k];
			cols[j] = BSR->blocksize * BSR->indexes[0][step + j / BSR->blocksize];
			if (j % BSR->blocksize == BSR->blocksize - 1) {	//Перемещение между блоками одной строки
				k += BSR->blocksize * (BSR->blocksize - 1);
				for (l = j - (BSR->blocksize - 1); l < j; ++l) {
					cols[l + 1] = cols[l] + 1;
				}
			}
		}

		//Умножение вектора на буферный вектор(строку матрицы)
		for (j = 0; j < M[i]; ++j) {
			for (m = 0; m < this->size; ++m) {
				if (cols[j] == m) {
					Result->values[i] += buffer[j] * this->values[m];
				}
			}
		}
		delete[] cols;
		delete[] buffer;
	}
}

//Поэлементно сравнивает два вектора
uint8_t vector::vectors_equal(vector *Vector2)
{
	uint16_t i;

	if (this->size == Vector2->size) {
		for (i = 0; i < this->size; ++i) {
			if (this->values[i] != Vector2->values[i]) {
				return 1;
			}
		}
		return 0;
	}

	return 1;
}

//Деструктор класса Vector
vector::~vector()
{

}