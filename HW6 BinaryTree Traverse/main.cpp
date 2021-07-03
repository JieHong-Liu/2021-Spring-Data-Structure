/* Binary Tree Traversal - Preorder, Inorder, Postorder */
#include<iostream>
#include<iomanip>
#include "tree.h"
using namespace std;
int main() {
	/* construct a binary search tree
	   according to the input chars 

	             M
			   /   \
			  B     Q
			 / \     \
			A   C     Z
                     /
					X
				   /
				  W	  
	*/
	Tree bt,infixTree;
	string infix = "(11-7)^2+(3-81)/(12+4)*(7-15)";
	char input[30] = "MBQZACXW";
	infixTree.InsertInInfixOrder(infix);
	for (int i = 0; i < 8; i++)
	{
		bt.Insert(input[i]);
	}
	/**
		bt.Insert('M'); bt.Insert('B');
		bt.Insert('Q'); bt.Insert('Z'); 
		bt.Insert('A'); bt.Insert('C');
		bt.Insert('X'); bt.Insert('W');
	*/
	cout <<std::left << setw(15) <<"original input chars:" << input << endl;
	cout<<std::left<<setw(15)<<"Preorder: ";   bt.Preorder();
	cout<<std::left<<setw(15)<<"Inorder: ";	   bt.Inorder();
	cout<<std::left<<setw(15)<<"Postorder:";   bt.Postorder();
	cout<<std::left<<setw(15)<<"Levelorder:";  bt.Levelorder();


	cout << std::left << setw(15) << "\noriginal input chars:" << infix << endl;
	cout << std::left << setw(15) << "Preorder: ";   infixTree.Preorder();
	cout << std::left << setw(15) << "Inorder: ";	   infixTree.Inorder();
	cout << std::left << setw(15) << "Postorder:";   infixTree.Postorder();
	cout << std::left << setw(15) << "Levelorder:";  infixTree.Levelorder();
	cout << "\nEvaluate: " << infixTree.evaluate() << endl;
	cout << "\nPress any key to exit\n";
	getchar();
	return 0;
}