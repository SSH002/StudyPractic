#include "line.hpp"
using namespace std;

//Вычисляет кол-во элементов в строке number
uint32_t cols_size(const char *filename, uint32_t number)
{
	uint32_t i, size = 1;
	char *string = new char[max_linesize];
	ifstream file(filename);

	for (i = 0; i < number; ++i) {
		file.getline(string, max_linesize, '\n');
	} file.close();

	while (string[i] != '\0') {
		if (string[i] == ' ') {
			++size;
		}
		++i;
	}

	delete[] string;
	return size;
}

uint32_t rows_size(const char *filename)
{
	uint32_t i, size = 1;
	FILE *f = fopen(filename, "r");
	char symb;

	while (fscanf(f, "%c", &symb) != EOF) {
		switch (symb) {
		case '\n':
			++size;
		break;
		}
	}

	return size;
}