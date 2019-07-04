#pragma once
#include <iostream>
#include <fstream>
#include <inttypes.h>
#include "f-read-write.hpp"
#include "matrix.hpp"
#include "coo.hpp"

class bsr {
	friend class matrix;
	friend class vector;
	friend class coo;

	protected:
		double *values;
		uint16_t **indexes;
		uint32_t size;
		uint32_t cols;
		uint16_t rowindexes;
		uint16_t blocksize;

	public:
		bsr(const uint32_t size, const uint32_t colindexes, const uint16_t rowindexes, const uint16_t blocksize);
		void print_bsr();
		void read_bsr(const char *filename);
		void write_bsr(const char *filename);
		~bsr();
		/*Для проведения тестов*/
		uint8_t bsr_equals(bsr* BSR);
};