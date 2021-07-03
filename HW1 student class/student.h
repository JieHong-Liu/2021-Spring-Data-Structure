#pragma once
#include <string>
typedef struct {  // This is a data structure for a person
	char name[40], pID[10];
	int age;
} person;

typedef struct {   // a data structure for a student
	person p;
	char sID[10], dept[4];  // student id and departure 
	int score[3];
	int total_score;
	double avg;
} student;
//void process1();
void file_process();
void sort_score(int n, student s[], int index_list[]);
void print_data(int n, student s[], int index_list[], std::string type);
void find();
