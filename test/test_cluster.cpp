#include <gtest.h>
#include "cluster.h"

using namespace std;

TEST(Cluster, can_create_cluster)
{
	ASSERT_NO_THROW(Cluster c(4));
}

TEST(Cluster, can_add_tasks)
{
	Cluster c(4);
	Task t{ "T", 1, ull(1) };
	ASSERT_NO_THROW(c.addTask(t));
}

TEST(Cluster, task_in_progress)
{
	Cluster c(4);
	Task t{ "T", 1, 10 };
	c.addTask(t);
	c.process();
	ASSERT_EQ(c.getEngagedList()[0].id, t.id);
}

TEST(Cluster, can_complete_task)
{
	Cluster c(4);
	Task t{ "T", 1, ull(1) };
	c.addTask(t);
	ASSERT_EQ(c.getCompleted(), 0);
	for(int i=0;i<10;i++)
		c.process();
	ASSERT_EQ(c.getCompleted(), 1);
}

TEST(Cluster, doing_light_tasks_when_cant_heavy)
{
	Cluster c(8);
	Task big{ "big", 6, 20 };
	Task smol{ "smol", 2, 10 };
	c.addTask(smol);
	c.addTask(smol);
	c.addTask(big);
	c.addTask(smol);
	c.addTask(smol);
	for (int i = 0;i < 5;i++)
		c.process();
	ASSERT_EQ(c.getEngagedList().size(), 4);
	for (int i = 0;i < 6;i++)
		c.process();
	ASSERT_EQ(c.getEngagedList().size(), 1);
}

TEST(Cluster, heavy_task_cant_be_delayed_forever) //лёгкие задачи добавляются бесконечно, но приоритетная система со временем перестанет добавлять их в начало очереди
{
	Cluster c(8);
	Task big{ "big", 6, 10 };
	Task smol{ "smol", 3, 3 };
	c.addTask(smol);
	c.addTask(smol);
	c.addTask(big);

	bool found = 0;
	for (int i = 0;i < 500;i++)
	{
		c.addTask(smol);
		c.process();
		auto e = c.getEngagedList();
		for (int j = 0;j < e.size();j++)
		{
			if (e[j].id == "big")
			{
				found = 1;
				break;
			}
		}
		if (found)
			break;
	}


		ASSERT_TRUE(found);
}



