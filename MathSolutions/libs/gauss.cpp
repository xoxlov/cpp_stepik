/*
 * Sample Input 1:
 * 3 3
 * 4 2 1 1
 * 7 8 9 1
 * 9 1 3 2
 * Sample Output 1:
 * YES
 * 0.2608695652173913 0.04347826086956526 -0.1304347826086957
 *
 * Sample Input 2:
 * 2 3
 * 1 3 4 4
 * 2 1 4 5
 * Sample Output 2:
 * INF
 * 
 * Sample Input 3:
 * 3 3
 * 1 3 2 7
 * 2 6 4 8
 * 1 4 3 1
 * Sample Output 3:
 * NO
 */
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "gauss.h"

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::setprecision;

using MatrixType = vector<vector<double>>;
using SolutionType = vector<double>;

void InputMatrixData(MatrixType& matrix)
{
    int numOfEquations;
    int numOfVariablesExt;
    cin >> numOfEquations;
    cin >> numOfVariablesExt;
    ++numOfVariablesExt;

    matrix.resize(numOfEquations);

    cout << "input [A] | [B]:" << endl;
    for (auto& row : matrix)
    {
        row.resize(numOfVariablesExt);
        for (auto& column : row)
            cin >> column;
    }
}

void PrintMatrix(const MatrixType& matrix)
{
    cout << "matrix [A]" << MULTIPLY_SIGN << "[X] = [B]: " << endl;
    const auto width = 7;
    const auto precision = 4;
    for (auto& row : matrix)
    {
        for (auto j = 0u; j < row.size() - 1; ++j)
            cout << setw(width) << setprecision(precision) << row[j] << " ";
        cout << "| " << setw(width) << setprecision(precision) << row[row.size() - 1] << endl;
    }
}

void NormalizeRowOfMatrix(MatrixType &matrix, const unsigned rowNum)
{
    const auto normValue = matrix[rowNum][rowNum];
    for (auto j = rowNum; j < matrix[rowNum].size(); ++j)
        matrix[rowNum][j] /= normValue;
}

void RearrangeMatrixRows(MatrixType& matrix)
{
    const auto size = matrix.size();
    for (auto relatedRowNum = 0u; relatedRowNum < size - 1; ++relatedRowNum)
    {
        auto maxValueRow = relatedRowNum;
        for (auto currentRowNum = relatedRowNum + 1; currentRowNum < size; ++currentRowNum)
            if (matrix[currentRowNum][relatedRowNum] > matrix[maxValueRow][relatedRowNum])
                maxValueRow = currentRowNum;
        std::swap(matrix[relatedRowNum], matrix[maxValueRow]);
    }
}

void MakeMatrixTriangle(MatrixType& matrix)
{
    const auto size = matrix.size();
    for (auto relatedRowNum = 0u; relatedRowNum < size - 1; ++relatedRowNum)
    {
        if (matrix[relatedRowNum][relatedRowNum] == 0)
            return;
        for (auto currentRowNum = relatedRowNum + 1; currentRowNum < size; ++currentRowNum)
        {
            const auto tmp = matrix[currentRowNum][relatedRowNum] / matrix[relatedRowNum][relatedRowNum];
            for (auto colNum = relatedRowNum; colNum < size + 1; ++colNum)
                matrix[currentRowNum][colNum] = matrix[currentRowNum][colNum] - tmp * matrix[relatedRowNum][colNum];
        }
    }
}

double CalcDeterminant(MatrixType matrix)
{
    MakeMatrixTriangle(matrix);
    auto detA{ 1.0 };
    for (auto i = 0u; i < matrix.size(); ++i)
        detA *= matrix[i][i];
    return detA;
}

void ForwardElimination(MatrixType &matrix)
{
    MakeMatrixTriangle(matrix);
    for (auto i = 0u; i < matrix.size(); ++i)
        NormalizeRowOfMatrix(matrix, i);
}

void BackSubstitution(MatrixType& matrix, SolutionType& solution)
{
    for (int i = solution.size() - 1; i >= 0; --i)
    {
        solution[i] = matrix[i][matrix.size()];
        for (auto j = i + 1u; j < matrix.size(); ++j)
            solution[i] = solution[i] - matrix[i][j] * solution[j];
    }
}

void PrintVector(SolutionType& solution)
{
    for (double item : solution)
        cout << item << " ";
    cout << endl;
}

bool IsSolutionMultiple(const MatrixType& matrix)
{
    // TODO: строки могут быть линейно зависимыми, поэтому можно привести матрицу к треугольному виду и тогда делать вывод
    if (matrix.size() < matrix[0].size() - 1) {
        cout << "INF" << endl;
        return true;
    }
    return false;
}

bool NoValidSolution(const MatrixType& matrix)
{
    if (matrix.size() >= matrix[0].size() || CalcDeterminant(matrix) == 0)
    {
        cout << "NO" << endl;
        return true;
    }
    return false;
}

void SolveEquationsWithGaussMethod()
{
    MatrixType matrix;
    SolutionType solution;

    InputMatrixData(matrix);
    RearrangeMatrixRows(matrix); // not really needed, but cool
    if (IsSolutionMultiple(matrix) || NoValidSolution(matrix))
        return;
    ForwardElimination(matrix);
    solution.resize(matrix.size());
    ForwardElimination(matrix);
    BackSubstitution(matrix, solution);

    PrintVector(solution);
}
