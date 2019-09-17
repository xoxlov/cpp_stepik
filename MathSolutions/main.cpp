#include "libs/matrix.h"
#include "libs/gauss.h"

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
    //SolveSystemOfLinearEquationsByGaussMethod();
    SolveEquationsWithGaussMethod();

    system("pause");
    return 0;
}
