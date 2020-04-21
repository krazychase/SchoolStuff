//Chase Brown
//Explore Trees

#include<iostream>
#include<fstream>
using namespace std;

const int MAXTREE = 100;							// Max amount of nodes

struct treetype
{
	int num;
	bool threaded;
	treetype *left, *right;
};

bool emptyArrayTree(int tree[])
{
	return tree[1] == -1;							// Test for Array Tree init data
}

bool emptyThreadedTree(treetype *root)
{
	return root->num == -1;							// Test for Threaded Tree init data
}

void initArrayTree(int tree[])
{
	int i;
	for (i = 0; i < MAXTREE; i++)tree[i] = -1;
}

void createtree(treetype *&root)
{
	root = new treetype;							// Create root
	root->num = -1;									// Set data
	root->threaded = false;
	root->left = NULL;
	root->right = NULL;
}

void insertArrayTree(int tree[], int num)
{ 
	int i = 1;
													/*
													 * while not empty
													 * 	search to insert
													 * 	set data if enough space
													 * else set 1 to data
													 * */
	if (!emptyArrayTree(tree))
	{
		while (tree[i] != -1)
		{
			if (tree[i] > num) i *= 2;
			else i = i * 2 + 1;
		}
		if (i < MAXTREE) tree[i] = num;
	}
	else tree[1] = num;
}

void insertThreadedTree(treetype *root, int num)
{
	treetype *nu, *c, *parent;
	if (!emptyThreadedTree(root))					// If not empty
	{
		nu = new treetype;							// Create new node
		nu->num = num;								// Set data fields
		nu->threaded = false;
		nu->left = NULL;
		nu->right = NULL;
		c = root;									// Set c to root
		parent = root;								// Set parent to root
		while (c != NULL && c->threaded == false)	// While not at the end of tree
		{
			parent = c;								// Move parent up
			if (nu->num < c->num)					// Set c accordingly
				c = c->left;
			else
				c = c->right;
		}
		if (nu->num < parent->num)					// If num is less
		{
			nu->threaded = true;					// Set threads
			nu->right = parent;
			parent->left = nu;						// Set data
		}
		else
		{
			nu->threaded = parent->threaded;		// Set threads
			nu->right = parent->right;
			parent->right = nu;						// Set data
			parent->threaded = false;
		}
	}
	else
		root->num = num;							// Set root as nu
}

void read(int tree[], treetype *root)				// Read in Array Tree
{
	ifstream inf("data.dat");
	int num;
	while (!inf.eof())
	{
		inf >> num;
		insertArrayTree(tree, num);
		insertThreadedTree(root, num);
	}
}

void inorder(int tree[], int i, ofstream &outf)
{
	if (!emptyArrayTree(tree))
	{
		if (2 * i < MAXTREE && tree[2 * i] != -1)	
			inorder(tree, 2 * i, outf);				// Travel to left, visit node
		outf << tree[i] << endl;					// Print data inorder, least to greatest
		if (2 * i < MAXTREE && tree[2 * i + 1] != -1)
			inorder(tree, 2 * i + 1, outf);			// Travel right
	}
	else outf << "Tree is empty!\n";
}

void traverseTree(treetype *root, ofstream &outf)	// Threaded Traverse
{
	treetype *c;
	bool done;
	if (!emptyThreadedTree(root))
	{
		c = root;
		while (c != NULL)							// While not at end of tree
		{
			while(c->left != NULL)
				c = c->left;						// Travel to left most node
			done = false;
			while (!done)
			{
				outf << c->num << endl;				// Print data in order, least to greatest
				if (!c->threaded)
					done = true;					// Done when no more threads
				c = c->right;
				if (c == NULL)
					done = true;					// Done when at end of tree
			}
		}
	}
	else
		outf << "\nTree is Empty!\n";
}

int main()											// Test Everything
{
	ofstream outf("output.ot");
	int tree[MAXTREE];
	treetype *root;
	initArrayTree(tree);
	createtree(root);
	read(tree, root);
	outf << "Array Tree\n";
	inorder(tree, 1, outf);
	outf << "\nThreaded Tree\n";
	traverseTree(root, outf);
	system("pause");
	return 0;
}
