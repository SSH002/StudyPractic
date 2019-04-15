#include "line.hpp"
#include "matrix.hpp"
#include "coo.hpp"
#include "csr.hpp"
using namespace std;

int main()
{
	uint32_t i, n = 6, m = 6;
	char *file = "matr.txt";
	char *filename = "matrix.txt";
	char *filename2 = "matrix3.txt";
	char *filename3 = "matrix4.txt";
	matrix *M = new matrix(file_size(file), line_size(file, 2));

	setlocale(0, "");
	//M->gen_matrix();
	M->read_matr(file);
	M->print_matrix();

	system("pause");
	return 0;
}