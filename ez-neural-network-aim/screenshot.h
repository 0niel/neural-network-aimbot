#pragma once
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include "defines.h"

class screenshot {
public:
	screenshot();
	~screenshot();
	cv::Mat& get();

private:
	HDC m_hWDC;
	HDC m_hScreen;
	HBITMAP m_hBitmap;
	BITMAPINFO m_bitmapinfo;

	int m_width;
	int m_height;

	int m_left;
	int m_top;

	char* m_data;
	cv::Mat* m_screen;

	HGDIOBJ m_hGDI_temp;
};