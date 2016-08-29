#pragma once



class MyImg
{
public:
	MyImg(void);
	~MyImg(void);
	cv::Mat img;
	char m_name[128];
	char result[128];
	void* param;
	int index;
};

