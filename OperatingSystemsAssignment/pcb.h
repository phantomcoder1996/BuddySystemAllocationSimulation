#pragma once
#ifndef pcb_h
#define pcb_h

#include<string>
using namespace std;

class pcb
{
public:
	string pid;
	int arrivalTime;
	//int executionTime;
	int remainingTime;
	int state;   //0 ready
				 //1 resumed
				 //2 stopped
				 //3 finished
	int runtime;
	//int priority;
	int totalwait;
	int laststopTime;
	int executionStart;
	int finishTime;
	int p_size;  //needed to determine the end address and the level

	int startAddress;
	int noAllocationCount; //A counter to determine if a process cannot be allocated for less than or equal 5 times 
						   //then it will be blocked
	//bool allocated;
	pcb();
	void setParameters(string pid, int arrivaltime, int runtime, int _size);
	void updatepcb(int newstate, int curtime);
	void setStartAddress(int address);

	void incrementAllocationCount();

	bool operator<(pcb p2)
	{
		return pid < p2.pid;
	}
};









#endif