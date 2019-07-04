#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <time.h>
#include "f-read-write.hpp"
#include "matrix.hpp"
#include "coo.hpp"
#include "csr.hpp"
#include "bsr.hpp"
#include "vector.hpp"
using namespace std;

int main()
{
	setlocale(0, "");
	time_t start, end;
	uint32_t size, colsize;
	uint16_t rowindexes, N = 1000;
	uint16_t blocksize = 2;
	matrix *Matr = new matrix(N, N);
	vector *Vect = new vector(N);
	vector *Vect2 = new vector(N);

	Matr->gen_matrix();
	Vect->gen_vector();
	Matr->bsr_size(&size, &colsize, &rowindexes, blocksize);
	bsr *BSR = new bsr(size, colsize, rowindexes, blocksize);
	Matr->matrix_to_bsr(BSR);
	BSR->write_bsr("delfi.txt");

	delete Matr;
	start = clock();
	Vect->multiple_bsr(BSR, Vect2);
	end = clock();

	cout << "\nElapsed time: " << difftime(end, start) / CLOCKS_PER_SEC << " sec\n";
	system("pause");
	return 0;
}