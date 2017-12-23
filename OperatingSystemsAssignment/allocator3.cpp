#include "allocator3.h"


MemoryAllocator::MemoryAllocator()
{
	buddylist = vector<vector<int>>(11);
	buddylist[0].push_back(0);
}

bool MemoryAllocator::allocate(pcb & p)

{


	

	if (p.startAddress != -1) return true; //process already alloacted
	 
	int level = 10 - int(ceil(log2(p.p_size+6)));
	int i = level;
	if (!buddylist[i].empty())
	{
	  p.startAddress=buddylist[i][0];
	  //////////////will do something ////////////maybe/////////////
	  buddylist[i].erase(buddylist[i].begin());
	  return true;
	}
	while (i >= 0 &&buddylist[i].empty() )
	{
		--i;
	}
	if (i == -1)
	{
		p.noAllocationCount++; 
		return false;
	}
	int startAdd=buddylist[i][0];

	buddylist[i].erase(buddylist[i].begin());

	while (i != level) //i is the first non-empty level greater than size
	{
		
		//int startAdd = (buddylist[i][0] + blocksize(i)) / 2;
		buddylist[++i].push_back(startAdd + (blocksize(i)) / 2);
		//temp = startAdd; 
		//sort(buddylist[i ].begin(), buddylist[i ].end());
		//++i;
	}
	//int startAdd = (buddylist[i - 1][0]) - blocksize(i - 1);
	//buddylist[i].push_back(startAdd);
	
	p.startAddress = startAdd;
	
	return true;
    


}

void MemoryAllocator::deallocate(pcb &p)
{
	int level = 10 - int(ceil(log2(p.p_size+6)));

	int start_add= p.startAddress;
	int x = blocksize(level);
	int indx = start_add / x;
	bool canMerge = true;
	int j = level;
	while (canMerge&&j>=0)
	{
		x = blocksize(j);
		indx = start_add /x;
		
		if (indx % 2 == 0)
		{
			vector<int>::iterator it = find(buddylist[j].begin(), buddylist[j].end(), (indx + 1)*blocksize(j));
			if (it != buddylist[j].end())
			{
				buddylist[j].erase(it);
				
//				start_add = p.startAddress;
				


			}
			else
			{
				buddylist[j].push_back(start_add);
				sort(buddylist[j ].begin(), buddylist[j ].end());
				canMerge = false;

			}
		}
		else
		{
			vector<int>::iterator it = find(buddylist[j].begin(), buddylist[j].end(), (indx - 1)*blocksize(j));
			if (it != buddylist[j].end())
			{
				buddylist[j].erase(it);
				start_add = (indx - 1)*blocksize(j);
				


			}
			else {
				buddylist[j].push_back(start_add);
				sort(buddylist[j].begin(), buddylist[j].end());
				canMerge = false;

			}

		}
		--j;
	}

	
}

bool MemoryAllocator::canallocate(pcb p)
{
	return false;
}