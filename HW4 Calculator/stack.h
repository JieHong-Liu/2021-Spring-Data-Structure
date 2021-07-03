// header file of stack
#pragma once
#include <iostream>
#define DefaultSize 10
using namespace std;
template <typename KeyType>
class Stack
{
public:
    Stack(int MaxStackSize = DefaultSize); // constructor of stack
    ~Stack();
    bool isEmpty() const;           // return true if stack is empty, vice versa.
    KeyType Top() const;            // return the top "element" of the stack, add const to prevent you change the value of Top element.
    void Push(const KeyType &item); // Insert the item into the stack
    void Pop();                     // delete the top "element" of the stack
    // friend ostream &operator<<(ostream &outputString, const Stack<KeyType> &s);

private:
    KeyType *stack;
    int top;
    // array position of top element, top will always be the toppest item index + 1.
    // in the beginning, the top is 0, since there is no item in the stack.
    int MaxSize; // Max size of the stack (capacity)
};

template <typename KeyType>
Stack<KeyType>::Stack(int MaxStackSize) // put the argument MaxStackSize into our object Stack's parameter Maxsize.
{
    this->MaxSize = MaxStackSize;
    this->stack = new KeyType[MaxSize];
    this->top = 0; // top index
}

template <typename KeyType>
Stack<KeyType>::~Stack()
{
    delete[] this->stack;
}

template <typename KeyType>
bool Stack<KeyType>::isEmpty() const
{
    if (this->top == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

template <typename KeyType>
KeyType Stack<KeyType>::Top() const
{
    return this->stack[this->top - 1];
}

template <typename KeyType>
void Stack<KeyType>::Push(const KeyType &item)
{
    if (this->top < (this->MaxSize))
    {
        // cout << "The element you push is " << item << endl;
        this->stack[this->top] = item;
        top++;
    }
    else
    {
        cout << "The element you want to push is " << item << endl;
        std::cout << "But The memory of stack is fulled." << endl
                  << endl;
    }
}

template <typename KeyType>
void Stack<KeyType>::Pop()
{
    KeyType top_value;
    if (this->top > 0)
    {
        top_value = (this->stack[top - 1]);
        (this->top)--;
    }
    else
    {
        // std::cerr << "There is no element in the stack." << endl;
    }
}