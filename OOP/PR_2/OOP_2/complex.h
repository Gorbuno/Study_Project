#ifndef OOP_PROJECT_COMPLEX_H
#define OOP_PROJECT_COMPLEX_H

#include <iostream>
#include <cmath>
using namespace std;
class TComplex {
    double real; // Реальная часть
    double imaginary; // Мнимая часть
 public:
        // Конструктор по умолчанию
        TComplex();
        // Конструктор с параметрами
        TComplex(const int&);
        // Деструктор
        ~TComplex();
       friend ostream& operator<< (ostream&,TComplex);
       friend istream& operator>> (istream&,TComplex&);
       friend  TComplex abs(const TComplex&);
       friend TComplex operator*(int n, const TComplex& c);
    // Методы для работы с комплексными числами
        double abs() const;
        TComplex operator*(TComplex) const;
        TComplex operator*(int n) const;
        TComplex operator-(const TComplex& other) const;
        TComplex operator+( const TComplex& other) const;
        TComplex operator/( TComplex& other) ;
        bool operator>( const TComplex& other);
        bool operator== (TComplex);
        TComplex operator/=( TComplex& other) ;
};
#endif //OOP_PROJECT_COMPLEX_H
