#include "line.hpp"
using namespace std;

//Вычисляет кол-во элементов в строке number
uint32_t line_size(const char *filename, uint32_t number)
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