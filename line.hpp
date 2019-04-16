#pragma once
#include <inttypes.h>
#include <iostream>
#include <fstream>
#define max_linesize 1000
#define lines 3

uint32_t cols_size(const char *filename, uint32_t number);
uint32_t rows_size(const char *filename);