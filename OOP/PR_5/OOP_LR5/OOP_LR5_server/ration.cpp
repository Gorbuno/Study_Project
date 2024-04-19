#include "ration.h"

TRational::TRational(int numerator, int denominator)
        : m_numerator(numerator), m_denominator(denominator) {
    normalize();}

int TRational::numerator() const {
    return m_numerator;}

int TRational::denominator() const {
    return m_denominator;}

void TRational::normalize() {
    if (m_denominator == 0) {
        throw std::invalid_argument("Denominator cannot be zero.");}
    if (m_denominator < 0) {
        m_numerator = -m_numerator;
        m_denominator = -m_denominator;}
    int gcdValue = gcd(m_numerator, m_denominator);
    m_numerator /= gcdValue;
    m_denominator /= gcdValue;}

int TRational::gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;}
    return a;}

TRational TRational::operator+(const TRational &other) const {
    return TRational(m_numerator * other.m_denominator + other.m_numerator * m_denominator,
                     m_denominator * other.m_denominator);}

TRational TRational::operator-(const TRational &other) const {
    return TRational(m_numerator * other.m_denominator - other.m_numerator * m_denominator,
                     m_denominator * other.m_denominator);}

TRational TRational::operator*(const TRational &other) const {
    return TRational(m_numerator * other.m_numerator,
                     m_denominator * other.m_denominator);}

TRational TRational::operator*(int integer) const {
    return TRational(m_numerator * integer, m_denominator);}

TRational operator*(int integer, const TRational &rational) {
    return rational * integer;}

TRational TRational::operator/(const TRational &other) const {
    if (other.m_numerator == 0) {
        throw std::invalid_argument("Division by zero.");}
    return TRational(m_numerator * other.m_denominator,
                     m_denominator * other.m_numerator);}

TRational &TRational::operator/=(const TRational &other) {
    if (other.m_numerator == 0) {
        throw std::invalid_argument("Division by zero.");}
    m_numerator *= other.m_denominator;
    m_denominator *= other.m_numerator;
    normalize();
    return *this;}

bool TRational::operator==(const TRational &other) const {
    return m_numerator == other.m_numerator && m_denominator == other.m_denominator;}

bool TRational::operator!=(const TRational &other) const {
    return !(*this == other);}

bool TRational::operator>(const TRational &other) const {
    double thisValue = static_cast<double>(m_numerator) / m_denominator;
    double otherValue = static_cast<double>(other.m_numerator) / other.m_denominator;
    return thisValue > otherValue;}

std::ostream &operator<<(std::ostream &os, const TRational &r) {
    os << r.m_numerator << "/" << r.m_denominator;
    return os;}

std::istream &operator>>(std::istream &is, TRational &r) {
    int numerator, denominator;
    char slash;
    is >> numerator >> slash >> denominator;
    if (!is) {
        return is;}
    if (slash != '/') {
        is.setstate(std::ios::failbit);
        return is;}
    r = TRational(numerator, denominator);
    return is;}

TRational abs() {
    TRational t;
    return TRational(abs(t.m_numerator), t.m_denominator);}

TRational abs(const TRational &) {
    TRational t;
    return TRational(abs(t.m_numerator), t.m_denominator);}

QString TRational::toString() const {
    return QString("%1/%2").arg(numerator()).arg(denominator());}
