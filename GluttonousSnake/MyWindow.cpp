#include "MyWindow.h"
#include "Snake.h"

Node* food;
Snake* snake;
int basex = 0;
int basey = 55;
int map_w = 0;
int map_h = 0;

MyWindow::MyWindow(HINSTANCE hInstance) :MainWindow(hInstance)
{
}

MyWindow::~MyWindow()
{
}

LRESULT MyWindow::HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SIZE:
		this->OnResize(LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_ERASEBKGND:
		return 0;
	case WM_KEYUP:
		this->OnKeyUp(wParam);
		return 0;
	case WM_KEYDOWN:
		this->OnKeyDown(wParam);
		return 0;
	default:
		return MainWindow::HandleMessage(hWnd, message, wParam, lParam);
	}
}

void MyWindow::OnDestroy()
{
	KillTimer(this->getHWnd(), 1);
	delete food;
	snake->snakeList.clear();
	delete snake;
	MainWindow::OnDestroy();
}

void MyWindow::OnResize(int width, int height)
{
	this->width = width;
	this->height = height;
	basex = this->width / 13;
	map_w = (this->width - basex * 2) / 32;
	map_h = (this->height - basey * 1) / 32;
}

VOID CALLBACK TimerProc(HWND hWnd, UINT message, UINT idEvent, DWORD lParam)
{
	static int timer = 1;
	timer++;
	if (timer % snake->rate == 0)
	{
		timer = 1;
		if (!snake->dead)
		{
			snake->Snake::move(map_w, map_h, *food);
		}
	}
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);
}

void MyWindow::OnCreate()
{
	RECT rect;
	GetClientRect(this->getHWnd(), &rect);
	this->width = rect.right - rect.left;
	this->height = rect.bottom - rect.top;

	srand((unsigned)time(NULL));
	basex = this->width / 13;
	map_w = (this->width - basex * 2) / 32;
	map_h = (this->height - basey * 1) / 32;

	food = new Node(rand() % (map_w - 2) + 1, rand() % (map_h - 2) + 1, FLAG_FOOD);
	snake = new Snake(1, 1, RIGHT, 25);

	SetTimer(this->getHWnd(), 1, 16, TimerProc);
}

HGLOBAL mLoadResource(HINSTANCE hins, LPCWSTR lpName, LPCWSTR lpType, IStream** ppIStream)
{
	// 读取资源包文件
	HRSRC hRsrc = FindResourceW(hins, lpName, lpType);
	//获取资源的大小
	DWORD dwSize = SizeofResource(hins, hRsrc);
	//加载资源
	HGLOBAL hResGlobal = LoadResource(hins, hRsrc);;
	HGLOBAL hGLOBALMEM = GlobalAlloc(GMEM_MOVEABLE, dwSize);
	memcpy(GlobalLock(hGLOBALMEM), LockResource(hResGlobal), dwSize);
	GlobalUnlock(hResGlobal);
	CreateStreamOnHGlobal(hGLOBALMEM, false, ppIStream);
	return hGLOBALMEM;
}

void DrawFood(HDC mdc, HINSTANCE hins)
{
	//Image image(L"res\\images\\food.png");
	IStream* pIStream;
	HGLOBAL hGLOBALMEM = mLoadResource(hins, MAKEINTRESOURCE(IDB_PNG_FOOD), L"PNG", &pIStream);
	std::unique_ptr<Image> image(Image::FromStream(pIStream));
	Graphics graphics(mdc);
	graphics.DrawImage(image.get(), basex + food->getX() * 32 - 1, basey + food->getY() * 32 - 1);
	pIStream->Release();
	GlobalUnlock(hGLOBALMEM);
	GlobalFree(hGLOBALMEM);
}

void DrawMap(HDC mdc, int w, int h, HINSTANCE hins)
{
	// graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	IStream* pIStream;
	HGLOBAL hGLOBALMEM = mLoadResource(hins, MAKEINTRESOURCE(IDR_JPG_TITLE), L"JPG", &pIStream);
	std::unique_ptr<Image> image(Image::FromStream(pIStream));
	int imageHeight = image->GetHeight();
	int imageWidth = image->GetWidth();
	Graphics graphics(mdc);
	graphics.DrawImage(image.get(), (w - imageWidth) / 2 + 80, 0);
	pIStream->Release();
	GlobalUnlock(hGLOBALMEM);
	GlobalFree(hGLOBALMEM);

	SolidBrush solidBrush(Color(255, 160, 32, 240));

	basey = imageHeight;

	for (int i = 0; i < map_h; i++)
	{
		for (int j = 0; j < map_w; j++)
		{
			if (i == 0 || j == 0 || i == map_h - 1 || j == map_w - 1)
			{
				graphics.FillRectangle(&solidBrush, basex + (j * 32), basey + (i * 32), 30, 30);
			}
		}
	}
	DrawFood(mdc, hins);
}

void DrawSnake(HDC mdc, int w, int h, HINSTANCE hins)
{
	Node headNode = snake->snakeList.front();
	Graphics graphics(mdc);
	IStream* pIStream;
	HGLOBAL hGLOBALMEM;
	switch (snake->dir)
	{
	case UP:
	{
		hGLOBALMEM = mLoadResource(hins, MAKEINTRESOURCE(IDB_PNG_UP), L"PNG", &pIStream);
		std::unique_ptr<Image> image(Image::FromStream(pIStream));
		graphics.DrawImage(image.get(), basex + headNode.getX() * 32 - 1, basey + headNode.getY() * 32 - 1);
		pIStream->Release();
		GlobalUnlock(hGLOBALMEM);
		GlobalFree(hGLOBALMEM);
		break;
	}
	case DOWN:
	{
		hGLOBALMEM = mLoadResource(hins, MAKEINTRESOURCE(IDB_PNG_DOWN), L"PNG", &pIStream);
		std::unique_ptr<Image> image(Image::FromStream(pIStream));
		graphics.DrawImage(image.get(), basex + headNode.getX() * 32 - 1, basey + headNode.getY() * 32 - 1);
		pIStream->Release();
		GlobalUnlock(hGLOBALMEM);
		GlobalFree(hGLOBALMEM);
		break;
	}
	case LEFT:
	{
		hGLOBALMEM = mLoadResource(hins, MAKEINTRESOURCE(IDB_PNG_LEFT), L"PNG", &pIStream);
		std::unique_ptr<Image> image(Image::FromStream(pIStream));
		graphics.DrawImage(image.get(), basex + headNode.getX() * 32 - 1, basey + headNode.getY() * 32 - 1);
		pIStream->Release();
		GlobalUnlock(hGLOBALMEM);
		GlobalFree(hGLOBALMEM);
		break;
	}
	case RIGHT:
	{
		hGLOBALMEM = mLoadResource(hins, MAKEINTRESOURCE(IDB_PNG_RIGHT), L"PNG", &pIStream);
		std::unique_ptr<Image> image(Image::FromStream(pIStream));
		graphics.DrawImage(image.get(), basex + headNode.getX() * 32 - 1, basey + headNode.getY() * 32 - 1);
		pIStream->Release();
		GlobalUnlock(hGLOBALMEM);
		GlobalFree(hGLOBALMEM);
		break;
	}
	}
	hGLOBALMEM = mLoadResource(hins, MAKEINTRESOURCE(IDB_PNG_BODY), L"PNG", &pIStream);
	std::unique_ptr<Image> image(Image::FromStream(pIStream));
	auto it = snake->snakeList.begin();
	++it;
	for (; it != snake->snakeList.end(); ++it)
	{
		graphics.DrawImage(image.get(), basex + it->getX() * 32 - 1, basey + it->getY() * 32 - 1);
	}
	pIStream->Release();
	GlobalUnlock(hGLOBALMEM);
	GlobalFree(hGLOBALMEM);
}

void DrawString(HDC mdc, int w, int h)
{
	Graphics graphics(mdc);
	FontFamily fontFamily(L"Times New Roman");
	Font font(&fontFamily, 20, FontStyleRegular, UnitPixel);

	SolidBrush brush(Color(255, 0, 0, 255));
	PointF pointF(w - 150.0f, basey - 40.0f);

	WCHAR buffer[15];
	wsprintfW(buffer, L"当前得分: %d", snake->score);
	graphics.DrawString(buffer, -1, &font, pointF, &brush);
}

void MyWindow::OnPaint(HDC hdc, PAINTSTRUCT ps)
{
	int w = ps.rcPaint.right - ps.rcPaint.left;
	int h = ps.rcPaint.bottom - ps.rcPaint.top;
	HDC mdc = CreateCompatibleDC(hdc);
	HBITMAP hbmp = CreateCompatibleBitmap(hdc, w, h);
	SelectObject(mdc, hbmp);

	DrawMap(mdc, this->width, this->height, this->getHInstance());
	DrawString(mdc, this->width, this->height);
	DrawSnake(mdc, this->width, this->height, this->getHInstance());

	BitBlt(hdc, 0, 0, w, h, mdc, 0, 0, SRCCOPY);
	DeleteObject(hbmp);
	DeleteDC(mdc);
}

void MyWindow::OnKeyUp(WPARAM keyCode)
{
}
void MyWindow::OnKeyDown(WPARAM keyCode)
{
	if (!snake->dead)
	switch (keyCode)
	{
	case 'w':
	case 'W':
	case VK_UP:
	{
		if (snake->dir != DOWN)
		{
			snake->dir = UP;
		}
		break;
	}
	case 's':
	case 'S':
	case VK_DOWN:
	{
		if (snake->dir != UP)
		{
			snake->dir = DOWN;
		}
		break;
	}

	case 'a':
	case 'A':
	case VK_LEFT:
	{
		if (snake->dir != RIGHT)
		{
			snake->dir = LEFT;
		}
		break;
	}
	case 'd':
	case 'D':
	case VK_RIGHT:
	{
		if (snake->dir != LEFT)
		{
			snake->dir = RIGHT;
		}
		break;
	}
	}
}

//graphics.DrawEllipse(&greenPen, nextPos->getX() * 22, nextPos->getY() * 22, 20, 20);
	//graphics.FillEllipse(&solidBrush, headPos->getX() * 22, headPos->getY() * 22, 20, 20);
	// graphics.FillRectangle(&solidBrush, Rect(0, 0, 20, 20));
	//Pen greenPen(Color(255, 0, 174, 239), 2);
	//SolidBrush solidBrush(Color(255, 0, 174, 239));

//Bitmap(位图)          CreateBitmap, CreateBitmapIndirect,
//CreateCompatibleBitmap, CreateDIBitmap,
//CreateDIBSection
//Brush(画刷)           CreateBrushIndirect, eateDIBPatternBrush,
//CreateDIBPatternBrushPt, CreateHatchBrush,
//CreatePatternBrush, CreateSolidBrush
//Font(字体)              CreateFont, CreateFontIndirect
//Pen(画笔)               CreatePen, CreatePenIndirect
//Region(区域)             CombineRgn, CreateEllipticRgn,
//CreateEllipticRgnIndirect,
//CreatePolygonRgn, CreateRectRgn,
//CreateRectRgnIndirect