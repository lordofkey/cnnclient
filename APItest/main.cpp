#include <opencv2\opencv.hpp>
#include "SenderAPI.h"
#include <windows.h>


void receive(char* s,int len, void* param)
{
	std::cout << s << std::endl;
}

int main()
{
	SetCallBack(receive);
	int index = 0;
	cv::Mat image, imageIn;
	image = cv::imread("1.jpg");
	cv::resize(image, image, cv::Size(640, 480));
	int i = 0;
	while(true)
	{
		i ++;
		if(SendImg(image, "pb_c"))
		{
			std::cout << "sended1" << std::endl;
		}
		Sleep(5);
	}
}