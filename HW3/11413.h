#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>
using namespace std;
class Rational
{
    public:
        Rational( int = 0, int = 1 ); // default constructor
        Rational addition( const Rational & ) const; // function addition
        Rational multiplication( const Rational & ) const; // function multi.
        void printRational () const; // print rational format

    private:
        int numerator; // integer numerator
        int denominator; // integer denominator
        void reduce();
}; // end class Rational

int gcd(int a, int b);

////////////////////////////////////////////////////////////////////////////

Rational::Rational(int num, int den) {
    this->numerator = num;
    this->denominator = den;
    this->reduce();
}

Rational Rational::addition(const Rational &that) const {
    Rational temp;

    temp.numerator = this->numerator * that.denominator + that.numerator * this->denominator;
    temp.denominator = this->denominator * that.denominator;
    temp.reduce();

    return temp;
}

Rational Rational::multiplication(const Rational &that) const {
    Rational temp;

    temp.numerator = this->numerator * that.numerator;
    temp.denominator = this->denominator * that.denominator;
    temp.reduce();

    return temp;
}

void Rational::printRational() const {
    cout << this->numerator << "/" << this->denominator << endl;
}

void Rational::reduce() {
    int root = gcd(this->numerator, this->denominator);
    this->numerator /= root;
    this->denominator /= root;
    if (this->denominator<0) {
        this->numerator *= -1;
        this->denominator *=-1;
    }
}

/*
I:
+ 1 3 2 3
* 6 5 7 8
O:
1/1
21/20
*/
#endif
