#pragma once
#include <iostream>
#include <fstream>
#include <inttypes.h>
#include "line.hpp"
#include "matrix.hpp"

class bsr {
	friend class matrix;

protected:
	double **array;
	uint32_t count;
	uint32_t colindexes;
	uint32_t rowindexes;
	uint8_t blocksize;

public:
	bsr(const uint32_t count, const uint32_t colindexes, const uint32_t rowindexes, const uint8_t blocksize);
	void print_bsr();
	uint8_t read_bsr(const char *filename);
	uint8_t write_bsr(const char *filename);
	~bsr();
};