#ifndef CONSOLEAPP_H
#define CONSOLEAPP_H

#include <QCoreApplication>
#include <QStringList>
#include "../OOP_LR5_Comm/communicator.h"
#include "../OOP_LR5_Comm/com.h"
#include "squarematrix.h"


class ConsoleApp: public QCoreApplication
{
    Q_OBJECT
public:
    ConsoleApp(int, char**);
public slots:
    void msgReciever (QString);
private:
    TCommunicator* comms;
    SquareMatrix* matrix;
    void requestForm(int n);
};

#endif // CONSOLEAPP_H
