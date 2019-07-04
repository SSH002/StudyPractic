#pragma once
#include <inttypes.h>
#include <iostream>
#include <fstream>
#include <string>
#define max_length 256
#define lines 2

uint8_t is_exist(const char *filename);
char *get_line(const char *filename, uint32_t str_number);
uint8_t line_size(const char *filename, uint32_t str_number);
uint32_t lines_count(const char *filename);
uint32_t fset_size(const char *filename);		//—читывает 1-ый параметр из файла
uint32_t f2set_size(const char *filename);		//—читывает 2-ой параметр из файла
uint16_t f3set_size(const char *filename);		//—читывает 3-ий параметр из файла
uint16_t f4set_size(const char *filename);		//—читывает 4-ый параметр из файла