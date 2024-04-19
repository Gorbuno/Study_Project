#ifndef UNTITLED_MATRIX_H
#define UNTITLED_MATRIX_H

#include "number.h"
#include <iostream>
#include <vector>
using namespace std;

class SquareMatrix {
    int m_rows, m_cols;
    vector<vector<number>> m_values;
private:
    number determinantHelper(const vector<vector<number>>& matrix) const;
public:
    SquareMatrix();                         // по умолчанию создается пустая матрица
    SquareMatrix (int rows, int cols);      // выделяет память, элементы не инициализирует
   /** void generate_1();                   // заполняет единичную матрицу*/
    void print_screen();                    // вывод матрицы
    number determinant() const;             // определитель
    SquareMatrix transpose();               // транспонирование матрицы
    void CinMatrix (int);                   //ввод пользовательской матрицы
    int rows() const;
    int cols() const;
    int rank();
};


#endif //UNTITLED_MATRIX_H
