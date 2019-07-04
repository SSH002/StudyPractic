#define _CRT_SECURE_NO_WARNINGS
#include "f-read-write.hpp"
using namespace std;

//��������, ���������� �� ��������� ����
uint8_t is_exist(const char *filename)
{
	ifstream file(filename);

	if (!file) {
		//file.close();
		return 1;
	} else {
		file.close();
		return 0;
	}
}

//���������� ������
char *get_line(const char *filename, uint32_t str_number)
{
	char *string = new char[max_length];
	uint16_t i;
	ifstream file(filename);

	for (i = 0; i < str_number; ++i) {
		file.getline(string, max_length, '\n');
	} file.close();

	return string;
}

//�� ������������
//��������� ������ ������ number
uint8_t line_size(const char *filename, uint32_t number)
{
	uint32_t i, size = 1;
	char *string = new char[max_length];
	ifstream file(filename);

	for (i = 0; i < number; ++i) {
		file.getline(string, max_length, '\n');
	} file.close();

	while (string[i] != '\0') {
		if (string[i] == ' ') {
			++size;
		}
		++i;
	}																																																													if (number == 1) --size;

	delete[] string;
	return size;
}

//��������� ���-�� ����� � ����� (������������ ��� ���������� ����������� ������)
uint32_t lines_count(const char *filename)
{
	uint32_t size = 0;
	FILE *file = fopen(filename, "r");
	char symb;

	while (fscanf(file, "%c", &symb) != EOF) {
		if (symb == '\n') {
			++size;
		}
	}

	fclose(file);
	return size;
}

//���������� �������� 1-��� ���������
uint32_t fset_size(const char *filename)
{
	uint32_t size;
	ifstream file(filename);

	file >> size;

	return size;
}

//���������� �������� 2-��� ���������
uint32_t f2set_size(const char *filename)
{
	uint32_t size;
	ifstream file(filename);

	file >> size;		//�������
	file >> size;

	return size;
}

//���������� �������� 3-��� ���������
uint16_t f3set_size(const char *filename)
{
	uint16_t size;
	ifstream file(filename);

	file >> size;		//�������
	file >> size;		//�������
	file >> size;

	return size;
}

//���������� �������� 4-��� ���������
uint16_t f4set_size(const char *filename)
{
	uint8_t size;
	ifstream file(filename);

	file >> size;		//�������
	file >> size;		//�������
	file >> size;		//�������
	file >> size;

	return size;
}