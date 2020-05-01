// Chase Brown
// Recursive Descent Parser

#include <fstream>
#include <iostream>
#include<string>
using namespace std;

bool error = false;
ifstream inf("data.txt");
ofstream outf("output.txt");
string line;
char token;
int i = 0;

void parse();
void digit();
void number();
void factor();
void term();
void exp();

void getToken()
{
	if (i <= line.length())
	{
		token = line[i++];
		if (token == '\0')
			return;
		else
		{
			outf << "\n<getToken> ";
			outf << token << " ";

		}
	}
}

void exp()
{
	outf << "<exp> ";
	term();
	while (token == '+')
	{
		getToken();
		term();
	}
}

void term()
{
	outf << "<term> ";
	factor();
	while (token == '*')
	{
		getToken();
		factor();
	}
}

void factor()
{
	outf << "<factor> ";
	if (token == '(')
	{
		getToken();
		exp();
		if (token == ')')
			getToken();
		else
			error = true;

	}
	else
		number();
}

void number()
{
	outf << "<number> ";
	digit();
	while (token >= '0' && token <= '9')
		digit();
}

void digit()
{
	outf << "<digit> ";
	if (token >= '0' && token <= '9')
		getToken();
	else
		error = true;
}

void parse()
{
	outf << "<parse>";
	getToken();
	exp();
}

int main()
{
	while (!inf.eof())
	{
		getline(inf, line);
		parse();
		if (error == true)
			outf << "\nError in parsing . . . \n\n";
		else
			outf << "\nParse completed with no errors . . . \n\n";
		error = false;
		i = 0;
	}
	return 0;
}