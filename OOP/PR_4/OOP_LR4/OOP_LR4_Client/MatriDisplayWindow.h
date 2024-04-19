#ifndef MATRIXDISPLAYWINDOW_H
#define MATRIXDISPLAYWINDOW_H


#include <QDialog>
#include <QTextEdit>
#include <QVBoxLayout>
#include <sstream>

class MatrixDisplayWindow : public QDialog {
    Q_OBJECT

public:
    explicit MatrixDisplayWindow(QWidget *parent = nullptr);
    void displayMatrix(const std::stringstream &matrixText);

private:
    QTextEdit *matrixTextEdit;
};

#endif // MATRIXDISPLAYWINDOW_H
