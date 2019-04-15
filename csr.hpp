#pragma once
#include <iostream>
#include <fstream>
#include <inttypes.h>
#include "line.hpp"
#include "matrix.hpp"

class csr {
	friend class matrix;

	protected:
		double **array;
		uint32_t cols;
		uint32_t rowindexes;

	public:
		csr(const uint32_t n, const uint32_t m);
		void print_csr();
		uint8_t read_csr(const char *filename);
		uint8_t write_csr(const char *filename);
		~csr();
};