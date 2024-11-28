#pragma once

#include "smartQueue.h"
#include <string>

using namespace std;

class Task
{
public:
	string id;
	int ncores;
	ull cycles;	
	Task(string id, int cores, ull cycles):id(id),ncores(cores),cycles(cycles){}
};


///////////////////////////////////////////


class Cluster
{
	int cores;
	smart_queue<Task> q;
	vector<Task> engaged;
	int busy;

	ull tick;

	//веса для распределения задач
	int cyclesW = 2;
	int coresW = 16;

	int completed = 0;
	
public:

	Cluster(int cpu_count):cores(cpu_count){}

	void addTask(Task& t);
	void process();

	vector<Task> getEngagedList() { return engaged; }

};