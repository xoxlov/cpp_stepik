#pragma once
#include <iostream>
#include <iomanip>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::setprecision;

template <typename Type>
Matrix<Type>::Matrix()
{
    numOfEquations = 0;
    numOfVariablesExt = 0;
    matrix = nullptr;
    solutionVars = nullptr;
}

template <typename Type>
Matrix<Type>::~Matrix()
{
    freeMatrixAndSolutionMemory();
}

template <class MatrixType>
void Matrix<MatrixType>::freeMatrixAndSolutionMemory()
{
    if (matrix != nullptr && matrix[0] != nullptr) delete[] matrix[0];
    if (matrix != nullptr) delete[] matrix;
    if (solutionVars != nullptr) delete[] solutionVars;
}

template <typename Type>
void Matrix<Type>::CreateNewMatrix()
{
    freeMatrixAndSolutionMemory();
    ReadNumberOfEquations();
    ReadNumberOfVariables();
    AllocateMatrixInMemory();
    AllocateSolutionVarsInMemory();
}

template <typename Type>
void Matrix<Type>::ReadNumberOfEquations()
{
    cin >> numOfEquations;
}

template <typename Type>
void Matrix<Type>::ReadNumberOfVariables()
{
    cin >> numOfVariablesExt;
    ++numOfVariablesExt;
}

template <typename Type>
void Matrix<Type>::AllocateMatrixInMemory()
{
    matrix = new Type* [numOfEquations];
    matrix[0] = new Type [numOfEquations * numOfVariablesExt];
    for (auto i = 1; i < numOfEquations; ++i)
        matrix[i] = matrix[i - 1] + numOfVariablesExt;
}

template <typename Type>
void Matrix<Type>::AllocateSolutionVarsInMemory()
{
    solutionVars = new Type[numOfVariablesExt];
}

template <typename Type>
void Matrix<Type>::InputMatrixData()
{
    if (Matrix::verboseOutput)
        cout << "[A]" << MULTIPLY_SIGN << "[B]:" << endl;
    for (auto i = 0; i < numOfEquations; ++i)
        for (auto j = 0; j < numOfVariablesExt; ++j)
            cin >> matrix[i][j];
}

template <typename Type>
void Matrix<Type>::Print()
{
    if (Matrix::verboseOutput)
    {
        cout << "matrix [A]" << MULTIPLY_SIGN << "[X] = [B]: " << endl;
        for (auto i = 0; i < numOfEquations; ++i)
        {
            const auto width = 7;
            for (auto j = 0; j < numOfVariablesExt - 1; ++j)
                cout << setw(width) << setprecision(4) << matrix[i][j] << " ";
            cout << "| " << setw(width) << setprecision(4) << matrix[i][numOfVariablesExt - 1] << endl;
        }
        cout << endl;
    }
}

template <typename Type>
void Matrix<Type>::NormalizeEquationsByMainDiagonal()
{
    for (auto i = 0; i < numOfEquations; ++i)
    {
        Type tmp = matrix[i][i];
        for (auto j = 0; j < numOfVariablesExt; ++j)
            matrix[i][j] /= tmp;
    }
}

template <typename Type>
void Matrix<Type>::ForwardElimination()
{
    for (auto i = 0; i < numOfEquations - 1; ++i)
    {
        for (auto j = i + 1; j < numOfEquations; ++j)
        {
            Type tmp = matrix[j][i] / matrix[i][i];
            for (auto k = i; k < numOfVariablesExt; ++k)
                matrix[j][k] = matrix[j][k] - tmp * matrix[i][k];
            Print();
        }
        for (auto j = numOfVariablesExt - 1; j >= i + 1; --j)
            matrix[i + 1][j] /= matrix[i + 1][i + 1];
        Print();
    }
}

template <typename Type>
void Matrix<Type>::BackSubstitution()
{
    solutionVars[numOfEquations - 1] = matrix[numOfEquations - 1][numOfEquations];
    for (auto i = numOfEquations - 2; i >= 0; --i)
    {
        solutionVars[i] = matrix[i][numOfEquations];
        for (auto j = i + 1; j < numOfEquations; ++j)
            solutionVars[i] = solutionVars[i] - matrix[i][j] * solutionVars[j];
    }
}

template <typename Type>
void Matrix<Type>::SolveByGauss()
{
//    NormalizeEquationsByMainDiagonal();
//    if (Matrix::verboseOutput)
//        cout << "After normalization ";
//    Print();
    ForwardElimination();
    BackSubstitution();
}

template <typename Type>
void Matrix<Type>::PrintSolution()
{
//    if (std::any_of())
    // TODO: check if multiple solutions exist
    // TODO: check if no solution exists
    cout << "YES" << endl;
    if (Matrix::verboseOutput)
    {
        cout << "Solution:" << endl;
        for (auto i = 0; i < numOfVariablesExt - 1; ++i)
            cout << "x[" << i << "] = " << solutionVars[i] << endl;
    } else {
        for (auto i = 0; i < numOfVariablesExt - 1; ++i)
            cout << solutionVars[i] << " ";
    }
    cout << endl;
}

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
