#include <QApplication>
#include <QMainWindow>
#include "matrixlayoutwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    MatrixLayoutWidget *matrixLayoutWidget = new MatrixLayoutWidget(&mainWindow);
    mainWindow.setCentralWidget(matrixLayoutWidget);
    mainWindow.setWindowTitle("Matrix Editor");
    mainWindow.show();

    return app.exec();}
