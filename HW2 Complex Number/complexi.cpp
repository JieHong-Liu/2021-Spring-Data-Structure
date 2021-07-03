#include "complex.h"
#include <math.h>
using namespace std;

//          CONSTRUCTOR
complex::complex(const complex &c)
{
    this->real = c.real;
    this->imag = c.imag;
}

//        COPY CONSTRUCTOR
complex &complex::operator=(const complex &c)
{
    real = c.real;
    imag = c.imag;
    return *this;
}

complex complex::operator+(const complex &c)
{
    complex tmp, tmp1 = *this, tmp2(c);
    cout << "\n performing C1 + C2 =" << tmp1 << "+" << tmp2 << " =";
    tmp.real = this->real + c.real;
    tmp.imag = this->imag + c.imag;
    return tmp;
}

complex complex::operator-(const complex c)
{
    complex tmp(0, 0), tmp1 = *this, tmp2 = c;
    cout << "\n performing C1 - C2 =" << tmp1 << "-" << tmp2 << " =";
    /*   you have to implement the code   */
    tmp.real = this->real - c.real;
    tmp.imag = this->imag - c.imag;
    return tmp;
}

complex complex::operator*(const complex c)
{
    complex tmp(0, 0), tmp1 = *this, tmp2 = c;
    cout << "\n performing C1 * C2 =" << tmp1 << "*" << tmp2 << " =";
    /*   you have to implement the code   */
    tmp.real = tmp1.real * tmp2.real - tmp1.imag * tmp2.imag;
    tmp.imag = tmp1.real * tmp2.imag + tmp1.imag * tmp2.real;
    return tmp;
}

complex complex::operator/(const complex c)
{
    complex tmp(0, 0), tmp1 = *this, tmp2 = c;
    cout << "\n performing C1 / C2 =" << tmp1 << "/" << tmp2 << " =";
    float mom = tmp2.real * tmp2.real + tmp2.imag * tmp2.imag;
    // [(ac+bd)+(bc-ad)i]/(c^2+d^2)
    tmp.real = (tmp1.real * tmp2.real + tmp1.imag * tmp2.imag) / mom;
    tmp.imag = (tmp1.imag * tmp2.real - tmp1.real * tmp2.imag) / mom;
    return tmp;
}

complex complex::getconjugate()
{
    complex tmp(0, 0);
    cout << "\n performing C2 = conjugate(C1) =" << endl;
    /* you have to implement the code*/
    tmp.real = this->real;
    tmp.imag = this->imag * -1;
    return tmp;
}

complex complex::getreciprocal()
{
    // Performing C^(-1)
    complex t(0,0);
    float mom = this->real * this->real + this->imag * this->imag;
    t.real = this->real / mom;
    t.imag = (this->imag / mom) * -1;

    return t;
}

float complex::getmodulus()
{
    complex tmp = *this;
    cout << "\n performing |C| =" << "|" << tmp << "| = ";
    float z = tmp.real * tmp.real + tmp.imag * tmp.imag;
    z = sqrt(z);
    return z;
}

void complex::setdata(float r, float i)
{
    real = r;
    imag = i;
}

void complex::getdata()
{
    cout << "Enter Real:";
    cin >> this->real;
    cout << "Enter Imaginary:";
    cin >> this->imag;
}

float complex::getreal()
{
    return real;
}

float complex::getimaginary()
{
    return imag;
}
bool complex::operator==(const complex &c)
{
    return (real == c.real) && (imag == c.imag) ? 1 : 0;
}

ostream &operator<<(ostream &s, complex &c)
{

    s << " (" << c.real << setiosflags(ios::showpos)
      << c.imag << "i"
      << ") " << resetiosflags(ios::showpos);
    return s;
}
