#include <iostream>
#include <queue>
#include <stack>
#include <sstream>
#include "tree.h"
#include <cmath>
using namespace std;
void Tree::Preorder()
{
	Preorder(root);
	cout << endl;
}
void Tree::Postorder()
{
	Postorder(root);
	cout << endl;
}
//Function to visit nodes in Preorder
void Tree::Preorder(TreeNode *CurrentNode)
{
	// base condition for recursion
	// if tree/sub-tree is empty, return and exit
	if (CurrentNode)
	{
		if (CurrentNode->data.is_number == true)
		{
			cout << CurrentNode->data.f << " ";
		}
		else
		{
			if (CurrentNode->data.c == 'u')
			{
				cout << "-"
					 << " ";
			}
			else
			{
				cout << CurrentNode->data.c << " ";
			}
		}
		Preorder(CurrentNode->LeftChild);  // Visit LeftChild subtree
		Preorder(CurrentNode->RightChild); // Visit RightChild subtree
	}
}
void Tree::Inorder()
{
	Inorder(root);
	cout << endl;
}
//Function to visit nodes in Inorder
void Tree::Inorder(TreeNode *CurrentNode)
{
	if (CurrentNode)
	{
		Inorder(CurrentNode->LeftChild); // Visit LeftChild subtree
		if (CurrentNode->data.is_number == true)
		{
			cout << CurrentNode->data.f << " ";
		}
		else
		{
			if (CurrentNode->data.c == 'u')
			{
				cout << "-"
					 << " ";
			}
			else
			{
				cout << CurrentNode->data.c << " ";
			}
		}
		Inorder(CurrentNode->RightChild); // Visit RightChild subtree
	}
}

//Function to visit nodes in Postorder
void Tree::Postorder(TreeNode *CurrentNode)
{
	if (CurrentNode)
	{
		Postorder(CurrentNode->LeftChild);	// Visit LeftChild subtree
		Postorder(CurrentNode->RightChild); // Visit RightChild subtree
		if (CurrentNode->data.is_number == true)
		{
			cout << CurrentNode->data.f << " ";
		}
		else
		{
			if (CurrentNode->data.c == 'u')
			{
				cout << "-"
					 << " ";
			}
			else
			{
				cout << CurrentNode->data.c << " ";
			}
		}
	}
}
// Insert the item into the tree according to its priority, i.e., A<C<E etc.
void Tree::Insert(char item)
{
	TreeNode *p = new TreeNode;
	TreeNode *parent;
	Token item2;
	item2.c = item;
	item2.is_number = false;

	p->data = item2;
	p->LeftChild = p->RightChild = NULL;
	parent = NULL;
	if (isempty())
	{
		root = p;
		int i = -1;
	}
	else
	{
		TreeNode *ptr;
		ptr = root;
		while (ptr != NULL)
		{
			parent = ptr;
			if (item2.c > ptr->data.c)
				ptr = ptr->RightChild;
			else
				ptr = ptr->LeftChild;
		}
		if (item2.c < parent->data.c)
			parent->LeftChild = p;
		else
			parent->RightChild = p;
	}
}

void Tree::Levelorder()
{
	queue<TreeNode *> q;
	TreeNode *CurrentNode = root;
	while (CurrentNode)
	{
		if (CurrentNode->data.is_number == true)
		{
			cout << CurrentNode->data.f << " ";
		}
		else
		{
			if (CurrentNode->data.c == 'u')
			{
				cout << "-"
					 << " ";
			}
			else
			{
				cout << CurrentNode->data.c << " ";
			}
		}
		if (CurrentNode->LeftChild)
			q.push(CurrentNode->LeftChild);
		if (CurrentNode->RightChild)
			q.push(CurrentNode->RightChild);
		if (!q.empty())
		{
			CurrentNode = q.front();
			q.pop();
		}
		else
			CurrentNode = NULL;
	}
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

void Tree::InsertInInfixOrder(string infix_str)
{
	stack<char> operator_stack;	  // the stack for store the operators.
	stack<TreeNode *> Node_stack; // the stack for store the node.
	stringstream ss(infix_str);
	bool unary = true;
	while (ss.peek() != -1)
	{
		Token t;
		float x;
		char op;
		if (ss.peek() >= '0' && ss.peek() <= '9') // a number.
		{
			unary = false;
			ss >> t.f;
			t.is_number = true;
			TreeNode *newNode = new TreeNode;
			newNode->data = t;
			Node_stack.push(newNode);
		}
		else
		{
			if (ss.peek() == ' ') // delete space.
			{
				ss.get();
			}
			else if (ss.peek() == '(')
			{
				ss >> op;
				operator_stack.push(op);
				unary = true;
			}
			else if (ss.peek() == ')')
			{
				unary = false;
				ss >> op;
				while (!operator_stack.empty() && operator_stack.top() != '(')
				{
					t.is_number = false;
					t.c = operator_stack.top();
					operator_stack.pop();
					TreeNode *newNode = new TreeNode;
					newNode->data = t;
					newNode->RightChild = Node_stack.top();
					Node_stack.pop();
					if (!Node_stack.empty())
					{
						newNode->LeftChild = Node_stack.top();
						Node_stack.pop();
					}
					Node_stack.push(newNode);
				}
				operator_stack.pop(); // remove the '('.
			}
			else if (ss.peek() == '-' && unary == true)
			{
				ss >> op;
				op = 'u';
				operator_stack.push(op);
				unary = false;
			}
			else if (operator_stack.empty() || weight_calculator(ss.peek()) > weight_calculator(operator_stack.top()))
			// new operator priority is bigger than the top stack operator.
			{
				unary = false;
				ss >> op;
				operator_stack.push(op);
			}
			else if (weight_calculator(ss.peek()) <= weight_calculator(operator_stack.top()))
			{
				unary = false;
				// now the op_stack operator is bigger than the new operator.
				while (!operator_stack.empty() && (weight_calculator(operator_stack.top()) >= weight_calculator(ss.peek())))
				{
					t.is_number = false;
					t.c = operator_stack.top();
					operator_stack.pop();
					TreeNode *newNode = new TreeNode;
					newNode->data = t;
					newNode->RightChild = Node_stack.top();
					Node_stack.pop();
					if (!Node_stack.empty())
					{
						newNode->LeftChild = Node_stack.top();
						Node_stack.pop();
					}
					Node_stack.push(newNode);
				}
				ss >> op;
				operator_stack.push(op);
			}
		}
	}
	while (!operator_stack.empty())
	{
		Token t;
		t.is_number = false;
		t.c = operator_stack.top();
		operator_stack.pop();
		TreeNode *newNode = new TreeNode;
		newNode->data = t;
		newNode->RightChild = Node_stack.top();
		Node_stack.pop();
		if (!Node_stack.empty())
		{
			newNode->LeftChild = Node_stack.top();
			Node_stack.pop();
		}
		Node_stack.push(newNode);
	}
	this->root = Node_stack.top();
}

float Tree::evaluate(TreeNode *CurrentNode)
{
	if (CurrentNode)
	{
		float L_value = evaluate(CurrentNode->LeftChild);
		float R_value = evaluate(CurrentNode->RightChild);
		switch (CurrentNode->data.c)
		{
		case '+':
		case '-':
		}
	}
}

float Tree::evaluate(TreeNode *CurrentNode)
{
	static stack<float> ans_stack;
	if (CurrentNode)
	{
		float left = evaluate(CurrentNode->LeftChild);	 // Visit LeftChild subtree
		float right = evaluate(CurrentNode->RightChild); // Visit RightChild subtree
		if (CurrentNode->data.is_number == true)
		{
			ans_stack.push(CurrentNode->data.f);
		}
		else
		{
			if (CurrentNode->data.c == 'u')
			{
				float v = ans_stack.top();
				v = -v;
				ans_stack.pop();
				ans_stack.push(v);
			}
			else
			{
				float left_term, right_term;
				right_term = ans_stack.top();
				ans_stack.pop();
				left_term = ans_stack.top();
				ans_stack.pop();
				switch (CurrentNode->data.c)
				{
				case '+':
				{
					float ans = left_term + right_term;
					ans_stack.push(ans);
					break;
				}
				case '-':
				{
					float ans = left_term - right_term;
					ans_stack.push(ans);
					break;
				}
				case '*':
				{
					float ans = left_term * right_term;
					ans_stack.push(ans);
					break;
				}
				case '/':
				{
					float ans = left_term / right_term;
					ans_stack.push(ans);
					break;
				}
				case '^':
				{
					float ans = pow(left_term, right_term);
					ans_stack.push(ans);
					break;
				}
				}
			}
		}
		return ans_stack.top();
	}
}

float Tree::evaluate()
{
	return evaluate(this->root);
}
