#include "cluster.h"

void Cluster::addTask(Task& t)
{
	q.insert(t, t.cycles * cyclesW + t.ncores * coresW + tick);
}

void Cluster::process()
{
	Task* candidate = 0;
	
	candidate= &(q.top());
	while (candidate&&(candidate->ncores <= cores - busy))
	{
		engaged.push_back(*candidate);
		q.pop();
		candidate = &(q.top());
	}
	tick += 1;

	for (int i = 0;i < engaged.size();i++)
	{
		engaged[i].cycles -= 1;
		if (engaged[i].cycles <= 0)
		{
			busy -= engaged[i].ncores;
			engaged.erase(engaged.begin() + i);
			completed++;
		}
	}
}
