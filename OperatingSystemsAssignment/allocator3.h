#pragma once
#include "pcb.h"
#include "logger.h"
#include <vector>
#include <iostream>
#include<cmath>
#include<algorithm>
using namespace std;

#define maxMemSize 1024
#define blocksize(level) maxMemSize/(1<<level)
#define index(nodeAdd,level) nodeAdd/blocksize(level)

struct node
{
	int startAdd;

}; 

class MemoryAllocator
{
public:

	vector<vector<int>>buddylist;


public:

	MemoryAllocator();
	bool allocate(pcb & p);
	void deallocate(pcb & p);
	bool canallocate(pcb p);

};