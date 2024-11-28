#include "smartQueue.h"

#include <gtest.h>

TEST(smart_queue, can_create_sq)
{
	ASSERT_NO_THROW(smart_queue<int> q);
}

TEST(smart_queue, can_push_sq)
{
	smart_queue<int> q;
	ASSERT_NO_THROW(q.push(42); q.push(314));
}

TEST(smart_queue, can_pop)
{
	smart_queue<int> q;
	q.push(42);
	ASSERT_NO_THROW(q.pop(); q.pop());
}

TEST(smart_queue, get_top_in_right_order)
{
	smart_queue<int> q;
	q.push(42); 
	q.push(314);
	ASSERT_EQ(q.top(), 42);
	q.pop();
	ASSERT_EQ(q.top(), 314);
}

TEST(smart_queue, insert_in_right_order)
{
	smart_queue<int> q;
	q.insert(1, 100);
	q.insert(2, 200);
	q.insert(3, 1);

	ASSERT_EQ(q.top(), 3);
	q.pop();
	ASSERT_EQ(q.top(), 1);
	q.pop();
	ASSERT_EQ(q.top(), 2);
	q.pop();
}


