#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include "stack.h"
using namespace std;
class Token
{
public:
    float f;
    char c;
    bool is_number;
    Token() : is_number(false), c(0){};
};

int weight_calculator(char c);

vector<Token> in2post(string infix)
{
    stringstream ss(infix);
    Stack<char> op_stack(infix.length());
    vector<Token> postfix;
    bool unary = true; // first time.
    while (ss.peek() != -1 && ss.peek() != '#')
    {
        Token t;
        float x;
        char op;
        if (ss.peek() >= '0' && ss.peek() <= '9') // a number.
        {
            unary = false;
            ss >> t.f;
            t.is_number = true;
            postfix.push_back(t);
        }
        else
        {
            if (ss.peek() == ' ')
            {
                ss.get();
            }
            else if (ss.peek() == '(')
            {
                ss >> op;
                op_stack.Push(op);
                unary = true;
            }
            else if (ss.peek() == ')')
            {
                unary = false;
                ss >> op;
                while (!op_stack.isEmpty() && op_stack.Top() != '(')
                {

                    t.is_number = false;
                    t.c = op_stack.Top();
                    postfix.push_back(t);

                    op_stack.Pop();
                }
                op_stack.Pop(); // remove the '('.
            }
            else if (ss.peek() == '-' && unary == true)
            {
                ss >> op;
                op = 'u';
                op_stack.Push(op);
                unary = false;
            }
            else if (op_stack.isEmpty() || weight_calculator(ss.peek()) > weight_calculator(op_stack.Top()))
            {
                unary = false;
                ss >> op;
                op_stack.Push(op);
            }
            else if (weight_calculator(ss.peek()) <= weight_calculator(op_stack.Top()))
            {
                unary = false;
                while (!op_stack.isEmpty() && (weight_calculator(op_stack.Top()) >= weight_calculator(ss.peek())))
                {
                    t.is_number = false;
                    t.c = op_stack.Top();
                    postfix.push_back(t);
                    op_stack.Pop();
                }
                ss >> op;
                op_stack.Push(op);
            }
        }
    }

    while (!op_stack.isEmpty())
    {
        Token t;
        t.is_number = false;
        t.c = op_stack.Top();
        postfix.push_back(t);
        op_stack.Pop();
    }

    cout << "POSTFIX: ";
    for (int i = 0; i < postfix.size(); i++)
    {
        // cout << postfix[i] << " ";
        if (postfix[i].is_number == true)
        {
            cout << postfix[i].f << " ";
        }
        else
        {
            cout << postfix[i].c << " ";
        }
    }
    cout << endl;

    return postfix;
}

int weight_calculator(char c)
{
    char priority[8] = {'+', '-', '*', '/', '^', '(', ')', 'u'};
    int weight[8] = {1, 1, 2, 2, 4, 0, 0, 3};

    for (int i = 0; i < 8; i++)
    {
        if (c == priority[i])
        {
            return weight[i];
        }
    }
    return -1; // not found.
}