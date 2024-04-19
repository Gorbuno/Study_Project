#ifndef APP_H
#define APP_H

#include "interface.h"
#include "../OOP_LR4_Comm/communicator.h"
#include <QApplication>

class app: public QApplication
{
    Q_OBJECT

public:
    app(int , char **);

public slots:
    void dove(QString);
    void postOffice(QString);

private:
    Interface *interface;
    TCommunicator *comms;
};

#endif // APP_H
