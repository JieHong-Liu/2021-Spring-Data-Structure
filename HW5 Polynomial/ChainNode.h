#ifndef CHAIN_NODE_H
#define CHAIN_NODE_H

#include "ChainIterator.h"
#include <iostream>
#include <ostream>
using namespace std;

template<class T> class Chain;
template<class T> class ChainIterator; // new added from previos LinkedChain program 

//*****  ChainNode Template Class 
template <class T>
class ChainNode {
public:
	//	friend ostream &operator<<(ostream &, Polynomial &);
	friend class Chain <T>;
	friend class ChainIterator <T>; // new added for iterator
	template <class T> friend ostream& operator<<(ostream&, Chain<T>&);
	friend class Polynomial;
	T GetData() { return data; };
	ChainNode <T>* GetLink() { return link; };
	ChainNode(T element = 0) { data = element; link = 0; };
	//	Set(T d):data(d){};
private:
	T data;
	ChainNode<T>* link;
};

// *********Chain Template Class *********************
template<class T>
class Chain {
	template <class T> friend ostream& operator<<(ostream&, Chain<T>&);
	friend class ChainIterator<T>; // New Added for Iterator
	friend class Polynomial;
public:
	Chain() { first = last = 0; }; // constructor initializing first to 0
	// Chain(const Chain<T> &l); // copy constructor
	// Chain manipulation operations
	~Chain();// destructor to free all allocated memory space, got some trouble
	void Create2(T, T);
	void Insert(ChainNode<T>*, T);
	void Delete(ChainNode<T>*, ChainNode<T>*);
	void InsertBack(const T& e);
	void InsertInorder(const T& e);
	void InsertInorderB(const T& e);
	ChainNode<T>* FirstNode() { return first; };
	void PrintChain();
	void free();
private:
	ChainNode <T>* first, * last;
	ChainNode <T>* current;
};

/* free memory space by destructor may lead to unexpected semantic error.
   So we design another free() function to deleted allocated mem. space of the linked list nodes
*/
template<class T>
Chain<T>::~Chain() { // Free all nodes in the chain
	ChainNode <T>* next;
	//for (; first; first = next) {
	//	next = first->link;
	//	delete first;
	//}

};

/*  Free the memory space allocated for linked list nodes
	See lecture notes linked list I page 51 for details
 */
template<class T>
void Chain<T>::free() {
	// ============================================== 
	//	DIY
	// ==============================================
	ChainNode <T>* tmp_next;
	for (; this->first; this->first = tmp_next) {
		tmp_next = (this->first)->link;
		delete first;
	}
	cout << "Free is finished!\n";
};
// ***************************************************************************
template<class T>
void Chain<T>::Create2(T x1, T x2)
{
	first = new ChainNode<T>(x1); // create & initialize first node
	// create & initialize 2nd node & place its address in first->link   
	last = first->link = new ChainNode<T>(x2);
};

/****************************************************************************
  create a node with data value and insert after the node pointed by x
***************************************************************************  */
template< class T>
void Chain<T>::Insert(ChainNode<T>* x, T value)
{
	ChainNode<T>* t = new ChainNode<T>(value); // create and initialize new node
	if (!first) // insert into empty Chain
	{
		first = t;
		exit(1); // exit Chain::Insert50
	}
	// insert after x
	t->link = x->link;
	x->link = t;
};
//************************************************************************************
// copy constructor
//***********************************************************************************
//template<class T>
//Chain<T>::Chain(const Chain<T> & list) {
//	first = last = current = 0;
//	cout << "now in the copy constructor linked list\n";
//	ChainNode * current = list.first;
//	while (current) {
//		this->InsertBack(current->data);
//		current = current->link;
//	}
//};

/*********************************************************************************
  delete the node x, in which the original list is y-->x-->
*/
template <class T>
void Chain<T>::Delete(ChainNode<T>* x, ChainNode<T>* y)
{
	if (x == first) first = first->link;
	else y->link = x->link;
	delete x;
};
//*********************************************************************************
template <class T>
void Chain<T>::InsertBack(const T& e)
{
	if (first) { // non null chain
		last->link = new ChainNode<T>(e);
		last = last->link;
	}
	else first = last = new ChainNode<T>(e);
};

/*******************************************************
 Insert one node into a list in an increasing order
********************************************************/
template <class T>
void Chain<T>::InsertInorder(const T& e)
{
	ChainNode<T>* Current, * last, * temp;
	bool Proceed;
	temp = new ChainNode<T>(e);

	if (first) {
		if (e.exp < first->data.exp) { temp->link = first; first = temp; Proceed = false; };
		last = first;
		Current = first->link;
		Proceed = true;
		while (Proceed && Current)
			if (e.exp > Current->data.exp) {
				last = Current;
				Current = Current->link;
			}
			else Proceed = false;
		last->link = temp;
		temp->link = Current;
		if (!Current)  last = temp;
	}
	else first = last = Current = temp;
};
//***************************************

/*******************************************************
 Insert one node into a list in an increasing order.
 When nodes are equal in value, add their coefficients into one
********************************************************/
template <class T>
void Chain<T>::InsertInorderB(const T& e)
{
	ChainNode<T>* Current, * last, * temp;
	bool Proceed;
	temp = new ChainNode<T>(e);

	if (first) {
		if (e.exp > first->data.exp) { temp->link = first; first = temp; Proceed = false; }
		else {
			last = first;
			Current = first->link;
			Proceed = true;
			while (Proceed && Current)
				if (e.exp <= Current->data.exp) {
					last = Current;
					Current = Current->link;
				}
				else Proceed = false;
			if (last->data.exp == e.exp) last->data.coef += e.coef;
			else {
				last->link = temp;
				temp->link = Current;
			}
			if (!Current)  last = temp;
		}
	}
	else first = last = Current = temp;
};
//**********************************************
template<class T>
void Chain<T>::PrintChain()
{
	current = first;
	cout << "t--> ";
	while (current != NULL) {
		cout << current->data << " --> ";
		current = current->link;
	}
	cout << "NULL" << endl;
};

//****************************************
//  Finished in 2020
//****************************************
template<class T>
ostream& operator<<(ostream& out, Chain<T>& Chain) {
	Chain.current = Chain.first;
	out << endl
		<< "print the linked Chain by operator overloading << ll\n" << endl << "ll.Chain-->";
	while (Chain.current != NULL)
	{
		out << Chain.current->data << "-->";
		Chain.current = Chain.current->link;
	}
	out << "NULL(end)";
	return out;
};
#endif