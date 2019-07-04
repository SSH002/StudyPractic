#pragma once
#include <iostream>
#include <fstream>
#include <inttypes.h>
#include "f-read-write.hpp"
#include "matrix.hpp"
#include "coo.hpp"

class csr {
	friend class matrix;
	friend class vector;
	friend class coo;

	protected:
		double *values;
		uint16_t **indexes;
		uint32_t size;
		uint32_t rowindexes;

	public:
		csr(const uint32_t size, const uint32_t rowindexes);
		void print_csr();
		void read_csr(const char *filename);
		void write_csr(const char *filename);
		//void csr_to_matr(matrix *M);
		~csr();
		/*Для проведения тестов*/
		uint8_t csr_equals(csr* CSR);
};