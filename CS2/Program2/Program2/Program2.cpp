//Chase Brown
//Program 2
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;
struct listtype
{
	string last;
	string first;
	int id;
	listtype *link;
};
void createlist(listtype *&head, listtype *&tail)
{
	head = new listtype;
	tail = new listtype;
	head->last = "zzzzz";
	tail->last = "zzzzz";
	head->first = "$$$$$";
	tail->first = "$$$$$";
	head->id = -1;
	tail->id = 9999;
	head->link = tail;
	tail->link = NULL;
}
void insertlist(listtype *head, listtype *tail, 
	string last, string first, int id)
{
	listtype *before, *after, *nu;
	nu = new listtype;
	nu->last = last;
	nu->first = first;
	nu->id = id;
	before = head;
	after = head->link;
	while (after != tail && nu->last > after->last)
	{
		before = after;
		after = after->link;
	}
	before->link = nu;
	nu->link = after;
}
void read(listtype *head, listtype *tail)
{
	ifstream inf("Program2.dat");
	string last, first;
	int id;
	while (!inf.eof())
	{
		inf >> last >> first >> id;
		last.erase(last.find(","));
		insertlist(head, tail, last, first, id);
	}
}
bool emptylist(listtype *head, listtype *tail)
{
	return head->link == tail;
}
void traverse(listtype *head, listtype *tail, ofstream &outf)
{
	listtype *current;
	int i;
	if (!emptylist(head, tail))
	{
		current = head->link;
		outf << "ID #     Name" << endl;
		for (i = 0; i <= 35; i++) outf << "=";
		outf << endl;
		while (current != tail)
		{
			outf << current->id << "      " << current->first 
				<< " " << current->last << endl;
			current = current->link;
		}
	}
	else
		outf << "List is Empty" << endl;
	outf << endl;
}
void deletelist(listtype *head, listtype *tail, string last, ofstream &outf)
{
	listtype *before, *current, *after;
	before = head;
	current = head->link;
	after = current->link;
	while (current != tail && current->last < last)
	{
		before = current;
		current = after;
		after = after->link;
	}
	if (current != tail && current->last == last)
	{
		before->link = after;
		delete current;
		outf << "*" << last << " deleted." << endl;
	}
	else outf << "Person not in list" << endl;
}
void main()
{
	listtype *head, *tail;
	ofstream outf("Program2.ot");

	createlist(head, tail);
	read(head, tail);
	traverse(head, tail, outf);
	insertlist(head, tail, "Skywalker", "Luke", 444);
	traverse(head, tail, outf);
	deletelist(head, tail, "Organa", outf);
	traverse(head, tail, outf);
}