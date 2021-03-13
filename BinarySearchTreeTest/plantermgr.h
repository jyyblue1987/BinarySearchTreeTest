#pragma once
struct planter {
	int num;
	char *name;

	planter *left;
	planter *right;
};

class plantermgr
{
private:
	planter* root;		// root to the left
	int size;

	bool clear();
	planter* insert(planter *root, planter *newNode);
	void freeNodeTree(planter* node);
	void search(planter *root, char *name, int start, int end);

public:
	plantermgr(void);
	~plantermgr();

	void plant(int num, char *name);
	void harvest(char *name, int start, int stop);
	void prune(int num);
};

