#include "complex.h"

TComplex::TComplex()  {
    real = 0;
    imaginary = 0;
}

TComplex::TComplex(const int& n)  {
    real = n;
    imaginary = 0;
}
// Деструктор
TComplex::~TComplex() {}
ostream& operator<< (ostream& os, TComplex c){
    os<<"("<<c.real<<"+"<<c.imaginary<< "i)";
    return os;
}
istream& operator>> (istream& is, TComplex& c){
    is>>c.real>>c.imaginary;
    return is;
}

TComplex TComplex::operator - (const TComplex& other)const{
    TComplex t;
    t.real = real - other.real;
    t.imaginary = imaginary - other.imaginary;
    return t;
}
TComplex TComplex::operator+(const TComplex& other) const{
    TComplex t;
    t.real = real + other.real;
    t.imaginary = imaginary + other.imaginary;
    return t;
}
TComplex TComplex::operator*( TComplex c) const {
    TComplex t;
    t.real = real*c.real - imaginary*c.imaginary;
    t.imaginary = real*c.imaginary - imaginary*c.real;
    return t;
}
// Оператор умножения для комплексного числа и целого числа
TComplex TComplex::operator*(int n) const {
    TComplex t;
    t.real = real * n;
    t.imaginary = imaginary * n;
    return t;
}
// Оператор умножения для целого числа и комплексного числа
TComplex operator*(int n, const TComplex& c) {
    return c * n; // Используем уже реализованный оператор умножения
}
TComplex TComplex::operator/(TComplex& other)  {
    double denominator = other.real * other.real + other.imaginary * other.imaginary;
    TComplex t;
    t.real = (real * other.real + imaginary * other.imaginary) / denominator;
    t.imaginary = (imaginary * other.real - real * other.imaginary) / denominator;
    return t;
 }
TComplex TComplex:: operator/= ( TComplex& other) {
    *this = *this / other;
    return *this;
}
bool TComplex::operator== (TComplex c){
    return  (real == c.real) && (imaginary==c.imaginary);
}
bool TComplex::operator>( const TComplex& other){
    return abs () > other.abs();
}
double TComplex::abs() const {
    return sqrt(real * real + imaginary * imaginary);
}
TComplex abs(const TComplex& t) {
    double modulus = sqrt(t.real * t.real + t.imaginary * t.imaginary);
    return modulus;
}