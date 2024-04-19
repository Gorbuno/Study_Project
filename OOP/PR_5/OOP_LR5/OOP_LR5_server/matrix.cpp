#include "matrix.h"

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


int Matrix::rows() const { return m_rows; }
int Matrix::cols() const { return m_cols; }

void Matrix::print_screen() {
    for (int i =  0; i < m_rows; ++i) {
        for (int j =  0; j < m_cols; ++j) {
            cout << fixed << setprecision(1) << m_values[i][j] << " ";
        }
        cout << endl;
    }
}

void Matrix::print_screen(std::stringstream& ss) const{
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            ss << this->m_values[i][j] << " ";}
        ss << "\n";}}



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

