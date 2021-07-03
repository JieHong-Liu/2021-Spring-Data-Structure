#pragma once
#include<iostream>
using namespace std;
class Token
{
public:
	float f;
	char c;
	bool is_number;
	Token() : is_number(false), c(0),f(0) {};
};

class Tree;
class TreeNode {
	friend class Tree;
public:
	TreeNode()
	{
		LeftChild = NULL;
		RightChild = NULL;
	}
private:
	TreeNode* LeftChild;
	Token data;
	TreeNode* RightChild;
};

class Tree{
public:
	Tree() 
	{
		root = NULL;
	}
	~Tree() {};
	bool isempty()
	{
		return (root == NULL);
	}
	void Insert(char);
	void Inorder(TreeNode*); // Workhorse
	void Preorder(TreeNode*);
	void Postorder(TreeNode*);
	float evaluate(TreeNode*);
	void Inorder(); //Driver
	void Preorder();
	void Postorder();
	void Levelorder();
	void InsertInInfixOrder(std::string);
	float evaluate();
	void printTree()
	{
		cout << root->data.c << endl;
		cout << root->RightChild->data.c << endl;
	}
private:
	TreeNode* root;
};

