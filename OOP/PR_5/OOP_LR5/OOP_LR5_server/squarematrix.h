#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "matrix.h"

using namespace std;

class SquareMatrix: public Matrix {
private:
    number determinantHelper(const vector<vector<number>>& matrix) const;
public:
    number determinant() const;             // определитель
    void transpose();               // транспонирование матрицы
    int rank();
};


#endif //UNTITLED_MATRIX_H
