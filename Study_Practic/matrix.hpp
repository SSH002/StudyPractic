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
	friend class vector;

	protected:
		double **values;
		uint16_t rows;
		uint16_t cols;

	public:
		matrix(const uint16_t rows, const uint16_t cols);
		void print_matrix();
		void read_matrix(const char *filename);
		void write_matrix(const char *filename);
		uint16_t get_rows();
		uint16_t get_cols();
		void coo_size(uint32_t *size);
		void csr_size(uint32_t *size, uint32_t *size_row);
		void bsr_size(uint32_t *size, uint32_t *size_col, uint16_t *rowindexes, const uint8_t bs);
		void matrix_to_coo(coo *COO);
		void matrix_to_csr(csr *CSR);
		void matrix_to_bsr(bsr *BSR);
		~matrix();
		/*Для проведения тестов*/
		void gen_matrix();									//Заполнение матрицы случайными числами
		uint8_t matrix_equal(matrix *Matr);
};