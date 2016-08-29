#include "StdAfx.h"
#include "MyQueue.h"


MyQueue::MyQueue(void)
{
	rankinitial();
}


MyQueue::~MyQueue(void)
{
}

#pragma region 列队维护
//列队初始化
void MyQueue::rankinitial()
{
	rankMutex = CreateMutex(NULL,false,NULL);
	p_start = p_end = 0;
	ranksize = 100;
	for(int i = 0;i < 100;i++)
	{
		p_rank[i] = NULL;
	}
}

//入栈
bool MyQueue::pump(void *p)
{
	WaitForSingleObject(rankMutex,INFINITE);
	if(((p_end+1)%ranksize) == p_start)
	{
		ReleaseMutex(rankMutex);
		return false;
	}
	p_rank[p_end] = p;
	//入列数据
	//
	//
	//
	p_end = (p_end+1)%ranksize;
	ReleaseMutex(rankMutex);
	return true;
}

//销毁列队
void MyQueue::destroyrank()  
{
	p_start = p_end = 0;
	for(int i = 0;i < 100;i++)
	{
		if(p_rank[i] != NULL)
		{
			delete p_rank[i];
			p_rank[i] = NULL;
		}
	}
}
/*出栈*/  
void *MyQueue::pop()  
{  
	WaitForSingleObject(rankMutex,INFINITE);
	void *output;  
	if(p_start == p_end)
	{
		ReleaseMutex(rankMutex);
		return NULL;
	}
	output = p_rank[p_start];
	/////////////////////////////////////出栈时一定要将指针归NULL
	p_rank[p_start] = NULL;
	p_start = (p_start + 1)%ranksize;
	ReleaseMutex(rankMutex);
	return output;
}  
#pragma endregion