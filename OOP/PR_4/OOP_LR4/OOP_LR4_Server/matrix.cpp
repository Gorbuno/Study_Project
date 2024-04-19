#include "matrix.h"
#include <iomanip>
#include <sstream>

using namespace std;

Matrix::Matrix() {
    m_rows = 0;
    m_cols = 0;
    m_values.resize(m_rows, vector<number>(m_cols));
}

Matrix::Matrix(int cols, int rows) {
    m_rows = rows;
    m_cols = cols;
    m_values.resize(m_rows, vector<number>(m_cols));
}

void Matrix::CinMatrix(int n) {
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

int Matrix::rows() const { return m_rows;}

int Matrix::cols() const { return m_cols;}

void Matrix::print_screen() {
    for (int i =  0; i < m_rows; ++i) {
        for (int j =  0; j < m_cols; ++j) {
            cout << fixed << setprecision(1) << m_values[i][j] << " ";
        }
        cout << endl;
    }
}

void Matrix :: transpose() {
    number count;
    for(size_t i = 0; i < m_rows; i++) {
        for(size_t j = 0; j < i; j++) {
            count = m_values[j][i];
            m_values[j][i] =  m_values[i][j];
            m_values[i][j] = count;
        }
    }
}

number Matrix::determinant() const {
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

number Matrix::determinantHelper(const vector<vector<number>>& matrix) const {
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

int Matrix:: rank()
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
            for (int col = i; col < m_cols; ++col) { tempMatrix[i][col] /= divisor; }
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

void Matrix::print_screen(std::stringstream& ss) const{
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            ss << this->m_values[i][j] << " ";}
        ss << "\n";}}


void Matrix::setMatrixValue(int row, int col, int num, int det) {
    if (row >= 0 && row < m_rows && col >= 0 && col < m_cols) {
            m_values[row][col] = TRational (num, det) ;
        } else {
            throw std::out_of_range("Index out of range");}}

void Matrix:: setDimension(int dimension) {
    if (dimension <= 0) {
        throw std::invalid_argument("Dimension must be a positive integer.");
    }
    m_rows = dimension;
    m_cols = dimension;
    m_values.resize(m_rows, std::vector<number>(m_cols));
}


number Matrix :: getElement (int row, int col){
    if (row < 0 || row > m_rows || col < 0 || col > m_cols) {
           throw std::out_of_range("Index out of range");}
        return m_values[row][col];
}
