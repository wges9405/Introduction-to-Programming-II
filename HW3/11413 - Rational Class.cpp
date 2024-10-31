#include <iostream>
#include "11413.h" // include definition of class Rational
using namespace std;

int main()
{
    char s1;
    int s2, s3, s4, s5;

    Rational x;
    while(cin >>s1>>s2>>s3>>s4>>s5)
    {
        if(cin.eof())
        {
		    break;
        }
        Rational c(s2, s3), d(s4, s5);
        if(s1 == '+')
        {
            x = c.addition( d ); // adds object c and d; sets the value to x
            x.printRational(); // prints rational object x
        }
        else if(s1 == '*')
        {
            x = c.multiplication( d ); // multiplies object c and d
            x.printRational(); // prints rational object x
        }
    }
}

int gcd(int a, int b){
    return (b == 0) ? a : gcd(b, a % b);
}
