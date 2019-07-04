#define _CRT_SECURE_NO_WARNINGS
#include "thirdparty/UnitTest++.h"				//Third-party library, source:https://github.com/unittest-cpp
#include "../Study_Practic/f-read-write.cpp"
#include "../Study_Practic/matrix.cpp"
#include "../Study_Practic/coo.cpp"
#include "../Study_Practic/csr.cpp"
#include "../Study_Practic/bsr.cpp"
#include "../Study_Practic/vector.cpp"

//Разработал Пирoгoв A.B.
SUITE(Convertation)
{
	TEST(COO_to_Matrix)
	{
		cout << "*--------------COO_to_Matrix--------------*\n\n";
		uint32_t i, j;
		uint32_t size;
		uint16_t rows, cols;
		const char* filename = "test_matrix2.txt";

		matrix *Matr1 = new matrix(fset_size(filename), f2set_size(filename));
		Matr1->read_matrix(filename);
		cout << "+-------Matrix1-------+";
		Matr1->print_matrix();

		Matr1->coo_size(&size);
		coo *COO = new coo(size);
		Matr1->matrix_to_coo(COO);
		cout << "\n+-------COO-------+";
		COO->print_coo();

		COO->matrix_size(&rows, &cols);
		matrix *Matr2 = new matrix(rows, cols);
		COO->coo_to_matrix(Matr2);
		cout << "\n+-------Matrix2-------+";
		Matr2->print_matrix();

		CHECK_EQUAL(Matr1->matrix_equal(Matr2), 0);
	}

	TEST(Matrix_COO_to_CSR)
	{
		cout << "\n*--------------Matrix/COO_to_CSR--------------*\n\n";
		uint32_t size, rowindexes;
		uint16_t equal = 0;
		const char* filename = "test_matrix.txt";

		matrix *Matr = new matrix(fset_size(filename), f2set_size(filename));
		Matr->read_matrix(filename);
		cout << "+-------Matrix-------+";
		Matr->print_matrix();

		Matr->coo_size(&size);
		coo *COO = new coo(size);
		Matr->matrix_to_coo(COO);
		cout << "\n+-------COO-------+";
		COO->print_coo();

		Matr->csr_size(&size, &rowindexes);
		csr* CSR1 = new csr(size, rowindexes);
		Matr->matrix_to_csr(CSR1);
		cout << "\n+-------CSR1-------+";
		CSR1->print_csr();

		COO->csr_size(&size, &rowindexes);
		csr* CSR2 = new csr(size, rowindexes);
		COO->coo_to_csr(CSR2);
		cout << "\n+-------CSR2-------+";
		CSR2->print_csr();

		CHECK_EQUAL(CSR1->csr_equals(CSR2), 0);
	}

	TEST(Matrix_COO_to_BSR)
	{
		cout << "\n*--------------Matrix/COO_to_BSR--------------*\n\n";
		uint32_t size, colsize;
		uint16_t rowindexes;
		const char *filename = "test_matrix.txt";

		matrix *Matr = new matrix(fset_size(filename), f2set_size(filename));
		Matr->read_matrix(filename);
		cout << "+-------Matrix-------+";
		Matr->print_matrix();

		Matr->coo_size(&size);
		coo *COO = new coo(size);
		Matr->matrix_to_coo(COO);
		cout << "\n+-------COO-------+";
		COO->print_coo();

		Matr->bsr_size(&size, &colsize, &rowindexes, 2);
		bsr *BSR1 = new bsr(size, colsize, rowindexes, 2);
		Matr->matrix_to_bsr(BSR1);
		cout << "\n+-------BSR1-------+";
		BSR1->print_bsr();

		COO->bsr_size(&size, &colsize, &rowindexes, 2);
		bsr *BSR2 = new bsr(size, colsize, rowindexes, 2);
		COO->coo_to_bsr(BSR2);
		cout << "\n+-------BSR2-------+";
		BSR2->print_bsr();
		//COO->print_coo();

		CHECK_EQUAL(BSR1->bsr_equals(BSR2), 0);
	}
}

//Разработал Малыхов Д.Е.
SUITE(Multiplication_to_Vector)
{
	TEST(Multiplication_to_COO)
	{
		cout << "\n*--------------Multiplication_to_COO--------------*\n\n";
		uint32_t size;
		const char *filename = "test_matrix.txt";
		const char *filename2 = "test_vector.txt";

		matrix *Matr = new matrix(fset_size(filename), f2set_size(filename));
		Matr->read_matrix(filename);
		cout << "+-------Matrix-------+";
		Matr->print_matrix();

		vector *Vect = new vector(fset_size(filename2));
		Vect->read_vector(filename2);
		cout << "\n+-------Vect-------+";
		Vect->print_vector();

		Matr->coo_size(&size);
		coo *COO = new coo(size);
		Matr->matrix_to_coo(COO);
		cout << "\n+-------COO-------+";
		COO->print_coo();

		vector *Result_Matrix = new vector(fset_size(filename));
		vector *Result_COO = new vector(fset_size(filename));

		Vect->multiple_matrix(Matr, Result_Matrix);
		Vect->multiple_coo(COO, Result_COO);

		cout << "\n+-------Result_Matrix-------+";
		Result_Matrix->print_vector();
		cout << "\n+-------Result_COO-------+";
		Result_COO->print_vector();

		CHECK_EQUAL(Result_Matrix->vectors_equal(Result_COO), 0);
	}

	TEST(Multiplication_to_CSR)
	{
		cout << "\n*--------------Multiplication_to_CSR--------------*\n\n";
		uint32_t size, rowindexes;
		const char *filename = "test_matrix.txt";
		const char *filename2 = "test_vector.txt";

		matrix *Matr = new matrix(fset_size(filename), f2set_size(filename));
		Matr->read_matrix(filename);
		cout << "+-------Matrix-------+";
		Matr->print_matrix();

		vector *Vect = new vector(fset_size(filename2));
		Vect->read_vector(filename2);
		cout << "\n+-------Vect-------+";
		Vect->print_vector();

		Matr->csr_size(&size, &rowindexes);
		csr *CSR = new csr(size, rowindexes);
		Matr->matrix_to_csr(CSR);
		cout << "\n+-------CSR-------+";
		CSR->print_csr();

		vector *Result_Matrix = new vector(fset_size(filename));
		vector *Result_CSR = new vector(fset_size(filename));

		Vect->multiple_matrix(Matr, Result_Matrix);
		Vect->multiple_csr(CSR, Result_CSR);

		cout << "\n+-------Result_Matrix-------+";
		Result_Matrix->print_vector();
		cout << "\n+-------Result_CSR-------+";
		Result_CSR->print_vector();

		CHECK_EQUAL(Result_Matrix->vectors_equal(Result_CSR), 0);
	}

	TEST(Multiplication_to_BSR1)
	{
		cout << "\n*--------------Multiplication_to_BSR1-(bs=2)-------*\n\n";
		uint32_t size, colsize;
		uint16_t rowindexes;
		const char *filename = "test_matrix.txt";
		const char *filename2 = "test_vector.txt";

		matrix *Matr = new matrix(fset_size(filename), f2set_size(filename));
		Matr->read_matrix(filename);
		cout << "+-------Matrix-------+";
		Matr->print_matrix();

		vector *Vect = new vector(fset_size(filename2));
		Vect->read_vector(filename2);
		cout << "\n+-------Vect-------+";
		Vect->print_vector();

		Matr->bsr_size(&size, &colsize, &rowindexes, 2);
		bsr *BSR = new bsr(size, colsize, rowindexes, 2);
		Matr->matrix_to_bsr(BSR);
		cout << "\n+-------BSR-------+";
		BSR->print_bsr();

		vector *Result_Matrix = new vector(fset_size(filename));
		vector *Result_BSR = new vector(fset_size(filename));

		Vect->multiple_matrix(Matr, Result_Matrix);
		Vect->multiple_bsr(BSR, Result_BSR);

		cout << "\n+-------Result_Matrix-------+";
		Result_Matrix->print_vector();
		cout << "\n+-------Result_BSR-------+";
		Result_BSR->print_vector();

		CHECK_EQUAL(Result_Matrix->vectors_equal(Result_BSR), 0);
	}

	TEST(Multiplication_to_BSR2)
	{
		cout << "\n*--------------Multiplication_to_BSR2-(bs=3)-------*\n\n";
		uint32_t size, colsize;
		uint16_t rowindexes;
		const char *filename = "test_matrix2.txt";
		const char *filename2 = "test_vector2.txt";

		matrix *Matr = new matrix(fset_size(filename), f2set_size(filename));
		Matr->read_matrix(filename);
		cout << "+-------Matrix2-------+";
		Matr->print_matrix();

		vector *Vect = new vector(fset_size(filename2));
		Vect->read_vector(filename2);
		cout << "\n+-------Vect2-------+";
		Vect->print_vector();

		Matr->bsr_size(&size, &colsize, &rowindexes, 3);
		bsr *BSR = new bsr(size, colsize, rowindexes, 3);
		Matr->matrix_to_bsr(BSR);
		cout << "\n+-------BSR2-------+";
		BSR->print_bsr();

		vector *Result_Matrix = new vector(fset_size(filename));
		vector *Result_BSR = new vector(fset_size(filename));

		Vect->multiple_matrix(Matr, Result_Matrix);
		Vect->multiple_bsr(BSR, Result_BSR);

		cout << "\n+-------Result_Matrix2-------+";
		Result_Matrix->print_vector();
		cout << "\n+-------Result_BSR2-------+";
		Result_BSR->print_vector();

		CHECK_EQUAL(Result_Matrix->vectors_equal(Result_BSR), 0);
	}

	TEST(Multiplication_to_BSR3)
	{
		cout << "\n*--------------Multiplication_to_BSR3-(bs=5)-------*\n\n";
		uint32_t size, colsize;
		uint16_t rowindexes;
		const char *filename = "test_matrix3.txt";
		const char *filename2 = "test_vector3.txt";

		matrix *Matr = new matrix(fset_size(filename), f2set_size(filename));
		Matr->read_matrix(filename);
		cout << "+-------Matrix3-------+";
		Matr->print_matrix();

		vector *Vect = new vector(fset_size(filename2));
		Vect->read_vector(filename2);
		cout << "\n+-------Vect3-------+";
		Vect->print_vector();

		Matr->bsr_size(&size, &colsize, &rowindexes, 5);
		bsr *BSR = new bsr(size, colsize, rowindexes, 5);
		Matr->matrix_to_bsr(BSR);
		cout << "\n+-------BSR3-------+";
		BSR->print_bsr();

		vector *Result_Matrix = new vector(fset_size(filename));
		vector *Result_BSR = new vector(fset_size(filename));

		Vect->multiple_matrix(Matr, Result_Matrix);
		Vect->multiple_bsr(BSR, Result_BSR);

		cout << "\n+-------Result_Matrix3-------+";
		Result_Matrix->print_vector();
		cout << "\n+-------Result_BSR3-------+";
		Result_BSR->print_vector();

		CHECK_EQUAL(Result_Matrix->vectors_equal(Result_BSR), 0);
	}

	/*TEST(Multiplication_CSR_BIGDATA)
	{
		cout << "\n*--------------Multiplication_to_CSR--------------*\n\n";
		uint32_t size, rowindexes, N = 3000;

		matrix *Matr = new matrix(N, N);
		Matr->gen_matrix();

		vector* Vect = new vector(N);
		Vect->gen_vector();

		Matr->csr_size(&size, &rowindexes);
		csr* CSR = new csr(size, rowindexes);
		Matr->matrix_to_csr(CSR);

		vector* Result_Matrix = new vector(N);
		vector* Result_CSR = new vector(N);

		Vect->multiple_matrix(Matr, Result_Matrix);
		Vect->multiple_csr(CSR, Result_CSR);

		/*cout << "\n+-------Result_Matrix-------+";
		Result_Matrix->print_vector();
		cout << "\n+-------Result_CSR-------+";
		Result_CSR->print_vector();

		CHECK_EQUAL(Result_Matrix->vectors_equal(Result_CSR), 0);
	}*/
}

int main()
{
	return UnitTest::RunAllTests();
}