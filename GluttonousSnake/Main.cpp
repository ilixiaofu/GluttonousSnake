#include "MyWindow.h"

#define MAX_LOADSTRING 100

// 全局变量:
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)

{
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	MyWindow myWindow(hInstance);
	// 初始化全局字符串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_GLUTTONOUSSNAKE, szWindowClass, MAX_LOADSTRING);
	HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GLUTTONOUSSNAKE));
	HICON hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
	myWindow.InitWindowInstance(szWindowClass, szTitle, hIcon, hIconSm);
	int iret = myWindow.exec();

	GdiplusShutdown(gdiplusToken);
	return iret;
}