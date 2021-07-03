// A Polynomial Class
#include <iostream>
using namespace std;

class Polynomial;
// This hw is done by method 3
class Term
{
    friend Polynomial;

public:
    Term() // constructor of Term
    {
        this->coef = 0;
        this->exp = 0;
    }
    float getCoef()
    {
        return this->coef;
    }
    int getExp()
    {
        return this->exp;
    }
    Term &operator=(Term &T)
    {
        if (this == &T)
        {
            return *this;
        }
        else
        {
            this->coef = T.coef;
            this->exp = T.exp;
        }
        return *this;
    }

private:
    float coef; // coefficient
    int exp;    // exponential
};

class Polynomial
{
private:
    Term *termArray; // Array of nonzero terms;
    int capacity;    // temp size of termArray -> the max size of tempArray
    int terms;       // number of nonzero terms;

    void swap_term(Term &A, Term &B)
    {
        Term tmp;
        tmp = A;
        A = B;
        B = tmp;
    }

    void sort_termArray() // sort before cout
    {
        for (int i = 0; i < (this->terms) - 1; i++)
        {
            for (int j = 0; j < (this->terms) - i - 1; j++)
            {
                if (termArray[j].exp < termArray[j + 1].exp)
                {
                    swap_term(termArray[j], termArray[j + 1]);
                }
            }
        }
    }

public:
    Polynomial() //default constructor
    {
        termArray = NULL;
        capacity = 1; // reserve the size
        terms = 0;
    }

    void set(float a, int b) // setter function -> set(7,4) = 7x^4
    {
        int finished = 0;
        if ((this->terms) == (this->capacity))
        {
            this->capacity *= 2;
        }
        for (int i = 0; i < this->terms; i++)
        {
            if (b == this->termArray[i].exp)
            {
                this->termArray[i].coef = a;
                finished = 1;
                break;
            }
        }
        if (finished == 0)
        {
            Term *new_termArray = new Term[capacity];
            for (int i = 0; i < (this->terms); i++)
            {
                new_termArray[i] = this->termArray[i]; // put old value into new_termArray
            }
            delete[] this->termArray;
            if (terms < capacity) // make sure that term is always less than capacity
            {
                (new_termArray[terms]).coef = a;
                (new_termArray[terms]).exp = b;
            }
            this->termArray = new_termArray; // point my termArray to the new_termArray
            this->terms = this->terms + 1;
        }
    }
    // Return the degree of this polynomial,
    // i.e., the highest exponential order
    int degree()
    {
        int max_deg = 0;
        for (int i = 0; i < (this->terms); i++)
        {
            if (termArray[i].exp > max_deg && termArray[i].coef != 0)
            {
                max_deg = termArray[i].exp;
            }
        }
        return max_deg;
    }

    friend ostream &operator<<(ostream &os, Polynomial &s)
    {
        s.sort_termArray();
        os << "(";
        for (int i = 0; i < s.terms; i++)
        {
            if (s.termArray[i].getCoef() != 0)
            {
                if (i != 0 && s.termArray[i].getCoef() >= 0)
                {
                    os << "+";
                }
                if (s.termArray[i].getCoef() != 1 || s.termArray[i].getExp() == 0)
                {
                    os << s.termArray[i].getCoef();
                }
                if (s.termArray[i].getExp() != 0)
                {
                    os << "x^" << s.termArray[i].getExp();
                }
            }
        }
        os << ")";
        return os;
    }
    // use Horner's method to compute and return the polynomial evaluated at x
    // https://www.youtube.com/watch?v=RGrmEWj38bs
    // return the polynomial evaluation with value x,
    // i.e., if c(x) = 2x^2 + 3, then c(2)= 11
    // this is the operator overloading format function.

    int operator()(int x)
    {
        this->sort_termArray();
        Polynomial tmp_poly = *this;
        tmp_poly.terms = this->termArray[0].exp + 1;
        tmp_poly.termArray = new Term[tmp_poly.termArray[0].exp + 1];
        for (int i = 0; i < tmp_poly.terms; i++)
        {
            if (i < this->terms)
            {
                tmp_poly.termArray[i] = this->termArray[i];
            }
            else
            {
                tmp_poly.termArray[i].coef = 0.0;
                tmp_poly.termArray[i].exp = 0;
            }
        }
        double result = tmp_poly.termArray[0].coef;
        // Evaluate value of polynomial using Horner's method
        for (int i = 1; i < tmp_poly.terms; i++)
        {
            result = result * x + tmp_poly.termArray[i].coef;
        }

        return result;
    }

    // differentiate this polynomial and return it
    Polynomial differentiate() const
    {
        Polynomial derivation = *this;
        derivation.termArray = new Term[derivation.terms];
        for (int i = 0; i < this->terms; i++)
        {
            derivation.termArray[i].coef = this->termArray[i].coef;
            derivation.termArray[i].exp = this->termArray[i].exp;
        }
        bool has_constant = false;
        for (int i = 0; i < this->terms; i++)
        {
            derivation.termArray[i].coef = derivation.termArray[i].coef * derivation.termArray[i].exp;
            derivation.termArray[i].exp -= 1;
            if (termArray[i].exp == -1)
            {
                has_constant = true;
            }
        }
        if (has_constant)
        {
            derivation.sort_termArray();
            derivation.terms--;
        }
        return derivation;
    }

    //polynomial addition
    Polynomial operator+(Polynomial &b)
    {
        Polynomial ans;
        if (this->capacity < b.capacity)
        {
            ans.capacity = b.capacity;
        }
        else
        {
            ans.capacity = this->capacity;
        }
        Term *new_termArray = new Term[ans.capacity];
        ans.terms = this->terms;
        for (int i = 0; i < (ans.terms); i++)
        {
            new_termArray[i] = this->termArray[i]; // put old value into new_termArray
        }
        ans.termArray = new_termArray;

        for (int b_index = 0; b_index < b.terms; b_index++)
        {
            int same_exp = 0;
            for (int i = 0; i < (this->terms); i++)
            {
                if (b.termArray[b_index].getExp() == this->termArray[i].getExp())
                {
                    ans.termArray[i].coef = this->termArray[i].coef + b.termArray[b_index].getCoef();
                    same_exp = 1;
                    break;
                }
            }
            if (!same_exp)
            {
                ans.set(b.termArray[b_index].getCoef(), b.termArray[b_index].getExp());
            }
        }
        return ans;
    }
    // polynomial sub
    Polynomial operator-(Polynomial &b)
    {
        Polynomial ans;
        if (this->capacity < b.capacity)
        {
            ans.capacity = b.capacity;
        }
        else
        {
            ans.capacity = this->capacity;
        }
        Term *new_termArray = new Term[ans.capacity];
        ans.terms = this->terms;
        for (int i = 0; i < (ans.terms); i++)
        {
            new_termArray[i] = this->termArray[i]; // put old value into new_termArray
        }
        ans.termArray = new_termArray;

        for (int b_index = 0; b_index < b.terms; b_index++)
        {
            int same_exp = 0;
            for (int i = 0; i < (this->terms); i++)
            {
                if (b.termArray[b_index].getExp() == this->termArray[i].getExp())
                {
                    ans.termArray[i].coef = this->termArray[i].coef - b.termArray[b_index].getCoef();
                    same_exp = 1;
                    break;
                }
            }
            if (!same_exp)
            {
                ans.set(-1 * b.termArray[b_index].getCoef(), b.termArray[b_index].getExp());
            }
        }
        return ans;
    }

    Polynomial &operator=(Polynomial &p) // operator '=' overloading
    {
        if (this == &p)
        {
            return *this;
        }
        else
        {
            this->capacity = p.capacity;
            this->terms = p.terms;
            delete[] this->termArray;
            this->termArray = p.termArray;
            return *this;
        }
    }

    Polynomial operator*(Polynomial &b) // polynomial multiplication
    {
        // initialize
        Polynomial product;

        for (int i = 0; i < b.terms; i++)
        {
            Term *tmp_termArray = new Term[this->terms];
            int tmp_index = 0;
            for (int j = 0; j < this->terms; j++)
            {
                tmp_termArray[tmp_index].coef = this->termArray[j].coef * b.termArray[i].coef;
                tmp_termArray[tmp_index].exp = this->termArray[j].exp + b.termArray[i].exp;
                tmp_index++;
            }
            Polynomial tmp_product;
            tmp_product.capacity = this->capacity;
            tmp_product.termArray = tmp_termArray;
            tmp_product.terms = this->terms;
            product = product + tmp_product;
        }
        return product;
    }
};
