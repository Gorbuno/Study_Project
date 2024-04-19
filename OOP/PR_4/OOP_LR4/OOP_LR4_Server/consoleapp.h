#ifndef CONSOLEAPP_H
#define CONSOLEAPP_H

#include <QCoreApplication>
#include <QStringList>
#include "../OOP_LR4_Comm/communicator.h"
#include "../OOP_LR4_Comm/com.h"
#include "matrix.h"


class ConsoleApp: public QCoreApplication
{
    Q_OBJECT
public:
    ConsoleApp(int, char**);
public slots:
    void msgReciever (QString);
private:
    TCommunicator* comms;
    Matrix* matrix;
    void requestForm(int n);
};

#endif // CONSOLEAPP_H
