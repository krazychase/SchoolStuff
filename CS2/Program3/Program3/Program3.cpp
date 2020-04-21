//Chase Brown
//Program 3
#include<fstream>
#include<iostream>
#include<iomanip>
#include<string>
using namespace std;
const char initstack = '$';
const int maxstack = 20;
void createstack(char stack[], int &top)
{
	int i;
	for (i = 0; i < maxstack; i++)
		stack[i] = initstack;
	top = -1;
}
bool emptystack(int top)
{
	return top < 0;
}
bool fullstack(int top)
{
	return top >= maxstack - 1;
}
void push(char stack[], int &top, char value, ofstream &outf)
{
	if (!fullstack(top))
	{
		top++;
		stack[top] = value;
	}
	else outf << "Stack is full, " << value << " not pushed" << endl;
}
char pop(char stack[], int &top, char value, ofstream &outf)
{
	char temp = initstack;
	if (!emptystack(top))
	{
		temp = stack[top];
		stack[top] = initstack;
		top--;
		return temp;
	}
	else outf << "Stack is empty!" << endl;
}
int priority(char ch)
{
	if (ch == '+' || ch == '-') return -1;
	else return 1;
}
void read(char stack[], int &top, ofstream &outf)
{
	ifstream inf("Program3.dat");
	while (!inf.eof())
	{
		string instring, outstring = "";
		char ch;
		inf >> instring;
		int len = instring.length(), i;
		for (i = 0; i < len; i++)
		{
			ch = instring[i];
			if (ch >= 'a' && ch <= 'z')
				outstring += ch;
			else
			{
				if (emptystack(top)) 
					push(stack, top, ch, outf);
				else if (priority(ch) > priority(stack[top])) 
					push(stack, top, ch, outf);
				else
				{
					while (!emptystack(top) && priority(ch) <= priority(stack[top]))
						outstring += pop(stack, top, ch, outf);
					push(stack, top, ch, outf);
				}
			}
		}
		while (!emptystack(top))
			outstring += pop(stack, top, ch, outf);
		outf << instring << " = " << outstring << endl;
	}
}
void main()
{
	char stack[maxstack];
	int top;
	ofstream outf("Program3.ot");
	createstack(stack, top);
	read(stack, top, outf);
}