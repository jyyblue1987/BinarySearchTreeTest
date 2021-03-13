#pragma once
class plantermgr
{
public:
	plantermgr(void);

	void plant(int num, char *name);
	void harvest(char *name, int start, int stop);
	void prune(int num);
};

