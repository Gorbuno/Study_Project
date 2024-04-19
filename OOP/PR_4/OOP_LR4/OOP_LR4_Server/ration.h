#ifndef OOP_PROJECT_RATIONAL_H
#define OOP_PROJECT_RATIONAL_H


#include <iostream>
#include <cmath>
#include <numeric>
#include <QString>
#include <QStringList>

class TRational {
private:
    int m_numerator;
    int m_denominator;

public:
    TRational(int numerator = 0, int denominator = 1);

    int numerator() const;
    int denominator() const;

    void normalize();

    TRational operator+(const TRational &other) const;
    TRational operator-(const TRational &other) const;
    TRational operator*(const TRational &other) const;
    TRational operator*(int integer) const;
    friend TRational operator*(int integer, const TRational &rational);
    TRational operator/(const TRational &other) const;
    TRational &operator/=(const TRational &other);

    bool operator==(const TRational &other) const;
    bool operator!=(const TRational &other) const;
    bool operator>(const TRational &other) const;
    friend TRational abs();
    friend TRational abs(const TRational &);
    int gcd(int a, int b) ;

    friend std::ostream &operator<<(std::ostream &os, const TRational &r);
    friend std::istream &operator>>(std::istream &is, TRational &r);
    QString toString() const ;

};


#endif //OOP_PROJECT_RATIONAL_H
