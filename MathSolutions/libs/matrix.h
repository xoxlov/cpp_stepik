#pragma once

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

template <class MatrixType>
class Matrix
{
	const unsigned char MULTIPLY_SIGN = static_cast<unsigned char>(250);
private:
	int numOfEquations;
	int numOfVariables;
	MatrixType** matrix;
	MatrixType* solutionVars;
protected:
	void ReadNumberOfEquations();
	void ReadNumberOfVariables();
	void AllocateMatrixInMemory();
	void AllocateSolutionVarsInMemory();
	void ForwardElimination();
	void BackSubstitution();
public:
	Matrix();
	~Matrix();
	void CreateNewMatrix();
	void InputMatrixData(bool simple = false);
	void Print(bool simple = false);
	void NormalizeEquationsByMainDiagonal();
	void SolveByGauss();
	void PrintSolution(bool simple=false);
};

#include "matrix.tpp"
