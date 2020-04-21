//Chase Brown	
//Program 4 (Graphs)

#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

const int MAXV = 'M' + 1;
const char START = 'A';
enum colors { black, gray, white };

struct qtype
{
	char v1, v2;
	int wt;
	qtype *link;
};

void init(int graph[][MAXV], int color[], qtype mst[])
{
	int i, j;
	for (i = 'A'; i < MAXV; i++)
		for (j = 'A'; j < MAXV; j++)
			graph[i][j] = 0;
	for (i = 'A'; i < MAXV; i++) color[i] = white;
	for (i = 'A'; i < MAXV; i++)
	{
		mst[i].v1 = 'z';
		mst[i].v2 = 'z';
		mst[i].wt = -1;
	}	
}

void read(int graph[][MAXV])
{
	ifstream inf("data.dat");
	char v1, v2;
	int wt;
	while (!inf.eof())
	{
		inf >> v1 >> v2 >> wt;
		graph[v1][v2] = wt;
		graph[v2][v1] = wt;
	}
}

void printgraph(int graph[][MAXV], ofstream &outf)
{
	int i, j;
	for (i = 'A'; i < MAXV; i++) outf << " | "  << char(i);
	outf << endl;
	for (i = 1; i < 56; i++) outf << "-";
	for (i = 'A'; i < MAXV; i++)
	{
		outf << endl << char(i) << "| ";
		for (j = 'A'; j < MAXV; j++)
			outf << graph[i][j] << " | ";
	}
}

void createq(qtype *&qhead, qtype *&qtail)
{
	qhead = new qtype;
	qtail = new qtype;
	qhead->v1 = 'z';
	qhead->v2 = 'z';
	qhead->wt = -1;
	qhead->link = qtail;
	qtail->v1 = 'z';
	qtail->v2 = 'z';
	qtail->wt = 999;
	qtail->link = NULL;
}

bool emptyq(qtype *qhead, qtype *qtail)
{
	return qhead->link == qtail;
}

void enq(qtype *qhead, qtype *qtail, char v1, char v2, int wt)
{
	qtype *nu, *prior, *c;
	nu = new qtype;
	nu->v1 = v1;
	nu->v2 = v2;
	nu->wt = wt;
	prior = qhead;
	c = qhead->link;
	while (prior != qtail && c->wt <= nu->wt)
	{
		prior = c;
		c = c->link;
	}
	prior->link = nu;
	nu->link = c;
}

qtype deq(qtype *qhead, qtype *qtail)
{
	qtype *c, temp;
	if (!emptyq(qhead, qtail))
	{
		c = qhead->link;
		temp.v1 = c->v1;
		temp.v2 = c->v2;
		temp.wt = c->wt;
		qhead->link = c->link;
		delete c;
	}
	return temp;
}
void primMST(qtype *qhead, qtype *qtail, int color[], int graph[][MAXV], ofstream &outf)
{
	int i, wt;
	char to, from;
	qtype startVertex, v;
	startVertex.v1 = START;
	startVertex.v2 = 'A';
	startVertex.wt = graph[START]['A'];
	// Not sure why it's keeping the A - A edge, this is supposed to find the first edge.
	for (i = 'A'; i < MAXV; i++) 
		if (graph[START][i] < startVertex.wt && startVertex.wt != 0)
		{
			startVertex.v2 = i;
			startVertex.wt = graph[START][i];
		}
	enq(qhead, qtail, startVertex.v1, startVertex.v2, startVertex.wt);
	color[START] = black;
	color[startVertex.v2] = gray;
	outf << endl << "Prim's MST" << endl;
	while (!emptyq(qhead, qtail))
	{
		v = deq(qhead, qtail);
		from = v.v2;
		to = v.v1;
		wt = v.wt;
		if (color[to] != black)
		{
			outf << from << " - " << to << " " << wt << endl;
			for (i = 'A'; i < MAXV; i++)
			{
				if (graph[to][i] > 0 && color[i] != black)
				{
					enq(qhead, qtail, i, to, graph[to][i]);
					color[i] = gray;
				}
				color[to] = black;
			}
		}
	}
}

int main()
{
	ofstream outf("output.ot");
	int graph[MAXV][MAXV];
	int color[MAXV];
	qtype *qhead, *qtail, mst[MAXV];
	
	init(graph, color, mst);
	read(graph);
	printgraph(graph, outf);
	
	createq(qhead, qtail);
	primMST(qhead, qtail, color, graph, outf);
	return 0;
}
