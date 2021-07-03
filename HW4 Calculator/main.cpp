#include "stack.h"
#include "postfix.h"
#include <cmath>
#include <string>
float Eval(vector<Token> &postfix);
string deleteSpace(string infix);
int main()
{
    string infix;
    char cont;
    do
    {
        cin.ignore(); // clear the buffer.
        system("CLS");
        cout << "Enter the infix expression:" << endl;
        cout << "INFIX : ";
        getline(cin, infix);
        infix = deleteSpace(infix);
        bool wrong = 0;
        if (infix[0] != '(' && infix[0] != '-' && infix[0] != '#' && (infix[0] < '0' || infix[0] > '9'))
        {
            wrong = 1;
        }
        else
        {
            Stack<char> brackets;
            for (int i = 0; (i < infix.size()) && (infix[i] != '#'); i++)
            {
                if (infix[i] == '(')
                {
                    brackets.Push(infix[i]);
                }
                else if (infix[i] == ')')
                {
                    if (brackets.isEmpty())
                    {
                        wrong = 1;
                        break;
                    }
                    else
                    {
                        brackets.Pop();
                    }
                }
                else if (infix[i] != '+' && infix[i] != '-' && infix[i] != '*' && infix[i] != '/' && infix[i] != '.' && infix[i] != ' ' && infix[i] != '^' && (infix[i] < '0' || infix[i] > '9'))
                {
                    wrong = 1;
                    break;
                }
            }
            if (!brackets.isEmpty())
            {
                wrong = 1;
            }
        }

        if (wrong == 1)
        {
            cout << "The infix expression is invalid!\n";
        }
        else
        {
            vector<Token> postfix = in2post(infix);
            cout << "Evaluate " << infix << " = " << Eval(postfix) << endl
                 << endl;
        }
        cout << "Continue?(Y/N): ";
        cont = getchar();
    } while (cont == 'Y' || cont == 'y');

    return 0;
}

float Eval(vector<Token> &postfix)
{
    Stack<float> ans_stack(postfix.size());
    for (int i = 0; i < postfix.size(); i++)
    {
        if (postfix[i].is_number == true)
        {
            ans_stack.Push(postfix[i].f);
        }
        else if (postfix[i].is_number == false && postfix[i].c == 'u')
        {
            float v = ans_stack.Top();
            v = -v;
            ans_stack.Pop();
            ans_stack.Push(v);
        }
        else if (postfix[i].is_number == false)
        {
            float left_term, right_term;
            right_term = ans_stack.Top();
            ans_stack.Pop();
            left_term = ans_stack.Top();
            ans_stack.Pop();
            switch (postfix[i].c)
            {
            case '+':
            {
                float ans = left_term + right_term;
                ans_stack.Push(ans);
                break;
            }
            case '-':
            {
                float ans = left_term - right_term;
                ans_stack.Push(ans);
                break;
            }
            case '*':
            {
                float ans = left_term * right_term;
                ans_stack.Push(ans);
                break;
            }
            case '/':
            {
                float ans = left_term / right_term;
                ans_stack.Push(ans);
                break;
            }
            case '^':
            {
                float ans = pow(left_term, right_term);
                ans_stack.Push(ans);
                break;
            }
            }
        }
    }
    return ans_stack.Top();
}

string deleteSpace(string infix)
{
    stringstream ss(infix);
    string ifix = "", tmp_str;
    while (ss >> tmp_str)
    {
        ifix = ifix + tmp_str;
    }
    return ifix;
}