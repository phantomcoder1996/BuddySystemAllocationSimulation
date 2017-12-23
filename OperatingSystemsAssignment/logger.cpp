#include <stdio.h>

#include "pcb.h"

#include "logger.h"



	logger::logger(const char* fname)
	{
	//	fptr = fopen(fname, "r");
		 outfile=ofstream(fname);
	}

	/*void logger::logProcess(pcb process, int curtime)
	{
		// int pid,arrtime,runtime,remain,wait;
		int wait;
		double wta;
		int ta;
		const char * states[4] = { "started","resumed","stopped","finished" };
		switch (process.state)
		{
		case 0:
		{
			//state="started";
			wait = process.executionStart - process.arrivalTime;
			break;
		}
		case 1:
		{
			//state="resumed";
			wait = process.executionStart - process.laststopTime;
			break;
		}
		case 2:
		{
			//state="stopped";
			wait = 0; //TODO: REVISE THAT CONDITION
			break;
		}
		case 3:
		{
			//state="finished";
			wait = process.totalwait;
			ta = process.finishTime - process.arrivalTime;
			wta = double(ta) / process.runtime;
			break;
		}
		default:
			break;
		}

		if (process.state == 3)

			fprintf(fptr, "At time %d process %d %s arr %d total %d remain %d wait %d TA %d WTA %.2f \n", process.executionStart, process.pid, states[process.state], process.arrivalTime, process.runtime, process.remainingTime, wait, ta, wta);
		else
			fprintf(fptr, "At time %d process %d %s arr %d total %d remain %d wait %d \n", process.executionStart, process.pid, states[process.state], process.arrivalTime, process.runtime, process.remainingTime, wait);

	}
	*/

	void logger::logProcess(pcb process, int clk, int q)
	{
		//	int level = 10 - int(ceil(log2(process.p_size)));
		int endaddress = process.startAddress + (1 << ((int)(ceil(log2(process.p_size+6))))) - 1;
		switch (process.state)
		{
		case 2://stopped
		{

			outfile << "Executing process " << process.pid << "\t: started at " << clk << ", stopped at " << (clk+q) << ", " << process.remainingTime << " remaining memory starts at " << process.startAddress << " and ends at " << endaddress << endl;
			break;
		}
		case 3://finished
		{

			outfile << "Executing process " << process.pid << "\t: started at " << clk << ", finished at " << (clk+q) << ", memory starts at " << process.startAddress << " and ends at " << endaddress << endl;
			break;
		}

		default:
			break;
		}

	}


	void logger::logFinished(pcb process)
	{
	//	outfile << "process_id\trun_time\tarrival_time\tfinish_time\tmem_size\tmem_start\tmem_end" << endl;
		if (process.startAddress != -1)
		{
			int endaddress = process.startAddress + (1 << ((int)(ceil(log2(process.p_size + 6))))) - 1;
			outfile << process.pid << "\t\t\t" << process.runtime << "\t\t\t" << process.arrivalTime << "\t\t\t\t" << process.finishTime << "\t\t\t\t" << process.p_size << "\t\t\t" << process.startAddress << "\t\t\t" << endaddress << endl;
		}
		else
		{
			outfile << process.pid << "\t\t\t"<< "Process cannot be allocated" << endl;
		}
		
	}



	void logger::logtoFile(string s)
	{
		outfile << s;
	}
	logger::~logger()
	{
		//fclose(fptr);
		outfile.close();
	}
	void logger::logSwitching(int clk,int switchtime)
	{
		outfile << "Process switching\t\t: started at " << clk << ", finished at " << (clk + switchtime)<<endl;
	}
