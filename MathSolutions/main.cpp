#include "libs/matrix.h"
#include "libs/gauss.h"
#include "libs/gauss2.h"

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
    // from libs/gauss.h:
    //SolveEquationsWithGaussMethod();
    // from libs/gauss2.h:
    SolveEquationsWithGaussMethod2();

    system("pause");
    return 0;
}
