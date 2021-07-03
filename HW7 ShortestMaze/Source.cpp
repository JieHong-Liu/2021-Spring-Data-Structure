#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include "Point.h"
using namespace std;

void BFS(int **, Point start_point, Point end_point);
bool isValid(int **, Point p);
void print_map(int **, int n, int m);

class TreeNode {
public:
	TreeNode() {
		p.set_x(0);
		p.set_y(0);
		parent = NULL;
	}
	Point p;
	TreeNode* parent;
};

int main()
{
	// read map.
	ifstream f;
	f.open("maze.txt");
	if (!f)
	{
		cerr << "Error: file could not be opened" << endl;
	}
	else
	{
		int n, m;
		f >> n >> m;
		int **map = new int *[n];
		for (int i = 0; i < n; i++)
		{
			map[i] = new int[m];
		}
		cout << "The map is " << n << "*" << m << endl
			 << endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				f >> map[i][j];
				cout << map[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
		// start programming.
		Point end_point(n - 1, m - 1);
		Point start_point(0, 0);
		if (map[start_point.get_x()][start_point.get_y()] == 1)
		{
			cout << "There is no start point in the map." << endl;
		}
		else
		{
			BFS(map, start_point, end_point);
		}
		//delete map.
		for (int i = 0; i < n; i++)
		{
			delete[] map[i];
		}
		delete[] map;
	}
	return 0;
}

void BFS(int **map, Point start_point, Point end_point)
{
	queue<TreeNode*> q;
	TreeNode *root = new TreeNode;
	root->p = start_point;
	root->parent = NULL;
	q.push(root);
	while (!q.empty())
	{
		TreeNode* tmp_node = new TreeNode;
		tmp_node = q.front();
		//Point tmp = q.front();
		q.pop();
		map[tmp_node->p.get_x()][tmp_node->p.get_y()] = 2; // mark it as walked.
		if (tmp_node->p == end_point)
		{
			cout << "find the end point !" << endl;
			stack<TreeNode*> ans;
			while (tmp_node)
			{
				ans.push(tmp_node);
				tmp_node = tmp_node->parent;
			}
			while (!ans.empty())
			{
				cout << "( " << (ans.top()->p).get_x() << " , " << (ans.top()->p).get_y() << " ) " << endl;
				ans.pop();
			}
			break;
		}
		if (tmp_node->p.get_x() < end_point.get_x() && isValid(map, tmp_node->p.Point_down())) // The direction in order is down, right,top,left.
		{
			TreeNode* new_node = new TreeNode;
			new_node->p = tmp_node->p.Point_down();
			new_node->parent = tmp_node;
			q.push(new_node);
		}
		if (tmp_node->p.get_y() < end_point.get_y() && isValid(map, tmp_node->p.Point_right()))
		{
			TreeNode* new_node = new TreeNode;
			new_node->p = tmp_node->p.Point_right();
			new_node->parent = tmp_node;
			q.push(new_node);
		}
		if (tmp_node->p.get_x() > 0 && isValid(map, tmp_node->p.Point_up()))
		{
			TreeNode* new_node = new TreeNode;
			new_node->p = tmp_node->p.Point_up();
			new_node->parent = tmp_node;
			q.push(new_node);
		}
		if (tmp_node->p.get_y() > 0 && isValid(map, tmp_node->p.Point_left()))
		{
			TreeNode* new_node = new TreeNode;
			new_node->p = tmp_node->p.Point_left();
			new_node->parent = tmp_node;
			q.push(new_node);
		}
	}
	if (q.empty())
	{
		cout << "There is no exit in the maze." << endl;
	}
}

bool isValid(int **map, Point p)
{
	if (map[p.get_x()][p.get_y()] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void print_map(int **map, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
