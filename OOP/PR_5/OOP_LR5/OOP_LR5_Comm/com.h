#ifndef COM_H
#define COM_H

#include <QString>

enum messages
{
    INPUT_MATRIX = 1,
    DETERMINANT,
    TRANSPORINSE,
    RANG_MATRIX,
    OUTPUT_MATRIX,
};

extern const QChar separator;
QString& operator<< (QString&,const QString&);


#endif // COM_H
