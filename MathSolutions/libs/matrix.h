#pragma once

template <class MatrixType>
class Matrix
{
    static const bool verboseOutput = true;
    const unsigned char MULTIPLY_SIGN = static_cast<unsigned char>(250);

    int numOfEquations;
    int numOfVariablesExt; // extended with right matrix [B]
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
    void freeMatrixAndSolutionMemory();
    void CreateNewMatrix();
    void InputMatrixData();
    void Print();
    void NormalizeEquationsByMainDiagonal();
    void SolveByGauss();
    void PrintSolution();
};

#include "matrix.tpp"
