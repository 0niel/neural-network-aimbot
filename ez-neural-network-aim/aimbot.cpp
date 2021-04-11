#include "aimbot.h"

void aimbot::aim_to(int x, int y, int box_w, int box_h) {
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);

	x = static_cast<int>(w / 2 - ACTIVATION_RANGE / 2 + x + box_w / 2);
	y  = static_cast<int>(h / 2 - ACTIVATION_RANGE / 2 + y + box_h / 2);
	SetCursorPos(x, y);
}