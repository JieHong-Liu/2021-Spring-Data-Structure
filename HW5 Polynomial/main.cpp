#include "ChainNode.h"
// #include "Polynomial.h"
#include "Polynomial.h"
#include <iostream>
#include <fstream>
#include <ostream>
using namespace std;
int main() {
	Polynomial p1, p2,p3,p4;   LOGO();
	ifstream inFile("polynomial.txt", ios::in); //"equiv.in" is th input file
	if (!inFile) { cerr << "Cannot open input file" << endl; return 0; }
	inFile >> p1;
	inFile >> p2;

	 p3 = p1 + p2;
	cout << p1 << " + " << p2 << " =\n " << p3 << "\n\n";

	 p4 = p3 + p1 * p2;
	cout << p3 << '+' << p1 << " * " << p2 << " = \n" << p4 << "\n\n";

	p1.free(); p2.free(); p3.free();
	getchar();
	return 0;
};

