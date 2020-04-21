//Chase Brown
//Program 3 (HPFIFO)

#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;

struct qtype
{
	int priority;
	string jobname;
	qtype *link;
};

void createq(qtype *&qhead, qtype *&qtail)
{
	qhead = new qtype;
	qtail = new qtype;
	qhead->priority = -1;
	qhead->jobname = "*NoJob";
	qhead->link = qtail;
	qtail->priority = 999;
	qtail->jobname = "*NoJob";
	qtail->link = NULL;
}

bool emptyq(qtype *qhead, qtype *qtail)
{
	return qhead->link == qtail;
}

void enq(qtype *qhead, qtype *qtail, int priority, string job)
{
	qtype *nu, *prior, *c;
	nu = new qtype;
	nu->priority = priority;
	nu->jobname = job;
	prior = qhead;
	c = qhead->link;
	while (prior != qtail && c->priority <= nu->priority)
	{
		prior = c;
		c = c->link;
	}
	prior->link = nu;
	nu->link = c;
}

void deq(qtype *qhead, qtype *qtail, ofstream &outf)
{
	qtype *c, temp;
	if (!emptyq(qhead, qtail))
	{
		c = qhead->link;
		temp.jobname = c->jobname;
		temp.priority = c->priority;
		qhead->link = c->link;
		delete c;
	}
	outf << temp.priority << "  " << temp.jobname << endl;
}

void printq(qtype *qhead, qtype *qtail, ofstream &outf)
{
	qtype *c;
	if (!emptyq(qhead, qtail))
	{
		c = qhead->link;
		while (c != qtail)
		{
			outf << c->priority << "  " << c->jobname << endl;
			c = c->link;
		}
	}
	else outf << "Queue is empty" << endl;
}

int main()
{
	qtype *qhead, *qtail;
	ofstream outf("output.ot");
	createq(qhead, qtail);
	enq(qhead, qtail, 5, "Smith-123");
	enq(qhead, qtail, 5, "Harold-222");
	deq(qhead, qtail, outf);
	enq(qhead, qtail, 2, "Manzanares-111");
	enq(qhead, qtail, 1, "Payne-051");
	enq(qhead, qtail, 3, "Findley-303");
	deq(qhead, qtail, outf);
	enq(qhead, qtail, 5, "Smith-124");
	enq(qhead, qtail, 3, "Fox-858");
	while (!emptyq(qhead, qtail))
	{
		deq(qhead, qtail, outf);
	}
	return 0;
}