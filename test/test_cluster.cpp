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

