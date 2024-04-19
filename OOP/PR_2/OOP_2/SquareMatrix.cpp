#include "Matrix.h"
//#include <iostream>
#include <iomanip>
using namespace std;

SquareMatrix::SquareMatrix() {
    m_rows = 0;
    m_cols = 0;
    m_values.resize(m_rows, vector<number>(m_cols));
}

SquareMatrix::SquareMatrix(int cols, int rows) {
    m_rows = rows;
    m_cols = cols;
    m_values.resize(m_rows, vector<number>(m_cols));
}
/**
void SquareMatrix::generate_1() {
    for (number i = 0; i < m_rows; ++i) {
        for (number j = 0; j < m_cols; ++j) {
            //cout << "\nmatrix [" << i << "][" << j << "] = ";
            if (i == j) {
                m_values[i][j] = 1;}
            else {
                m_values[i][j] = 0;}
        }}
}
*/
void SquareMatrix::CinMatrix(int n) {
    m_rows = n;
    m_cols = n;
    m_values.resize(m_rows, vector<number>(m_cols));
    for (size_t i =  0; i < m_rows; ++i) {
        for (size_t j =  0; j < m_cols; ++j) {
            cout << "\nmatrix [" << i << "][" << j << "] = ";
            cin >> m_values[i][j];
        }
    }
}

int SquareMatrix::rows() const { return m_rows;}

int SquareMatrix::cols() const { return m_cols;}

void SquareMatrix::print_screen() {
    for (int i =  0; i < m_rows; ++i) {
        for (int j =  0; j < m_cols; ++j) {
            cout << fixed << setprecision(1) << m_values[i][j] << " ";
        }
        cout << endl;
    }
}

SquareMatrix SquareMatrix::transpose() {
    SquareMatrix other(m_cols, m_rows);
    for(size_t i = 0; i < m_rows; i++) {
        for(size_t j = 0; j < m_cols; j++) {
            other.m_values[j][i] = m_values[i][j];
        }
    }
    return other;
}

number SquareMatrix::determinant() const {
    int n = m_rows;
    if (n ==  1) {
        return m_values[0][0];
    } else if (n ==  2) {
        return m_values[0][0] * m_values[1][1] - m_values[0][1] * m_values[1][0];
    } else {
        number det =  0;
        vector<vector<number>> subMatrix(n -  1, vector<number>(n -  1));

        for (int i =  0; i < n; ++i) {
            for (int j =  1; j < n; ++j) {
                for (int k =  0; k < n; ++k) {
                    if (k != i) {
                        subMatrix[j -  1][k < i ? k : k -  1] = m_values[j][k];
                    }
                }
            }
            det = det + (i %  2 ==  0 ?  1 : -1) * m_values[0][i] * determinantHelper(subMatrix);
        }
        return det;
    }
}

number SquareMatrix::determinantHelper(const vector<vector<number>>& matrix) const {
    int n = matrix.size();
    if (n ==  1) {
        return matrix[0][0];
    } else if (n ==  2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    } else {
        number det =  0;
        vector<vector<number>> subMatrix(n -  1, vector<number>(n -  1));

        for (int i =  0; i < n; ++i) {
            for (int j =  1; j < n; ++j) {
                for (int k =  0; k < n; ++k) {
                    if (k != i) {
                        subMatrix[j -  1][k < i ? k : k -  1] = matrix[j][k];
                    }
                }
            }
            det = det + (i %  2 ==  0 ?  1 : -1) * matrix[0][i] * determinantHelper(subMatrix);
        }
        return det;
    }
}

int SquareMatrix:: rank()
{
        if (m_rows != m_cols) {
            throw std::invalid_argument("Метод rank применим только к квадратным матрицам.");}
        int rank =  0;
        vector<vector<number>> tempMatrix = m_values;
        for (int i =  0; i < m_rows; ++i) {
            int maxRowIndex = i;
            for (int row = i +  1; row < m_rows; ++row) {
                if (abs(tempMatrix[row][i]) > abs(tempMatrix[maxRowIndex][i])) { maxRowIndex = row;}
            }
            if (maxRowIndex != i) { swap(tempMatrix[i], tempMatrix[maxRowIndex]);}
            if (tempMatrix[i][i] ==  0) {continue;}
            number divisor = tempMatrix[i][i];
            for (int col = i; col < m_cols; ++col) { tempMatrix[i][col] /= divisor;}
            for (int row = i +  1; row < m_rows; ++row) {
                number factor = tempMatrix[row][i];
                for (int col = i; col < m_cols; ++col) {
                    tempMatrix[row][col] =  tempMatrix[row][col] - factor * tempMatrix[i][col];
                }
            }

            rank++;
        }

        return rank;
    }
