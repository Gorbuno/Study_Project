#include "consoleapp.h"

ConsoleApp::ConsoleApp(int argc, char *argv[]) : QCoreApplication (argc, argv)
{
    this -> matrix = new Matrix;
    TCommonParam params = {
        QHostAddress :: LocalHost,
        11031, 19031};
    this -> comms = new TCommunicator (params);
    connect(this -> comms, SIGNAL (recieved (QString)), this, SLOT (msgReciever(QString)));
}

void ConsoleApp::requestForm(int n){
    QString request;
    request += QString::number(n) + "|";
    if (n == TRANSPORINSE || n == OUTPUT_MATRIX){
        int size = this -> matrix -> rows();
        request += QString::number(size) + "|";
        for(int i=0; i < size; i++){
            for (int j=0; j < size; j++){
                request += this -> matrix -> getElement(i,j).toString() + ";";
            }
        }
    } else {
    if (n == DETERMINANT)
        request +=this -> matrix -> determinant().toString();
    else if (n == RANG_MATRIX)
        request += QString::number(this -> matrix -> rank());
    if (n == INPUT_MATRIX)
        request += QString :: number(0);
    }
    this -> comms -> send(request);
}

void ConsoleApp::msgReciever(QString msg){
    QStringList array, msgMatrix;
    int size;
    array = msg.split("|");
    switch (array[0].toInt()){
    case INPUT_MATRIX: // input_matrix
    {
        size = array[1].toInt();
        msgMatrix = array[2].split(";");
        this -> matrix -> setDimension(size);
        int count = 0;
        for (int i=0; i < size; i++){
            for (int j = 0; j < size; j++){
                QStringList parts = msgMatrix[count].split ("/");
                int numerator = parts[0].toInt();
                int denominator = parts[1].toInt();
                this -> matrix -> setMatrixValue(i,j,numerator, denominator);
                count ++;
            }
        }
        requestForm(INPUT_MATRIX);
        std::cout << "request Input send\n";
        break;
    }
    case TRANSPORINSE: // transporise or output_matrix
    {
        this -> matrix -> transpose();
        requestForm(TRANSPORINSE);
        std::cout << "request transporinse send\n";
        break;
    }
    case DETERMINANT: // determinate
    {
        requestForm(DETERMINANT);
        std::cout << "request determinate send\n";
        break;
    }
    case RANG_MATRIX: // rang
    {
        requestForm(RANG_MATRIX);
        std::cout << "request Rang send\n";
        break;
    }
    case OUTPUT_MATRIX:
    {
        requestForm(OUTPUT_MATRIX);
        std::cout << "request output send\n";
        break;
    }
    }
}
