#pragma once
#include<iostream>
using namespace std;
class node
{
public:
	node* left;
	node* right;
	node* parent;
	bool allocated;

	node();
	

};

class allocator2
{

	
	node* root;
    public:
		allocator2();
	int getlevel(int size);
	int allocate(int level);
	void deallocate(int index);
	int allocateProcess(int level);
	int getParent(int index);
	int getminindex(int level);
	int getmaxindex(int level);

	bool allocatenode(int level, int currentlevel,node * n);
	bool canallocate(int i, int & index);






};