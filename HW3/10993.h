#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

class Polynomial
{

public:
    Polynomial();
    Polynomial(const int , const int [51]);
    Polynomial add( const Polynomial) const; // add function
    Polynomial subtract( const Polynomial ) const; // subtract function
    Polynomial multiplication( const Polynomial ) const; // multiplication function
    void output() const;
private:
    int coefficients[101]; // integer coefficients
    int greatestPower; // integer greatestPower
}; // end class Polynomial

/////////////////////////////////////////////////////////////////////////////////////

Polynomial::Polynomial() {
    this->greatestPower=0;
    for (int i = 0 ; i < 101 ; i++)
        this->coefficients[i] = 0;
}

Polynomial::Polynomial(const int N, const int temp[51]) {
    this->greatestPower = N;
    for (int i = N ; i >= 0 ; i--)
        this->coefficients[i] = temp[i];
}

Polynomial Polynomial::add(const Polynomial b) const {
    Polynomial temp;

    if (this->greatestPower >= b.greatestPower) temp.greatestPower = this->greatestPower;
    else temp.greatestPower = b.greatestPower;

    for (itn i = 0 ; i <= this->greatestPower ; i++)
        temp.coefficients[i] = this->coefficients[i];
    for (int i = 0 ; i <= b.greatestPower ; i++)
        temp.coefficients[i] += b.coefficients[i];
    return temp;
}

Polynomial Polynomial::subtract(const Polynomial b) const {
    Polynomial temp;

    if (this->greatestPower >= b.greatestPower) temp.greatestPower = this->greatestPower;
    else temp.greatestPower = b.greatestPower;

    for (itn i = 0 ; i <= this->greatestPower ; i++)
        temp.coefficients[i] = this->coefficients[i];
    for (int i = 0 ; i <= b.greatestPower ; i++)
        temp.coefficients[i] -= b.coefficients[i];
    return temp;
}

Polynomial Polynomial::multiplication(const Polynomial b) const {
    Polynomial temp;

    temp.greatestPower = this->greatestPower + b.greatestPower;

    for (itn i = 0 ; i <= this->greatestPower ; i++)
        for (int j = 0 ; j <= b.greatestPower ; j++)
            temp.coefficients[i+j] += this->coefficients[i] * b.coefficients[j];
    return temp;
}

void Polynomial::output() const {
    for (int i = this->greatestPower ; i >= 0 ; i--)
        if (!i) cout << this->coefficients[i];
        else cout << this->coefficients[i] << " ";
}


/*
I:
2
1 2 3
3
1 1 1 1

O:
1 2 3 4
-1 0 1 2
1 3 6 6 5 3
*/
#endif

