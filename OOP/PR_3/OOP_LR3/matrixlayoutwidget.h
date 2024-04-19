#ifndef MATRIXLAYOUTWIDGET_H
#define MATRIXLAYOUTWIDGET_H

#include <QRegExpValidator>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QLineEdit>
#include <qstring.h>
#include <QWidget>
#include <QLabel>
#include <QMap>

#include "Matrix.h"
#include "MatriDisplayWindow.h"


class MatrixLayoutWidget : public QWidget
{
    Q_OBJECT

public:
    MatrixLayoutWidget(QWidget *parent = nullptr);
    ~MatrixLayoutWidget();
     void displaySquareMatrix(int rows, int cols);

private:
    void removeLabel();
    virtual void resizeEvent(QResizeEvent *event) override;

protected slots:
    void onSetMatrixLayout(int row, int column, bool bIsResize=false);
    void onMatrixLayoutDivision();
    void onInputMatrixBtnClicked();
    void onOutputMatrixBtnClicked();
    void onOutputMatrixTransp();
    void onTransposeMatrix();
    void onDeterminantMatrix();
    void onRangMatrix();
    void removeNumeratorDenominatorFields();

private:
    QPushButton		*_1x1Btn;
    QPushButton		*_2x2Btn;
    QPushButton		*_3x3Btn;
    QPushButton		*_editBtn;
    QPushButton     *_outputMatrixBtn, *_transporiseBtn, *_rangBtn, *_determinantBtn, *_inputMatrixBtn;
    SquareMatrix    *_squareMatrix;
    QLineEdit		*_sizeEdit;
    QGridLayout     *gridLayout;
    QFrame          *_displayWall;
    QMap<quint16, QLineEdit *> _numeratorEditMap, _denominatorEditMap;
    int _row;
    int _column;
    SquareMatrix  *matrix, _matrix;
};

#endif // MATRIXLAYOUTWIDGET_H
