#include "plantermgr.h"
#include <iostream>
#include <string.h>

#define NULL 0

using namespace std;

plantermgr::plantermgr(void)
{
	root = NULL;
	size = 0;
}

plantermgr::~plantermgr(void) 
{
	clear();
}

bool plantermgr::clear() {
	freeNodeTree(root);
	root = NULL;
	size = 0;

	return true;
}

void plantermgr::freeNodeTree(planter* node) {
	if (node != NULL)
	{
		freeNodeTree(node->left);
		freeNodeTree(node->right);

		delete node->name;
		delete node;
	}
}

planter * plantermgr::insert(planter * root, planter * newNode) {
	if (root == NULL)
		return newNode;
	if (newNode == NULL)
		return root;

	int key = newNode->num;
	if (key < root->num)
		root->left = insert(root->left, newNode);
	else if (key > root->num)
		root->right = insert(root->right, newNode);

	return root;
}


void plantermgr::plant(int num, char *name) 
{
	planter *node = new planter;
	node->left = NULL;
	node->right = NULL;
	node->num = num;
	node->name = new char[strlen(name) + 1];
	strcpy(node->name, name);

	cout << "Planting " << name << " in box " << num << endl;

	root = insert(root, node);
}

void plantermgr::harvest(char *name, int start, int end)
{
	if (root == NULL)
		return;

	cout << "Harvesting " << name << " from boxes " << start << " to " << end << ". The following boxes will be harvested:";

	search(root, name, start, end);

	cout << endl << endl;	
}

void plantermgr::search(planter *root, char *name, int start, int end)
{
	if( start > end )
		return;

	if( root == NULL )
		return;

	search(root->left, name, start, end);

	if( strcmp(name, root->name) == 0 && start <= root->num && root->num <= end )
		cout << " " << root->num;

	search(root->right, name, start, end);
}


void plantermgr::prune(int num)
{
	if (root == NULL)
		return;

	cout << "Pruning box number " << num << "." << endl;

	planter *curNode = root;
	planter* prevNode = root;

	while (curNode != NULL) {
		if (curNode->num == num)
			break;

		prevNode = curNode;
		if (curNode->num < num)
			curNode = curNode->right;
		else if (curNode->num > num)
			curNode = curNode->left;		
	}

	if (curNode == NULL)
		return;

	if (curNode == root) {
		root = curNode->left;
		root = insert(root, curNode->right);
	}
	else {
		if (curNode->num < prevNode->num)
			prevNode->left = NULL;
		else
			prevNode->right = NULL;
		root = insert(root, curNode->left);
		root = insert(root, curNode->right);
	}

	delete curNode->name;
	delete curNode;

	size--;

}