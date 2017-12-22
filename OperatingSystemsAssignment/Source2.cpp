#include<iostream>
#include<vector>
#include<queue>
#include<fstream>
#include<string>
#include <windows.h>

using namespace std;

#include"pcb.h"
#include "logger.h"
#include"allocator3.h"

vector<pcb>processes;
vector<pcb>readyQueue;
vector<pcb>finished;

pcb running;

int quantum, switchtime;

int clk = 0;

//Utilities
void readFile();

void EnqueueArrivingProcesses();
void printQueueState();

logger output("Output.txt");
logger mylog("log.txt");

bool firstArrival=true;
int main()
{

//Reading the file

	readFile();

	//Create the memory allocator
	MemoryAllocator memalloc;
	string outputHeader = "process_id\trun_time\tarrival_time\tfinish_time\t\tmem_size\tmem_start\tmem_end\n";
	output.logtoFile(outputHeader);

	
	while (!processes.empty() || !readyQueue.empty()) //There are still processes to arrive

	{
		EnqueueArrivingProcesses();
		//printQueueState();

		if (!readyQueue.empty())
		{
			if (firstArrival)
			{
				firstArrival = false;
				printQueueState();

				running = readyQueue[0];
				running.updatepcb(0, clk); //The process has started
				readyQueue.erase(readyQueue.begin());
				memalloc.allocate(running);
				if (running.remainingTime - quantum > 0)
				{
					 //run and stop
					//sleep(quantum);
					running.updatepcb(2, clk+quantum);
					mylog.logProcess(running, clk, quantum);

					clk += quantum;
					
					EnqueueArrivingProcesses(); //check if a process has arrived before pushing the process to the end of the queue
					readyQueue.push_back(running);
					//printQueueState();

				}
				else//The process will finish
				{
					
					//_sleep(running.remainingTime);
					running.updatepcb(3, clk+running.remainingTime);
					mylog.logProcess(running, clk, running.remainingTime);
					clk += running.remainingTime;
					
					//now deallocate the procese
					memalloc.deallocate(running);

					output.logFinished(running);
					//EnqueueArrivingProcesses();
					//printQueueState();
				}
			}
			else
			{

				pcb temp = readyQueue[0];
				if ( (!(memalloc.allocate(temp)))) //not allocated before
				{

					readyQueue.erase(readyQueue.begin());
					if (temp.noAllocationCount <= 5) //
					{

						readyQueue.push_back(temp); //process cannot be executed;

					}
					else
					{
						cout << "Process cannot be allocated" << endl;
					}
					clk++;
					EnqueueArrivingProcesses();
					printQueueState();

				}
				else
				{
					//if (running.pid != temp.pid) //not same process
					{
						clk++;
						mylog.logSwitching(clk, switchtime);
						clk += switchtime;
						clk++;
						//	_sleep(switchtime);
						running = temp;
						printQueueState();
						if (running.laststopTime == 0)
						{
							running.updatepcb(0, clk);
						}
						else
						{
							running.updatepcb(1, clk); //resumed
						}
						readyQueue.erase(readyQueue.begin());
						if (running.remainingTime - quantum > 0)
						{

							//	_sleep(quantum);
							running.updatepcb(2, clk + quantum); //run and stop
							mylog.logProcess(running, clk, quantum);

							clk += quantum;

							EnqueueArrivingProcesses(); //check if a process has arrived before pushing the process to the end of the queue
							readyQueue.push_back(running);
							//printQueueState();

						}
						else//The process will finish
						{
							int temprmtime = running.remainingTime; 
							//_sleep(running.remainingTime);
							running.updatepcb(3, clk + running.remainingTime);
							mylog.logProcess(running, clk, temprmtime);
							clk += temprmtime;

							//now deallocate the procese
							memalloc.deallocate(running);
							finished.push_back(running);
							//output.logFinished(running);
							EnqueueArrivingProcesses();
							//printQueueState();
						}



					}

				}
			}

		}


	}
	

	sort(finished.begin(), finished.end());
	for (int i = 0; i < finished.size(); i++)
		output.logFinished(finished[i]);


	return 0;
}

void readFile()
{
	ifstream infile("input.txt");
	string s;
	int num;
	infile >> s >> num;
	quantum = num;
	infile >> s >> num;
	switchtime = num;
	infile >> s >> s >> s >> s;
	while (!infile.eof())
	{
		infile >> s;
		//num = atoi(s.substr(1).c_str());
		//create a pcb for the process
		pcb p;
		int  arrival, runtime, _size;
		infile >> runtime>>arrival  >> _size;
		p.setParameters(s, arrival, runtime, _size);
		processes.push_back(p);
	}
	infile.close();
}



void EnqueueArrivingProcesses()
{
	int i = 0;
	for (; i < processes.size(); i++)
	{
		if (processes[i].arrivalTime > clk)
			break;
		readyQueue.push_back(processes[i]);
		
	}
	if(!processes.empty())processes.erase(processes.begin(),processes.begin()+i);
}
void printQueueState()
{
	if(readyQueue.size()>0)mylog.logtoFile("Queue: ");
	int i = 0;
	for (; i < readyQueue.size()-1; i++)
	{
		
		mylog.logtoFile(readyQueue[i].pid + ", ");
		
	}
	if (readyQueue.size() >0) mylog.logtoFile(readyQueue[i].pid + "\n");

}