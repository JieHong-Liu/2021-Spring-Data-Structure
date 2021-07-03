#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "student.h"
using namespace std;

void file_process()
{
	int n; /* i is for index and n is the number of record to be read */
	string tt;
	ifstream fin("list1.txt"); 
	if (!fin) 
	{
		exit(1); // exit if file open error
	}
	else
	{
		student* s= NULL;
		fin >> n;
		getline(fin, tt);
		if (n > 0)
		{
			s = new student[n];  /* dynamic memory allocation */
			cout << "now reading the record from the input file....." << endl;
			for (int i = 0; i < n; i++)
			{
				fin >> s[i].p.name >> s[i].p.pID >> s[i].p.age >> s[i].sID >> s[i].dept;
				int sum = 0;
				for (int j = 0; j < 3; j++)
				{
					fin >> s[i].score[j];
					sum += s[i].score[j];
				}
				s[i].total_score = sum;
				double average = sum / 3.0;
				s[i].avg = average;
			}
			int* index_list = new int[n];	  // index list
			for (int i = 0; i < n; i++)
			{
				index_list[i] = i;
			}
			string type = "normal";
			print_data(n, s, index_list, type);
			type = "sort";
			sort_score(n, s, index_list);
			print_data(n, s, index_list,type);
		}
		else
		{
			cerr << "There is no student in the class. " << endl;
		}
	}
}

void print_data(int n,student s[], int index_list[], string type)
{
	if (type == "normal")
	{
		cout << "out put the recorded data " << endl;
		cout << setw(2) << "index"
			<< setw(12) << "NAME" << setw(16) << "P_ID" << setw(6) << "AGE"
			<< setw(14) << "S_ID" << setw(6) << "DEPT" << setw(4) << "S1" << setw(4) << "S2" << setw(4) << "S3" << setw(12) << "Ave" << endl;
		for (int i = 0; i < n; i++)
		{
			cout << setw(2) << i
				<< setw(15) << s[index_list[i]].p.name << setw(16) << s[index_list[i]].p.pID << setw(6) << s[index_list[i]].p.age
				<< setw(14) << s[index_list[i]].sID << setw(6) << s[index_list[i]].dept;
			for (int j = 0; j < 3; j++)
			{
				cout << setw(4) << s[index_list[i]].score[j];
			}
			cout << setw(12) << (int)s[index_list[i]].avg << endl;
		}
	}
	else
	{
		cout << "After sorting :" << endl;
		cout << setw(2) << "index" << setw(12) << "NAME" << setw(12) << "Score" << endl;
		for (int i = 0; i < n; i++)
		{
			cout << setw(2) << i+1 << setw(15) << s[index_list[i]].p.name << setw(12) << (int)s[index_list[i]].total_score << endl;
		}
	}
	cout << endl;
}

void sort_score(int n, student s[], int index_list[])
{
	//bubble sort
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (s[index_list[j]].total_score < s[index_list[j + 1]].total_score)
			{
				int tmp_index = index_list[j];
				index_list[j] = index_list[j + 1];
				index_list[j + 1] = tmp_index;
			}
		}
	}
}

// provide a function to find the highest student and lowest student

void find()
{
	// read the file again , since it may not excute file_process
	ifstream fin("list1.txt");
	if (!fin)
	{
		exit(1); // exit if file open error
	}
	else
	{
		string tt;
		student* s = NULL;
		int n; /* i is for index and n is the number of record to be read */
		fin >> n;
		getline(fin, tt);
		if (n > 0)
		{
			s = new student[n];  /* dynamic memory allocation */
			for (int i = 0; i < n; i++)
			{
				int sum = 0;
				fin >> s[i].p.name >> s[i].p.pID >> s[i].p.age >> s[i].sID >> s[i].dept;
				for (int j = 0; j < 3; j++)
				{
					fin >> s[i].score[j];
					sum += s[i].score[j];
				}
				s[i].total_score = sum;
				double average = sum / 3.0;
				s[i].avg = average;
			}
			int* index_list = new int[n];	  // index list
			for (int i = 0; i < n; i++)
			{
				index_list[i] = i;
			}
			sort_score(n, s, index_list);
			if (n - 1 == 0)
			{
				cout << "There is only one student " << s[index_list[0]].p.name << " in class, and the avg is " << s[index_list[0]].avg << endl;
			}
			else
			{
				cout << "The highest student is " << s[index_list[0]].p.name << " and the avg is " << (int)s[index_list[0]].avg << endl;
				cout << "The lowest student is " << s[index_list[n - 1]].p.name << " and the avg is " << (int)s[index_list[n - 1]].avg << endl;
			}
		}
	}
}