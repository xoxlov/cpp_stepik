// Note: взято из https://prog-cpp.ru/gauss/
// Note: метод Жордано-Гаусса
// Note: вылетает при несовместной системе, проверить совместность - посчитать определитель

#include <iostream>
#include "gauss2.h"

using namespace std;

void print_matrix(double** a, double* y, const int n)
{ // Вывод системы уравнений
    for (auto i = 0; i < n; i++)
    {
        for (auto j = 0; j < n; j++)
        {
            cout << a[i][j] << "*x" << j;
            if (j < n - 1)
                cout << " + ";
        }
        cout << " = " << y[i] << endl;
    }
}

double* gauss(double** a, double* y, const int n)
{
    const auto eps = 0.00001; // точность
    const auto x = new double[n];
    auto k = 0;
    while (k < n)
    { // Поиск строки с максимальным a[i][k]
        auto max = abs(a[k][k]);
        auto index = k;
        for (auto i = k + 1; i < n; i++)
        {
            if (abs(a[i][k]) > max)
            {
                max = abs(a[i][k]);
                index = i;
            }
        }
        // Перестановка строк
        if (max < eps)
        { // нет ненулевых диагональных элементов
            cout << "Решение получить невозможно из-за нулевого столбца ";
            cout << index << " матрицы A" << endl;
            return nullptr;
        }
        for (int j = 0; j < n; j++)
            std::swap(a[k][j], a[index][j]);
        std::swap(y[k], y[index]);
        // Нормализация уравнений
        for (auto i = k; i < n; i++)
        {
            const auto temp = a[i][k];
            if (abs(temp) < eps) continue; // для нулевого коэффициента пропустить
            for (auto j = 0; j < n; j++)
                a[i][j] = a[i][j] / temp;
            y[i] = y[i] / temp;
            if (i == k) continue; // уравнение не вычитать само из себя
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] - a[k][j];
            y[i] = y[i] - y[k];
        }
        k++;
    }
    // обратная подстановка
    for (k = n - 1; k >= 0; k--)
    {
        x[k] = y[k];
        for (auto i = 0; i < k; i++)
            y[i] = y[i] - a[i][k] * x[k];
    }
    return x;
}

void SolveEquationsWithGaussMethod2()
{
    system("chcp 1251");
    system("cls");
    cout << "Введите количество уравнений: ";
    int n;
    cin >> n;
    const auto a = new double*[n];
    auto* y = new double[n];
    for (auto i = 0; i < n; i++)
    {
        a[i] = new double[n];
        for (auto j = 0; j < n; j++)
        {
            cout << "a[" << i << "][" << j << "]= ";
            cin >> a[i][j];
        }
        cout << "y[" << i << "]= ";
        cin >> y[i];
    }
    print_matrix(a, y, n);
    const auto x = gauss(a, y, n);
    for (auto i = 0; i < n; i++)
        cout << "x[" << i << "]=" << x[i] << endl;

    for (auto i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;
    delete[] x;
    delete[] y;

    cin.get();
}
