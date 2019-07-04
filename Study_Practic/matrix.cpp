#define _CRT_SECURE_NO_WARNINGS
#include "matrix.hpp"
using namespace std;

//Конструктор класса matrix
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

//Генерации разряжённой матрицы
void matrix::gen_matrix()
{
	//Запуск ГСЧ
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
					this->values[i][j] = 0;							//Заполнение нулями
				break;
				case 7:
				case 8:
				case 9:
					l = rand() % 2;
					switch (l) {
						case 0:
							this->values[i][j] = rand() % 10;		//Заполнение цифрами от 0 до 9
						break;
						case 1:
							this->values[i][j] = -1 * rand() % 10;	//Заполнение цифрами от -9 до 0
						break;
					}
				break;
			}
		}
	}
}

//Вывод матрицы на экран
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

//Считывание стандартной матрицы из файла
void matrix::read_matrix(const char *filename)
{
	uint16_t i, j;
	ifstream file(filename);


	file >> i;							//Костыль
	file >> i;							//Костыль

	//Заполнение матрицы
	for (i = 0; i < this->rows; ++i) {
		for (j = 0; j < this->cols; ++j) {
			file >> this->values[i][j];
		}
	}

	//Завершение работы
	file.close();
}

//Запись стандартной матрицы в файл
void matrix::write_matrix(const char *filename)
{
	uint16_t i, j;
	ofstream file(filename);

	//Запись в файл количества строк
	file << this->rows << " ";
	//Запись в файл количества столбцов
	file << this->cols << " \n";

	//Запись матрицы в файл
	for (i = 0; i < this->rows; ++i) {
		for (j = 0; j < this->cols; ++j) {
			file << this->values[i][j] << " ";
		}
		file << endl;
	}

	//Завершение работы
	file.close();
}

//Возвращает количество строк матрицы
uint16_t matrix::get_rows()
{
	return this->rows;
}

//Возвращает количество столбцов матрицы
uint16_t matrix::get_cols()
{
	return this->cols;
}

//Оперделяет объём памяти, выделяемый для COO
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

//Оперделяет объём памяти, выделяемый для CSR
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

//Оперделяет объём памяти, выделяемый для BSR
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
			if (fullness) {					//Проверка, были ли выявлены ненулевые элементы
				++(*size_col);
				fullness = 0;
			}
		}
	}

	*size = (*size_col) * (uint32_t) pow(bs, 2);
	*rowindexes = (this->rows / bs) + 1;
}

//Преобразование матрицы в формат COO
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

//Преобразование матрицы в формат CSR
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

	//Записываем кол-во элеметов
	CSR->indexes[1][i] = k;
}

//Преобразование матрицы в формат BSR
void matrix::matrix_to_bsr(bsr *BSR)
{
	uint32_t i, j, k, l, count, n = 0, fullness = 0;

	for (i = 0, count = 0; i < this->rows; i += BSR->blocksize) {
		BSR->indexes[1][i / BSR->blocksize] = count;
		for (j = 0; j < this->cols; j += BSR->blocksize) {
			for (k = i; k < BSR->blocksize + i; ++k) {
				for (l = j; l < BSR->blocksize + j; ++l) {
					if (this->values[k][l]) {	//Если элемент не равен нулю
						fullness++;
					}
				}
			}
			if (fullness) {						//Проверка, были ли выявлены ненулевые элементы
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

	//Записываем кол-во блоков
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

//Деструктор класса matrix
matrix::~matrix()
{

}