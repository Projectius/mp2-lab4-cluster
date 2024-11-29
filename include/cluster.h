#pragma once

#include "smartQueue.h"
#include <string>
#include<iostream>

using namespace std;

class Task
{
public:
	string id;
	int ncores;
	ull cycles;
	Task(string id, int cores, ull cycles) :id(id), ncores(cores), cycles(cycles) {}
};


///////////////////////////////////////////


class Cluster
{
	int cores;
	smart_queue<Task> q;
	vector<Task> engaged;
	int busy = 0;

	ull tick = 0;

	//веса для распределения задач
	int cyclesW = 1;
	int coresW = 4;

	int completed = 0;

public:

	Cluster(int cpu_count) :cores(cpu_count) { //cout << "CORES " << cores << endl; 
	}

	void process()
	{
		Task* candidate = 0;

		candidate = &(q.top());
		while (candidate && (candidate->ncores <= cores - busy))
		{
			engaged.push_back(*candidate);
			busy += candidate->ncores;

			//cout << tick<<" <<<<    engaged: " << candidate->id << " free "<< (cores - busy) << endl;

			q.pop();
			candidate = &(q.top());
		}
		

		for (int i = 0;i < engaged.size();i++)
		{
			engaged[i].cycles -= 1;
			//cout << tick << " <<<<    updated: " << engaged[i].id << " remaining " << engaged[i].cycles << endl;
		}

		for (int i = engaged.size()-1;i >=0;i--)
		{
			if (engaged[i].cycles <= 0)
			{
				busy -= engaged[i].ncores;
				//cout << tick << " <<<<    ended: " << engaged[i].id << " free " << (cores - busy) << endl;
				engaged.erase(engaged.begin() + i);
				completed++;
			}
		}
		tick += 1;
	}

	int getCompleted() { return completed; }
	int getBusy() { return busy; }

	void addTask(Task& t)
	{
		q.insert(t, t.cycles * cyclesW + t.ncores * coresW + tick);
	}
	

	vector<Task> getEngagedList() { return engaged; }

};

