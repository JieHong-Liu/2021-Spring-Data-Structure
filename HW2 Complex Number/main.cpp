#include "complex.h" 
using namespace std;

int main()
{
	complex a(10.0f, -2.f); // Calls Constructor
	cout << a << endl;               // Calls the overloaded << operator
	complex b(-2);         // Calls Constructor
	complex c = a;                    // Calls Copy Constructor
	c = a;                          // calls overloaded = operator
	b.getdata();                    // Calls Getdata()
	c.getdata();
	if (b == c)            // calls overloaded == operator
		cout << "b == c";
	else
		cout << "b != c";
	c = a;
	cout << c.getmodulus() << endl; // calls the getmodulus() function
	cout << "Performing C*C^(-1) = " <<
		c * c.getreciprocal() << endl; // calls the receiprocal() function
	cout << a + b << endl;      // Calls overloaded + and <<
	cout << a - b << endl;     // Calls overloaded -  and << 
	cout << a * b << endl;     // calls overloaded *  and << 
	cout << a / b << endl;     // calls overloaded / and <<
	cout << (a + b) * (a - b) / c << endl;  // combine + - * / operations
	cout << "The conjugate of a is " << a.getconjugate() << endl;
	getchar();
	return 0;
}