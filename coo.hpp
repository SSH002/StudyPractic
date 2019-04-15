#pragma once
#include <iostream>
#include <fstream>
#include <inttypes.h>
#include "line.hpp"
#include "matrix.hpp"
#include "csr.hpp"

class coo {
	friend class matrix;
	friend class csr;

	protected:
		double **array;
		uint32_t cols;

	public:
		coo(const uint32_t n);
		void print_coo();
		uint8_t read_coo(const char *filename);
		uint8_t write_coo(const char *filename);
		matrix *coo_to_matr(matrix *matr);
		csr *coo_to_csr(csr *CSR);
		~coo();
};