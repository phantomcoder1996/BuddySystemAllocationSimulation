#pragma once
#include<cmath>
class allocator
{
	int arr[2047];
public:

	int getlevel(int size);
	int allocate(int level);
	void deallocate(int index);
	int allocateProcess(int level);
	int getParent(int index);
	int getminindex(int level);
	int getmaxindex(int level);


	bool canallocate(int i, int & index);
};