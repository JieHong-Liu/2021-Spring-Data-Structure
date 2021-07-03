#include "Polynomial.h"

int main()
{
     Polynomial a, b, c, d;
     a.set(7, 4); //7x^4
     a.set(2, 2);
     a.set(1, 2); //x^2
     b.set(6, 3);  //6x^3
     b.set(-3, 2); //-3x^2
     c = a - b;    // (7x^4 + x^2) - (6x^3 - 3x^2) operator overloading of "-"
     cout << a << " - " << b << " = " << c << endl
          << endl; // print out the c polynomial
     c = a + b;
     cout << a << " + " << b << " = " << c << endl
          << endl; // operator overloading of "+"

     c = a * b; // (7x^4 + x^2) * (6x^3 - 3x^2), operator overloading of "*"
     cout << a << " * " << b << " = " << c << endl
          << endl; // operator overloading for output polynomial

     cout << "The degree of c is " << c.degree() << endl
          << endl; // test for degree

     d = c.differentiate().differentiate().differentiate().differentiate().differentiate();
     cout << "differentiate " << c << "two times lead to: " << endl
          << endl;
     cout << d << endl
          << endl; // operator overloading <<
     cout << c(2) << endl
          << endl; // evaluate the polynomial with x=2 by horner's method
     cin.get();
}
