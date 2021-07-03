#include <cmath>
#include <iostream>
#include <iomanip>
#include <ostream>
using namespace std;

class complex
{
   public:
         float real;      // Real Part
         float imag;      //  Imaginary Part

   public:
 
	   complex::complex(float r=0,float im=0):real(r),imag(im)
	   {}
          complex(const complex&);
          complex operator +(const complex&);
          complex operator -(const complex);
          complex operator *(const complex);
          complex operator /(const complex);
          complex getconjugate();
          complex getreciprocal();
          float getmodulus();
          void setdata(float,float);
          void getdata();
          float getreal();
          float getimaginary();
          bool operator ==(const complex&);
          complex& operator =(const complex&);
          friend ostream & operator<<(ostream &s,complex &c);
};


