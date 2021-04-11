#include "screenshot.h"

screenshot::screenshot() {
	// Параметры экрана
	HWND hwnd = GetDesktopWindow();
	m_hWDC = GetWindowDC(hwnd);
	m_width = GetSystemMetrics(SM_CXSCREEN);
	m_height = GetSystemMetrics(SM_CYSCREEN);

	m_left = static_cast<int>(m_width / 2 - ACTIVATION_RANGE / 2);
	m_top = static_cast<int>(m_height / 2 - ACTIVATION_RANGE / 2);
	int x2 = static_cast<int>(m_width / 2 + ACTIVATION_RANGE / 2);
	int y2 = static_cast<int>(m_height / 2 + ACTIVATION_RANGE / 2);

	m_width = x2 - m_left + 1;
	m_height = y2 - m_top + 1;

	m_hScreen = CreateCompatibleDC(m_hWDC);
	m_hBitmap = CreateCompatibleBitmap(m_hWDC, m_width, m_height);
	m_hGDI_temp = SelectObject(m_hScreen, m_hBitmap);

	m_bitmapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_bitmapinfo.bmiHeader.biWidth = m_width;
	m_bitmapinfo.bmiHeader.biHeight = -m_height;
	m_bitmapinfo.bmiHeader.biPlanes = 1;
	m_bitmapinfo.bmiHeader.biBitCount = 24;
	m_bitmapinfo.bmiHeader.biCompression = BI_RGB;

	int step = static_cast<int>(ceil(m_width * 3 / static_cast<double>(4))) * 4; // Шаг строки
	m_data = new char[step * m_height];

	m_screen = new cv::Mat(m_height, m_width, CV_8UC3, m_data, step);
}

screenshot::~screenshot() {
	SelectObject(m_hScreen, m_hGDI_temp);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hScreen);
	delete m_screen;
	delete[] m_data;
}

cv::Mat& screenshot::get() {
	BitBlt(m_hScreen, 0, 0, m_width, m_height, m_hWDC, m_left, m_top, SRCCOPY);
	GetDIBits(m_hScreen, m_hBitmap, 0, m_height, m_data, &m_bitmapinfo, DIB_RGB_COLORS);
	return *m_screen;
};