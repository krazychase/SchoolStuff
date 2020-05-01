//Chase Brown
//Final Program
#include<fstream>
#include<iostream>
#include<iomanip>
#include<string>
using namespace std;
const int maxres = 20, maxsource = 20, maxexplain = 20;
enum statetype {
	newtoken, resword, variable, integer, real, delim, laststate
};
enum chartype {
	letter, digit, period, delimiter, blank, pod, eoln, illegal, lastchar
};
statetype strtostate(string s)
{
	statetype ans;
	if (s == "newtoken") ans = newtoken;
	else if (s == "reserveword") ans = resword;
	else if (s == "variable") ans = variable;
	else if (s == "integer") ans = integer;
	else if (s == "real") ans = real;
	else if (s == "delimiter") ans = delim;
	else ans = laststate;
	return ans;
}
string statetostr(statetype s)
{
	string ans;
	if (s == newtoken) ans = "new token";
	else if (s == resword) ans = "reserve word";
	else if (s == variable) ans = "variable";
	else if (s == integer) ans = "integer";
	else if (s == real) ans = "real";
	else if (s == delim) ans = "delimiter";
	else ans = "*No State";
	return ans;
}
chartype strtochartype(string s)
{
	chartype ans;
	if (s == "letter") ans = letter;
	else if (s == "digit") ans = digit;
	else if (s == "period") ans = period;
	else if (s == "delimeter") ans = delimiter;
	else if (s == "blank") ans = blank;
	else if (s == "pod") ans = pod;
	else if (s == "eoln") ans = eoln;
	else if (s == "illegal") ans = illegal;
	else ans = lastchar;
	return ans;
}
string chartypetostr(chartype c)
{
	string ans;
	if (c == letter) ans = "letter";
	else if (c == digit) ans = "digit";
	else if (c == period) ans = "period";
	else if (c == delimiter) ans = "delimiter";
	else if (c == blank) ans = "blank";
	else if (c == pod) ans = "pod";
	else if (c == eoln) ans = "eoln";
	else if (c == illegal) ans = "illegal";
	else ans = "*No Char";
	return ans;
}
void swap(string &x, string &y)
{
	string temp;
	temp = x;
	x = y;
	y = temp;
}
void readreserve(string reserve[], int &reservenum)
{
	int i = 0;
	ifstream inf("reserve.dat");
	while (!inf.eof())
	{
		inf >> reserve[i];
		i++;
	}
	reservenum = i;
}
void readsource(string source[], int &sourcenum)
{
	int i = 0;
	ifstream inf("prog1.bas");
	while (!inf.eof())
	{
		getline(inf, source[i]);
		i++;
	}
	sourcenum = i;
}
void readexplain(string explain[], int &explainnum)
{
	int i = 0;
	ifstream inf("explain.dat");
	while (!inf.eof())
	{
		getline(inf, explain[i]);
		i++;
	}
	explainnum = i;
}
void readaction(int action[][lastchar])
{
	int i,j;
	ifstream inf("action.dat");
	for (i = newtoken; i < laststate; i++)
		for (j = letter; j < lastchar; j++)
			inf >> action[i][j];
}
void readstate(statetype fsm[][lastchar])
{
	int i, j;
	string state;
	ifstream inf("state.dat");
	for (i = newtoken; i < laststate; i++)
		for (j = letter; j < lastchar; j++)
		{
			inf >> state;
			fsm[i][j] = strtostate(state);
		}
}
void printreserve(string reserve[], int reservenum, ofstream &outf)
{
	int i, j;
	for (i = 0; i < reservenum-1; i++)
		for (j = 0; j < reservenum-1; j++)
			if (reserve[j] > reserve[j + 1]) swap(reserve[j], reserve[j + 1]);
	outf << "***Reserve Words***" << endl;
	for (i = 0; i < reservenum; i++) outf << reserve[i] << endl;
}
void printsource(string source[], int sourcenum, ofstream &outf)
{
	int i;
	outf << endl << "***BASIC code***" << endl;
	for (i = 0; i < sourcenum; i++) outf << source[i] << endl;
}
void printexplain(string explain[], int &explainnum, ofstream &outf)
{
	int i;
	outf << endl << "***Explainations***" << endl;
	for (i = 0; i < explainnum; i++) outf << explain[i] << endl;

}
void printaction(int action[][lastchar], ofstream &outf)
{
	int i, j;
	chartype ch;
	statetype st;
	outf << endl << setw(56) << "***Action Table***" << endl << "             ";
	for (j = letter; j < lastchar; j++)
	{
		ch = chartype(j);
		outf << setw(10) << chartypetostr(ch);
	}
	for (i = newtoken; i < laststate; i++)
	{
		st = statetype(i);
		outf << endl << setw(13) << statetostr(st);
		for (j = letter; j < lastchar; j++)
			outf << setw(10) << action[i][j];
	}
	outf << endl;
}
void printstate(statetype fsm[][lastchar], ofstream &outf)
{
	int i, j;
	chartype ch;
	statetype st;
	outf << endl << setw(64) << "***State Table***" << endl << "            | ";
	for (j = letter; j < lastchar; j++)
	{
		ch = chartype(j);
		outf << setw(12) << chartypetostr(ch);
	}
	outf << endl;
	for (i = 0; i < 110; i++)outf << "-";
	for (i = newtoken; i < laststate; i++)
	{
		st = statetype(i);
		outf << endl << setw(12) << statetostr(st) << "| ";
		for (j = letter; j < lastchar; j++)
			outf << setw(12) << statetostr(fsm[i][j]);
	}
	outf << endl;
}
chartype setchartype(char ch)
{
	chartype cct;
	if (ch >= 'a' && ch <= 'z') cct = letter;
	else if (ch >= '0' && ch <= '9') cct = digit;
	else if (ch == '.') cct = period;
	else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '('
		|| ch == ')' || ch == '=' || ch == '<' || ch == '>' || ch == ','
		|| ch == '^' || ch == '"' || ch == '&') cct = delimiter;
	else if (ch == ' ') cct = blank;
	else if (ch == '%' || ch == '&') cct = pod;
	else if (ch == '`') cct = eoln;
	else cct = illegal;
	return cct;
}
statetype compare(string reserve[], string token, int reservenum)
{
	statetype cct = variable;
	int i;
	for (i = 0; i < reservenum; i++)
		if (token == reserve[i]) cct = resword;
	return cct;
}
void doaction(int action[][lastchar], string reserve[], char ch, int todo,
	int reservenum, string &token, statetype &st, ofstream &outf)
{
	switch (todo)
	{
	case 1: token += ch;
		break;
	case 2: st = compare(reserve, token, reservenum);
		outf << left << setw(10) << token << setw(15) << statetostr(st) << endl;
		token = "";
		break;
	case 3: outf << left << setw(10) << token << setw(15) << statetostr(st) << endl;
		token = "";
		break;
	case 4: outf << left << setw(10) << token << setw(15) << statetostr(st) << endl
		<< "Improper Usage: " << ch << endl;
		token = "";
		break;
	case 5: outf << "Improper Usage: " << ch << endl;
		break;
	case 6:
		break;
	case 7: outf << "Illegal Character: " << ch << endl;
		break;
	case 8: st = compare(reserve, token, reservenum);
		outf << left << setw(10) << token << setw(15) << statetostr(st) << endl;
		token = "";
		token += ch;
		break;
	case 9: outf << left << setw(10) << token << setw(15) << statetostr(st) << endl;
		token = "";
		token += ch;
		break;
	case 10: token += ch;
		st = variable;
		outf << left << setw(10) << token << setw(15) << statetostr(st) << endl;
		token = "";
		break;
	case 11: st = compare(reserve, token, reservenum);
		outf << left << setw(10) << token << setw(15) << statetostr(st) << endl
			<< "Illegal Character: " << ch << endl;
		break;
	case 12: token += ch;
		outf << left << setw(10) << token << setw(15) << statetostr(st) << endl;
		token = "";
		break;
	default: outf << left << setw(10) << token << setw(15) << statetostr(st) << endl
		<< "Illegal Character: " << ch << endl;
		token = "";
		break;
	}
}
void scan(string source[], string reserve[], int action[][lastchar], 
	statetype fsm[][lastchar], int sourcenum, int reservenum, ofstream &outf)
{
	string token = "", line;
	char ch;
	int i, j, todo;
	statetype st = newtoken;
	chartype cct;
	outf << endl << "Token" << setw(15) << "Token Type" << endl;
	for (i = 0; i < 21; i++) outf << "-";
	outf << endl;
	for (i = 0; i < sourcenum; i++)
	{
		line = source[i];
		line += "`";
		for (j = 0; j < line.length(); j++)
		{
			ch = line[j];
			cct = setchartype(ch);
			todo = action[st][cct];
			doaction(action, reserve, ch, todo, reservenum, token, st, outf);
			st = fsm[st][cct];
		}
	}
}
int main()
{
	ofstream outf("program7.ot");
	string reserve[maxres], source[maxsource], explain[maxexplain];
	int reservenum = 0, sourcenum = 0, explainnum = 0, action[laststate][lastchar];
	statetype fsm[laststate][lastchar];
	readreserve(reserve, reservenum);
	printreserve(reserve, reservenum, outf);
	readsource(source, sourcenum);
	readexplain(explain, explainnum);
	printexplain(explain, explainnum, outf);
	readaction(action);
	printaction(action, outf);
	readstate(fsm);
	printstate(fsm, outf);
	scan(source, reserve, action, fsm, sourcenum, reservenum, outf);
	system("pause");
	return 0;
}