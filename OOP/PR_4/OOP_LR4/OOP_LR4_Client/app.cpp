#include "app.h"

app::app(int argc, char* argv[]):QApplication(argc, argv){
    TCommonParam params = {
        QHostAddress::LocalHost,
        19031, 11031
    };
    this->interface = new Interface();
    this->comms = new TCommunicator(params);
     this->interface->show();
     connect(this->interface, SIGNAL(SENDER(QString)), this, SLOT(dove(QString)));
     connect(this->comms, SIGNAL(recieved(QString)), this, SLOT(postOffice(QString)));
}

void app::dove(QString msg){
    this->comms->send(msg);
}

void app::postOffice(QString msg){
    this->interface->recieveMSG (msg);
}
