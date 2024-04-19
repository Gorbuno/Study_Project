#ifndef INTERFACE_H
#define INTERFACE_H

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

#include "MatriDisplayWindow.h"
#include "../OOP_LR4_Comm/com.h"
#include "../OOP_LR4_Comm/communicator.h"

class Interface : public QWidget
{
    Q_OBJECT

public:
    Interface(QWidget *parent = nullptr);
    ~Interface();
    void recieveMSG (QString);

protected slots:
    void onSetMatrixLayout(int row, int column, bool bIsResize=false);
    void onMatrixLayoutDivision();

    void onInputMatrixBtnClicked();
    void onOutputMatrixBtnClicked();
    //void onOutputMatrixTransp();
    void onTransposeMatrixBtnClicked();
    void onDeterminantMatrixBtnClicked();
    void onRangMatrixBtnClicked();


    void removeNumeratorDenominatorFields();

signals:
    void SENDER(QString);

private:
    void removeLabel();
    virtual void resizeEvent(QResizeEvent *event);
    QString requestForm(int n);

    QPushButton		*_1x1Btn;
    QPushButton		*_2x2Btn;
    QPushButton		*_3x3Btn;
    QPushButton		*_editBtn;
    QPushButton     *_outputMatrixBtn, *_transporiseBtn, *_rangBtn, *_determinantBtn, *_inputMatrixBtn;
    QLineEdit		*_sizeEdit;
    QGridLayout     *gridLayout;
    QFrame          *_displayWall;
    QMap<quint16, QLineEdit *> _numeratorEditMap, _denominatorEditMap;
    int _row;
    int _column;

};
#endif // INTERFACE_H
