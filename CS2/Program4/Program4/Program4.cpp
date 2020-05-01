//Chase Brown
//Program 4
#include<fstream>
#include<iostream>
#include<iomanip>
using namespace std;
struct treetype
{
	int key;
	treetype *left, *right;
};
const int maxstack = 20;
void createtree(treetype *&root)
{
	root = new treetype;
	root->key = -1;
	root->left = NULL;
	root->right = NULL;
}
void createstack(treetype *stack[], int &top)
{
	int i;
	top = -1;
	for (i = 0; i < maxstack; i++)
		stack[i] = NULL;
}
bool emptytree(treetype *root)
{
	return root->key == -1;
}
void insert(treetype *root, int key)
{
	treetype *c, *parent, *nu;
	if (!emptytree(root))
	{
		nu = new treetype;
		nu->key = key;
		nu->left = NULL;
		nu->right = NULL;
		parent = NULL;
		c = root;
		while (c != NULL)
		{
			parent = c;
			if (nu->key < c->key)
				c = c->left;
			else
				c = c->right;
		}
		if (nu->key < parent->key)
			parent->left = nu;
		else
			parent->right = nu;
	}
	else
		root->key = key;
}
void read(treetype *root)
{
	ifstream inf("Program4.dat");
	int key;
	while (!inf.eof())
	{
		inf >> key;
		insert(root, key);
	}
}
void deleteleaf(treetype *parent, treetype *c)
{
	if (c->key < parent ->key)
		parent->left = NULL;
	else
		parent->right = NULL;
	delete c;
}
void deleteone(treetype *parent, treetype *c)
{
	treetype *child;
	if (c->left != NULL)
		child = c->left;
	else
		child = c->right;
	if (c->key < parent->key)
		parent->left = child;
	else
		parent->right = child;
	delete c;
}
void deletetwo(treetype *c)
{
	treetype *replace, *parent;
	replace = c->left;
	parent = c;
	while (replace->right != NULL)
	{
		parent = replace;
		replace = replace->right;
	}
	c->key = replace->key;
	if (replace->left == NULL)
		deleteleaf(parent, replace);
	else
		deleteone(parent, replace);
}
void deletetree(treetype *root, ofstream &outf, int key)
{
	treetype *c, *parent;
	c = root;
	parent = NULL;
	while (c != NULL && key != c->key)
	{
		parent = c;
		if (key < c->key)
			c = c->left;
		else
			c = c->right;
	}
	if (c != NULL && c->key == key)
	{
		if (c->left == NULL && c->right == NULL)
			deleteleaf(parent, c);
		else if (c->left != NULL && c->right != NULL)
			deletetwo(c);
		else
			deleteone(parent, c);
	}
	else
		outf << key << " not found." << endl;
}
void push(treetype *stack[], int &top, treetype *address)
{
	top++;
	stack[top] = address;

}
treetype *pop(treetype *stack[], int &top)
{
	treetype *temp;
	temp = stack[top];
	stack[top] = 0;
	top--;
	return temp;
}
void ipreordertrav(treetype *root, treetype *stack[], int &top, ofstream &outf)
{
	treetype *c;
	if (!emptytree(root))
	{
		push(stack, top, NULL);
		c = root;
		while (c != NULL)
		{
			outf << c->key << " ";
			if (c->right != NULL)
				push(stack, top, c->right);
			if (c->left != NULL)
				c = c->left;
			else
				c = pop(stack, top);
		}
		outf << endl;
	}
	else
		outf << "Tree is empty" << endl;
}
void preorder(treetype *c, ofstream &outf)
{
	outf << c->key << " ";
	if (c->left != NULL) preorder(c->left, outf);
	if (c->right != NULL) preorder(c->right, outf);
}
void iinordertrav(treetype *root, treetype *stack[], int &top, ofstream &outf)
{
	if (!emptytree(root))
	{
		treetype *c;
		push(stack, top, NULL);
		c = root; 
		while (c != NULL)
		{
			while (c->left != NULL)
			{
				push(stack, top, c);
				c = c->left;
			}
			bool done = false;
			while (!done)
			{
				outf << c->key << " ";
				if (c->right != NULL)
				{
					c = c->right;
					done = true;
				}
				else
				{
					c = pop(stack, top);
					if (c == NULL) done = true;
				}
			}
		}
		outf << endl;
	}
}
void inorder(treetype *c, ofstream &outf)
{
	if (c->left != NULL) inorder(c->left,outf);
	outf << c->key << " ";
	if (c->right != NULL) inorder(c->right, outf);
}
void postorder(treetype *c, ofstream &outf)
{
	if (c->left != NULL) postorder(c->left, outf);
	if (c->right != NULL) postorder(c->right, outf);
	outf << c->key << " ";
}
void preordertrav(treetype *root, ofstream &outf)
{
	if (!emptytree(root)) preorder(root, outf);
	else outf << "Tree is empty";
	outf << endl;
}
void inordertrav(treetype *root, ofstream &outf)
{
	if (!emptytree(root)) inorder(root, outf);
	else outf << "Tree is empty";
	outf << endl;
}
void postordertrav(treetype *root, ofstream &outf)
{
	if (!emptytree(root)) postorder(root, outf);
	else outf << "Tree is empty";
	outf << endl;
}
void main()
{
	treetype *root;
	treetype *stack[maxstack];
	int top;
	ofstream outf("Program4.ot");
	createtree(root);
	read(root);
	inordertrav(root, outf);
	deletetree(root, outf, 71);
	postordertrav(root, outf);
	deletetree(root, outf, 38);
	preordertrav(root, outf);
	createstack(stack, top);
	ipreordertrav(root, stack, top, outf);
	iinordertrav(root, stack, top, outf);
	system("pause");
}