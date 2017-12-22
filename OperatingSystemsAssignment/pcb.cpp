#include "pcb.h"


pcb::pcb()
{
	totalwait = 0;
	noAllocationCount = 0;
	arrivalTime = -1;
	this->startAddress = -1; //not allocated
	laststopTime = 0;
     
}

void pcb::setParameters(string pid, int arrivaltime, int runtime, int _size)
{
	this->pid = pid;
	this->arrivalTime = arrivaltime;
	this->runtime = runtime;
	this->p_size = _size;
	this->remainingTime = runtime;
	
}

void pcb::updatepcb(int newstate, int curtime)
{
	state = newstate;
	if (newstate == 0) //ready the process has just started
	{
		executionStart = curtime;
		totalwait += (executionStart - arrivalTime);
	}

	else if (newstate == 1) //resumed process
	{
		executionStart = curtime;
		totalwait += (executionStart - laststopTime);

	}
	else if (newstate == 2) //stopped process
	{
		laststopTime = curtime;
		remainingTime =remainingTime-(curtime - executionStart);
	}
	else
	{
		finishTime = curtime;
		remainingTime = 0;
	}

}

void pcb::setStartAddress(int address)
{
	this->startAddress = address;
}

void pcb::incrementAllocationCount()
{
	noAllocationCount++;
}