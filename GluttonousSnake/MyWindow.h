#pragma once

#include <MainWindow.h>
#include "meta.h"

class MyWindow :
	public MainWindow
{
public:
	MyWindow(HINSTANCE hInstance);
	~MyWindow();

protected:
	LRESULT HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void OnPaint(HDC hdc, PAINTSTRUCT ps);
	void OnCreate();
	void OnDestroy();
	void OnResize(int width, int height);
	void OnKeyUp(WPARAM keyCode);
	void OnKeyDown(WPARAM keyCode);

public:
	int width{ 0 };
	int height{ 0 };
};