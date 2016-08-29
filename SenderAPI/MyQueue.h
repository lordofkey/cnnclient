#pragma once


class MyQueue
{
private:
	HANDLE rankMutex;	                        //队列锁
	void *p_rank[100];                       //拟合数据列队
	int p_start;                               //列队起始位置指针
	int p_end;                                    //列队结尾指针
	int ranksize;                                 //列队容量
public:
	MyQueue(void);
	~MyQueue(void);
	void rankinitial();
	bool pump(void *p);
	void destroyrank();
	void* pop();  
};
