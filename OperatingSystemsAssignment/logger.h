#pragma once
#include <stdio.h>
#include "pcb.h"
#include <fstream>
#include<cmath>
using namespace std;


#define maxMemSize 1024
#define blocksize(level) maxMemSize/(1<<level)

class logger
{
	ofstream outfile;

public:

	logger(const char* fname);
   // void logProcess(pcb process, int curtime);
	void logProcess(pcb process,int clk, int q);
	void logFinished(pcb process);
	void logtoFile(string s);
	void logSwitching(int clk, int switchtime);
    ~logger();

};