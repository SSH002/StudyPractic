#pragma once
#include <inttypes.h>
#include "coo.hpp"
#include "csr.hpp"
#include "bsr.hpp"

class vector {
	friend class coo;

	protected:
		double *values;
		uint16_t size;

	public:
		vector(uint16_t size);
		void print_vector();
		void read_vector(const char *filename);
		void write_vector(const char *filename);
		uint16_t get_size();
		void multiple_matrix(matrix *Matr, vector *Result);
		void multiple_coo(coo *COO, vector *Result);
		void multiple_csr(csr *CSR, vector *Result);
		void multiple_bsr(bsr *BSR, vector *Result);
		~vector();
		/*Для проведения тестов*/
		void gen_vector();									//Заполнение вектора случайными числами
		uint8_t vectors_equal(vector *Vector2);			//Поэлементно сравнивает два вектора
};