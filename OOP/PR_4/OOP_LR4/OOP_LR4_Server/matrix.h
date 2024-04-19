#ifndef MATRIX_H
#define MATRIX_H

#include "number.h"
#include <iostream>
#include <vector>
#include <QStringList>

#include "ration.h"

using namespace std;

class Matrix {
    int m_rows, m_cols;
    vector<vector<number>> m_values;
private:
    number determinantHelper(const vector<vector<number>>& matrix) const;
public:
    Matrix();                         // по умолчанию создается пустая матрица
    Matrix (int rows, int cols);      // выделяет память, элементы не инициализирует
    void generate_1();                   // заполняет единичную матрицу
    void print_screen();                    // вывод матрицы
    number determinant() const;             // определитель
    void transpose();               // транспонирование матрицы
    void CinMatrix(int n);                   //ввод пользовательской матрицы
    int rows() const;
    int cols() const;
    int rank();
    // добавление новых функций
    void print_screen(std::stringstream& ss) const;
    void setMatrixValue(int row, int col, int num, int det);
    void setDimension(int dimension);
    number getElement(int row, int col);
};


#endif //UNTITLED_MATRIX_H
