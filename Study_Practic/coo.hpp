#pragma once
#include <iostream>
#include <fstream>
#include <inttypes.h>
#include "f-read-write.hpp"
#include "matrix.hpp"
#include "csr.hpp"
#include "bsr.hpp"

class coo {
	friend class matrix;
	friend class vector;
	friend class csr;
	friend class bsr;

	protected:
		double *values;
		uint16_t **indexes;
		uint32_t size;

	public:
		coo(const uint32_t size);
		void print_coo();
		void read_coo(const char *filename);
		void write_coo(const char *filename);
		uint16_t coo_colsize();
		uint16_t coo_rowsize(uint16_t index);
		void coo_to_matrix(matrix *Matr);
		void coo_to_csr(csr *CSR);
		void coo_to_bsr(bsr *BSR);
		void matrix_size(uint16_t *rows, uint16_t *cols);
		void csr_size(uint32_t *size, uint32_t *rowindexes);
		void bsr_size(uint32_t *size, uint32_t *cols, uint16_t *rowindexes, const uint8_t bs);
		~coo();
};