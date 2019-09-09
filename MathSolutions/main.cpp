//http://www.cyberforum.ru/cpp-beginners/thread571966.html
#include "libs/matrix.h"

void SolveSystemOfLinearEquationsByGaussMethod()
{
	// решение системы линейных уравнений методом Гаусса
	Matrix<double> matrix;
	matrix.CreateNewMatrix();
	matrix.InputMatrixData();
	matrix.Print();
	matrix.SolveByGauss();
	matrix.PrintSolution();
}

int main()
{
	SolveSystemOfLinearEquationsByGaussMethod();

    return 0;
}
