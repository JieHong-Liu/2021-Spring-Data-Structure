#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include "ChainIterator.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <math.h>

using namespace std;

struct Term // all members of Term are public by default
{
	int coef;	//coefficient
	int exp;	// exponential lorder
	Term Set(int c, int e) { coef = c; exp = e;  return *this; };
	Term Set(ChainNode <Term> temp) {
		Term data = temp.GetData();
		coef = data.coef; exp = data.exp;
		return *this;
	};
};
class Polynomial {
	friend ostream& operator<<(ostream&, Polynomial&);
	friend istream& operator>>(istream&, Polynomial&);
public:
	Polynomial(Chain <Term>ll) :poly(ll) { };
	Polynomial() {};
	//~Polynomial() { this->free(); };
	Polynomial operator+(const Polynomial&) const;
	Polynomial operator*(const Polynomial&) const;
public:
	Chain <Term> poly;
	void free();
};

// The destructor automatically delete a linkted list data but 
// it conflicts with an operator overloading function p3 = p1 + p2;
void Polynomial::free() { // Free all nodes in the chain
	poly.free();
}

Polynomial Polynomial::operator*(const Polynomial& b) const
{
	Polynomial c;

	for (ChainIterator<Term> ai(poly); ai.current; ai++)
	{
		for (ChainIterator<Term> bi(b.poly); bi.current; bi++) //
		{
			Term tmp;
			bool finished = 0;
			tmp.Set((ai->coef) * (bi->coef), (ai->exp + bi->exp));
			for (ChainIterator<Term> ci(c.poly); ci.current; ci++)
			{
				if (tmp.exp == ci->exp)
				{
					ci->coef += tmp.coef;
					finished = true;
					break;
				}
			}
			if (finished == false)
			{
				c.poly.InsertInorderB(tmp);
			}
		}
	}
	return c;
};



Polynomial Polynomial::operator+(const Polynomial& b) const
{
	// 相加多項式 *this（a）與b並且回傳它們的和
	Term temp;
	ChainIterator <Term> ai(poly), bi(b.poly);
	Polynomial c;
	while (ai.current && bi.current) { // 目前的節點不是空的
		if (ai->exp == bi->exp) {
			int sum = ai->coef + bi->coef;
			if (sum) c.poly.InsertBack(temp.Set(sum, ai->exp));
			ai++; bi++; // 前進至下一個項目
		}
		else if (ai->exp < bi->exp) {
			c.poly.InsertBack(temp.Set(bi->coef, bi->exp));
			bi++; // b的下一個項目
		}
		else {
			c.poly.InsertBack(temp.Set(ai->coef, ai->exp));
			ai++; // a的下一個項目
		}
	}
	while (ai.current) { // 複製a剩下的部份
		c.poly.InsertBack(temp.Set(ai->coef, ai->exp));
		ai++;
	}
	while (bi.current) { // 複製b剩下的部份
		c.poly.InsertBack(temp.Set(bi->coef, bi->exp));
		bi++;
	}
	return c;
};

ostream& operator<<(ostream& out, Polynomial& p) {

	ChainIterator <Term> ci(p.poly);
	ChainIterator <Term> ct(p.poly);
	char sign;
	out << "(";
	while (ct.NotNull())
	{
		sign = ct->coef > 0 ? '+' : '-';
		out << ' ' << sign << ' ' << fabs(ct->coef) << "x^" << ct->exp;
		ct++;
	}
	out << ")";
	return out;
};

istream& operator>>(istream& is, Polynomial& p)
// read in a polynomial  and set up its linked representation.
{
	int i, nterm;
	Term s;
	is >> nterm;
	for (i = 0; i < nterm; i++) {
		is >> s.coef >> s.exp; // matrix dimensions
		p.poly.InsertBack(s);
	}
	return is;
};

void LOGO() {
	cout << "===============================================================\n"
		<< "       Linked Polynomial Lecture 4 Part I: p44-p47 \n"
		<< "      Designed and verified by Jiann-Jone Chen 2021\n"
		<< "		Student B10707128 Jie-Hong Liu\n"
		<< "================================================================\n\n";
}
#endif
