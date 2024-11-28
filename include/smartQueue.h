#pragma once
#include<vector>
#define ull unsigned long long

template <class T>
class smart_queue
{
	struct sqNode
	{
		T data;
		sqNode* next = nullptr;
		ull prior;

		sqNode(const T& dat, ull pr) : data(dat), prior(pr){}
	};
	size_t size = 0;
	sqNode* head = nullptr;
	sqNode* tail = nullptr;
public:
	void push(const T& val, ull priority=0)
	{

		sqNode* n = new sqNode(val, priority);
		if (!tail)
			head = tail = n;
		else
		{
			tail->next = n;
			tail = n;
		}

	}

	//Вставить с учётом приоритета
	void insert(const T& val, ull priority)
	{
		sqNode* p = nullptr;
		sqNode* pnext = head;

		if (pnext && (pnext->prior < priority))
		{
			while (pnext)
			{
				p = pnext;
				pnext = p->next;

				if (pnext && (pnext->prior >= priority))
					break;
			}
		}
		
		sqNode* n = new sqNode(val, priority);
		if (p)
			p->next = n;
		else
			tail = head = n;
		n->next = pnext;
		if (!pnext)
			tail = n;

	}

	T& top()
	{
		return head->data;
	}

	void pop()
	{
		if(head)
		{
			sqNode* nhead = head->next;
			delete head;
			head = nhead;
		}
	}
};