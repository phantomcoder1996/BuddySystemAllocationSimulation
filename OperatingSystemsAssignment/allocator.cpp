#include"allocator.h"


int allocator::getlevel(int size)
{
	return 10 - int(ceil(log2(size)));
}
int allocator::allocate(int level)
{
	int mini = getminindex(level);
	int maxi = getmaxindex(level);
	int i = mini;
	int index = -1;
	while (!canallocate(i,index) && i <= maxi)
	{
		i++;
	}
	return index;
}
void allocator::deallocate(int index)
{

	
}
int allocator::allocateProcess(int level)
{

}

int allocator::getParent(int index)
{
	return (index - 1) / 2;
}
int allocator::getminindex(int level)
{
	return int(pow(2, level) - 1);
}
int allocator::getmaxindex(int level)
{
	return int(pow(2, level + 1) - 2);
}

bool allocator::canallocate(int i, int & index)
{
	if (arr[i] == 0)
	{
		int parent = getParent(i);
		//()
	}
	return true;
}