#include "MatriDisplayWindow.h"

MatrixDisplayWindow::MatrixDisplayWindow(QWidget *parent)
    : QDialog(parent), matrixTextEdit(new QTextEdit(this)) {
    setWindowTitle("Matrix Display");
    matrixTextEdit->setReadOnly(true);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(matrixTextEdit);
    setLayout(layout);
}

void MatrixDisplayWindow::displayMatrix(const std::stringstream &matrixText) {
    matrixTextEdit->setPlainText(matrixText.str().c_str());
}
