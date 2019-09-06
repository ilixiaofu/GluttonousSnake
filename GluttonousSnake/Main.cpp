#include "MyWindow.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���:
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������


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
	// ��ʼ��ȫ���ַ���
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_GLUTTONOUSSNAKE, szWindowClass, MAX_LOADSTRING);
	HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GLUTTONOUSSNAKE));
	HICON hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
	myWindow.InitWindowInstance(szWindowClass, szTitle, hIcon, hIconSm);
	int iret = myWindow.exec();

	GdiplusShutdown(gdiplusToken);
	return iret;
}