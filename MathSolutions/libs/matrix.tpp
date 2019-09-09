#include <iostream>
#include "matrix.h"
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::setprecision;

template <typename Type>
Matrix<Type>::Matrix()
{
	numOfEquations = 0;
	numOfVariables = 0;
	matrix = nullptr;
	solutionVars = nullptr;
}

template <typename Type>
Matrix<Type>::~Matrix()
{
	delete[] matrix;
	delete[] solutionVars;
}

template <typename Type>
void Matrix<Type>::CreateNewMatrix()
{
	delete[] solutionVars;
	delete[] matrix;
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
	cin >> numOfVariables;
	++numOfVariables;
}

template <typename Type>
void Matrix<Type>::AllocateMatrixInMemory()
{
	matrix = new Type * [numOfEquations];
	for (auto i = 0; i < numOfEquations; ++i)
		matrix[i] = new Type[numOfVariables];
}

template <typename Type>
void Matrix<Type>::AllocateSolutionVarsInMemory()
{
	solutionVars = new Type[numOfVariables];
}

template <typename Type>
void Matrix<Type>::InputMatrixData(bool simple)
{
	if (simple)
		cout << "[A]" << MULTIPLY_SIGN << "[B]:" << endl;
	for (auto i = 0; i < numOfEquations; ++i)
		for (auto j = 0; j < numOfVariables; ++j)
			cin >> matrix[i][j];
}

template <typename Type>
void Matrix<Type>::Print(bool simple)
{
	if (simple)
	{
		cout << "matrix [A]" << MULTIPLY_SIGN << "[X] = [B]: " << endl;
		for (auto i = 0; i < numOfEquations; ++i)
		{
			const auto width = (simple) ? 0 : 7;
			for (auto j = 0; j < numOfVariables - 1; ++j)
				cout << setw(width) << setprecision(4) << matrix[i][j] << " ";
			cout << "| " << setw(width) << setprecision(4) << matrix[i][numOfVariables - 1] << endl;
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
		for (auto j = 0; j < numOfVariables; ++j)
			matrix[i][j] /= tmp;
	}
}

template <typename Type>
void Matrix<Type>::ForwardElimination()
{
	for (auto i = 0; i < numOfEquations; ++i)
	{
		for (auto j = i + 1; j < numOfEquations; ++j)
		{
			Type tmp = matrix[j][i];
			for (auto k = numOfEquations; k >= i; --k)
				matrix[j][k] = matrix[j][k] - tmp * matrix[i][k];
		}
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
	NormalizeEquationsByMainDiagonal();
	Print();
	ForwardElimination();
	BackSubstitution();
}

template <typename Type>
void Matrix<Type>::PrintSolution(bool simple)
{
	if (simple) {
		cout << "Solution:" << endl;
		for (auto i = 0; i < numOfEquations; ++i)
			cout << "x[" << i << "] = " << solutionVars[i] << endl;
	} else {
		for (auto i = 0; i < numOfEquations; ++i)
			cout << solutionVars[i] << " ";
	}
	cout << endl;
}
