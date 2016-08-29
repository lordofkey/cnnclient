// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "socket-lib/Socket.hpp"

using namespace cv;
using namespace std;

typedef int ssize_t;


#define  PORT 8145
#define  IP_ADDRESS "172.1.10.134"

Socket::TCP server;
MyQueue que;
PF proresul = NULL;

void process(MyImg* pimg)
{
	try
	{
		server.send<char>(pimg->m_name, 128);
		server.send_buffer(pimg->img.data, (size_t)pimg->img.cols, (size_t)pimg->img.rows);
		server.receive<char>(pimg->result, 128);
	}
	catch (Socket::SocketException &e)
	{
		cout << e << endl;
	}
}


DWORD WINAPI SendFun(LPVOID pM)  
{
	char *pre;
	MyImg *pimg;
	while (true)
	{
		pimg = (MyImg *)que.pop();
		if(pimg == NULL)
		{
			Sleep(200);
			continue;
		}
		if (!pimg->img.data)                              // Check for invalid input
		{
			cout << "Could not open or find the image" << std::endl;
			continue;
		}
		//TODO 图片检查
		try
		{
			server.connect_to(Socket::Address(IP_ADDRESS, PORT));
		}
		catch (Socket::SocketException &e)
		{
			cout << e << endl;
//TODO回掉处理函数
			server.close();
			continue;
		}

		//vector<uchar> buff;//buffer for coding
		//cv::Mat tmp = pimg->img;
		//cv::imencode(".tiff", tmp, buff);
		//std::cout << tmp.rows << ":" << tmp.cols << ":" << buff.size() << std::endl;

		process(pimg);
		pre = new char[128];
		strcpy(pre,pimg->result);
		if(proresul != NULL)
			proresul(pre, 128, pimg->param);
		delete pimg;
		pimg = NULL;
		server.close();
	}

}  
DWORD WINAPI RevFun(LPVOID pM)  
{
	return 0;
} 


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	HANDLE sendthread;
	HANDLE revthread;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		sendthread = CreateThread(NULL, 0, SendFun, NULL, 0, NULL);
		revthread = CreateThread(NULL, 0, RevFun, NULL, 0, NULL);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}