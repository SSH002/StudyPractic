#pragma once
#include <time.h>
#include <inttypes.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include "coo.hpp"
#include "csr.hpp"
#include "bsr.hpp"

class matrix {
	friend class coo;
	friend class csr;
	friend class bsr;

	protected:
		double **array;
		uint32_t rows;
		uint32_t cols;

	public:
		matrix(const uint32_t rows, const uint32_t cols);
		void print_matrix();
		void gen_matrix();
		uint8_t read_matr(const char *filename);
		uint8_t write_matr(const char *filename);

		void matr_to_coo(coo *COO);
		void matr_to_csr(csr *CSR);
		void matr_to_bsr(bsr *BSR);
		~matrix();
};