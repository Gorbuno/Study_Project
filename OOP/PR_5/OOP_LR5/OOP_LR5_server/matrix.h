#ifndef MATRIX_H
#define MATRIX_H

#include "number.h"
#include <iostream>
#include <vector>
#include <QStringList>
#include <iomanip>
#include <sstream>
#include "ration.h"

using namespace std;

class Matrix
{
protected:
    int m_rows, m_cols;
    vector<vector<number>> m_values;
public:
    Matrix();

    Matrix(int rows, int cols);

    int rows() const;
    int cols() const;

    void print_screen();                    // вывод матрицы
    void print_screen(std::stringstream& ss) const;

    void CinMatrix(int n);                   //ввод пользовательской матрицы
    void setMatrixValue(int row, int col, int num, int det);
    void setDimension(int dimension);
    number getElement(int row, int col);
};

#endif // MATRIX_H
