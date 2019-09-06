# GDI+

微软官方API文档地址 https://docs.microsoft.com/zh-cn/windows/desktop/gdiplus/-gdiplus-gdi-start

## 入门

+ ### 画线

本主题演示如何使用GDI Plus绘制线条。

要在Windows GDI +中绘制一条线，您需要一个Graphics对象，一个Pen对象和一个Color对象。的图形对象提供的DrawLine方法方法和笔对象保持线的属性，例如颜色和宽度。Pen对象的地址作为参数传递给DrawLine方法方法。

以下程序从（0,0）到（200,100）绘制一条线，由三个函数组成：WinMain，WndProc和OnPaint。在WinMain函数和WndProc的功能提供了常见的大多数Windows应用程序的基本代码。WndProc函数中没有GDI +代码。所述的WinMain函数具有GDI +代码，即所需要的呼叫的少量GdiplusStartup和GdiplusShutdown。实际创建Graphics对象并绘制线条的GDI +代码位于OnPaint函数中。

所述的OnPaint函数接收设备句柄上下文并传递句柄图形构造函数。传递给Pen构造函数的参数是对Color对象的引用。传递给颜色构造函数的四个数字表示颜色的alpha，红色，绿色和蓝色分量。alpha分量决定了颜色的透明度; 0是完全透明的，255是完全不透明的。传递给DrawLine方法方法的四个数字表示该行的起点（0,0）和终点（200,100）。


```
#include <stdafx.h>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

VOID OnPaint(HDC hdc)
{
   Graphics graphics(hdc);
   Pen      pen(Color(255, 0, 0, 255));
   graphics.DrawLine(&pen, 0, 0, 200, 100);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
   HWND                hWnd;
   MSG                 msg;
   WNDCLASS            wndClass;
   GdiplusStartupInput gdiplusStartupInput;
   ULONG_PTR           gdiplusToken;
   
   // Initialize GDI+.
   GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
   
   wndClass.style          = CS_HREDRAW | CS_VREDRAW;
   wndClass.lpfnWndProc    = WndProc;
   wndClass.cbClsExtra     = 0;
   wndClass.cbWndExtra     = 0;
   wndClass.hInstance      = hInstance;
   wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
   wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
   wndClass.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
   wndClass.lpszMenuName   = NULL;
   wndClass.lpszClassName  = TEXT("GettingStarted");
   
   RegisterClass(&wndClass);
   
   hWnd = CreateWindow(
      TEXT("GettingStarted"),   // window class name
      TEXT("Getting Started"),  // window caption
      WS_OVERLAPPEDWINDOW,      // window style
      CW_USEDEFAULT,            // initial x position
      CW_USEDEFAULT,            // initial y position
      CW_USEDEFAULT,            // initial x size
      CW_USEDEFAULT,            // initial y size
      NULL,                     // parent window handle
      NULL,                     // window menu handle
      hInstance,                // program instance handle
      NULL);                    // creation parameters
      
   ShowWindow(hWnd, iCmdShow);
   UpdateWindow(hWnd);
   
   while(GetMessage(&msg, NULL, 0, 0))
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }
   
   GdiplusShutdown(gdiplusToken);
   return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, 
   WPARAM wParam, LPARAM lParam)
{
   HDC          hdc;
   PAINTSTRUCT  ps;
   
   switch(message)
   {
   case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      OnPaint(hdc);
      EndPaint(hWnd, &ps);
      return 0;
   case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
   default:
      return DefWindowProc(hWnd, message, wParam, lParam);
   }
} // WndProc
```

请注意WinMain函数中对GdiplusStartup的调用。GdiplusStartup函数的第一个参数是ULONG_PTR的地址。GdiplusStartup使用稍后传递给GdiplusShutdown函数的标记填充该变量。GdiplusStartup函数的第二个参数是GdiplusStartupInput结构的地址。前面的代码依赖于默认的GdiplusStartupInput构造函数来适当地设置结构成员。

+ ### 绘制一个字符串

“ 绘制线条 ”主题显示了如何编写使用Windows GDI +绘制线条的Windows应用程序。要绘制字符串，请使用以下OnPaint函数替换该主题中显示的OnPaint函数：

```
VOID OnPaint(HDC hdc)
{
   Graphics    graphics(hdc);
   SolidBrush  brush(Color(255, 0, 0, 255));
   FontFamily  fontFamily(L"Times New Roman");
   Font        font(&fontFamily, 24, FontStyleRegular, UnitPixel);
   PointF      pointF(10.0f, 20.0f);
   
   graphics.DrawString(L"Hello World!", -1, &font, pointF, &brush);
}
```

前面的代码创建了几个GDI +对象。的图形对象提供的DrawString方法的方法，其中实际的绘图。该SolidBrush对象指定字符串的颜色。

该的FontFamily构造函数接收标识字体系列单，字符串参数。FontFamily对象的地址是传递给Font构造函数的第一个参数。传递给Font构造函数的第二个参数指定字体大小，第三个参数指定样式。FontStyleRegular值是FontStyle枚举的成员，它在Gdiplusenums.h中声明。Font构造函数的最后一个参数表示字体的大小（在本例中为24）以像素为单位。UnitPixel的值是Unit枚举的成员。

传递给DrawString方法方法的第一个参数是宽字符串的地址。第二个参数-1指定字符串为空终止。（如果字符串不是以null结尾，则第二个参数应指定字符串中的宽字符数。）第三个参数是Font对象的地址。第四个参数是对PointF对象的引用，该对象指定将绘制字符串的位置。最后一个参数是Brush对象的地址，它指定字符串的颜色。


## 用笔绘制线条和形状

+ ### 使用笔绘制线条和矩形

要绘制直线和矩形，需要Graphics对象和Pen对象。的图形对象提供的DrawLine方法，并且笔的线的对象存储特征，例如颜色和宽度。

以下示例从（20,10）到（300,100）绘制一条线。假设图形是现有的Graphics对象。

```
Pen pen(Color(255, 0, 0, 0));
graphics.DrawLine(&pen, 20, 10, 300, 100);
```

第一个代码语句使用Pen类构造函数创建黑色笔。传递给Pen构造函数的一个参数是Color对象。用于构造Color对象的值- （255,0,0,0） - 对应于颜色的alpha，red，green和blue组件。这些值定义了不透明的黑色笔。

以下示例绘制一个矩形，其左上角位于（10,10）。矩形的宽度为100，高度为50.传递给Pen构造函数的第二个参数表示笔的宽度为5像素。

```
Pen blackPen(Color(255, 0, 0, 0), 5);
stat = graphics.DrawRectangle(&blackPen, 10, 10, 100, 50);
```

绘制矩形时，笔位于矩形边界的中心。因为笔宽为5，所以矩形的边被绘制为5个像素宽，使得在边界上绘制1个像素，在内部绘制2个像素，在外部绘制2个像素。有关笔对齐的更多详细信息，请参阅设置笔宽和对齐。

下图显示了生成的矩形。虚线表示如果笔宽为一个像素，则绘制矩形的位置。矩形左上角的放大视图显示粗黑线以这些虚线为中心。

+ ### 设置笔宽度和对齐方式

创建Pen对象时，可以将笔宽作为构造函数的参数之一提供。您还可以使用Pen :: SetWidth方法更改笔的宽度。

理论线的宽度为零。绘制线条时，像素位于理论线的中心。下面的示例绘制两次指定的行：一次使用宽度为1的黑色笔，一次使用宽度为10的绿色笔。

```
Pen blackPen(Color(255, 0, 0, 0), 1);
Pen greenPen(Color(255, 0, 255, 0), 10);
stat = greenPen.SetAlignment(PenAlignmentCenter);

// Draw the line with the wide green pen.
stat = graphics.DrawLine(&greenPen, 10, 100, 100, 50);

// Draw the same line with the thin black pen.
stat = graphics.DrawLine(&blackPen, 10, 100, 100, 50);
```

下面的示例绘制两次指定的矩形：一次使用宽度为1的黑色笔，一次使用宽度为10的绿色笔。代码将值PenAlignmentCenter（PenAlignment枚举的一个元素）传递给Pen :: SetAlignment方法以指定用绿色笔绘制的像素位于矩形边界的中心。

```
Pen blackPen(Color(255, 0, 0, 0), 1);
Pen greenPen(Color(255, 0, 255, 0), 10);
stat = greenPen.SetAlignment(PenAlignmentCenter);

// Draw the rectangle with the wide green pen.
stat = graphics.DrawRectangle(&greenPen, 10, 100, 50, 50);

// Draw the same rectangle with the thin black pen.
stat = graphics.DrawRectangle(&blackPen, 10, 100, 50, 50);
```

您可以通过修改前面示例中的第三个语句来更改绿色笔的对齐方式，如下所示：

```
stat = greenPen.SetAlignment(PenAlignmentInset);
```

+ ### 用线帽画一条线

您可以使用称为线帽的几种形状之一绘制线的起点或终点。Windows GDI +支持多种线路上限，例如圆形，方形，菱形和箭头。

您可以为行的开头（开始上限），行的结尾（结束上限）或虚线的短划线（短划线上限）指定行上限。

以下示例绘制一条线，一端带箭头，另一端带圆帽：

```
Pen pen(Color(255, 0, 0, 255), 8);
stat = pen.SetStartCap(LineCapArrowAnchor);
stat = pen.SetEndCap(LineCapRoundAnchor);
stat = graphics.DrawLine(&pen, 20, 175, 300, 175);
```

LineCapArrowAnchor和LineCapRoundAnchor是LineCap枚举的元素。

+ ### 加入线

线连接是由两条线相交或重叠形成的公共区域。Windows GDI +提供了四种线连接样式：斜接，斜角，圆形和斜接修剪。线连接样式是Pen类的属性。为笔指定线连接样式然后使用该笔绘制路径时，指定的连接样式将应用于路径中的所有连接线。

您可以使用Pen类的Pen :: SetLineJoin方法指定行连接样式。以下示例演示了水平线和垂直线之间的斜面线连接：

```
GraphicsPath path;
Pen penJoin(Color(255, 0, 0, 255), 8);

path.StartFigure();
path.AddLine(Point(50, 200), Point(100, 200));
path.AddLine(Point(100, 200), Point(100, 250));

penJoin.SetLineJoin(LineJoinBevel);
graphics.DrawPath(&penJoin, &path);
```

在前面的示例中，传递给Pen :: SetLineJoin方法的值（LineJoinBevel）是LineJoin枚举的元素。

+ ### 绘制自定义虚线

Windows GDI +提供了DashStyle枚举中列出的几种破折号样式。如果这些标准的破折号样式不符合您的需求，您可以创建自定义破折号模式。

要绘制自定义虚线，请将短划线和空格的长度放在数组中，并将数组的地址作为参数传递给Pen对象的Pen :: SetDashPattern方法。以下示例基于数组{5,2,15,4}绘制自定义虚线。如果将数组的元素乘以笔宽5，则得到{25,10,75,20}。显示的短划线在25到75之间交替变换，并且空间在10到20之间交替变换。

```
REAL dashValues[4] = {5, 2, 15, 4};
Pen blackPen(Color(255, 0, 0, 0), 5);
blackPen.SetDashPattern(dashValues, 4);
stat = graphics.DrawLine(&blackPen, Point(5, 5), Point(405, 5));
```
请注意，最后一个短划线必须短于25个单位，以便该行可以在（405,5）处结束。

+ ### 绘制一条充满纹理的线条

您可以使用纹理绘制，而不是使用纯色绘制线条或曲线。要使用纹理绘制线条和曲线，请创建TextureBrush对象，并将该TextureBrush对象的地址传递给Pen构造函数。与纹理画笔相关联的图像用于平铺平面（不可见），并且当笔绘制线条或曲线时，笔的笔划揭示平铺纹理的某些像素。

以下示例从Texture1.jpg文件创建一个Image对象。该图像用于构造TextureBrush对象，TextureBrush对象用于构造Pen对象。对Graphics :: DrawImage的调用绘制图像的左上角为（0,0）。对Graphics :: DrawEllipse的调用使用Pen对象绘制纹理椭圆。

```
Image         image(L"Texture1.jpg");
TextureBrush  tBrush(&image);
Pen           texturedPen(&tBrush, 30);

graphics.DrawImage(&image, 0, 0, image.GetWidth(), image.GetHeight());
graphics.DrawEllipse(&texturedPen, 100, 20, 200, 100);
```

## 使用画笔填充形状

Windows GDI + Brush对象用于填充闭合形状的内部。GDI +定义了几种填充样式：纯色，阴影图案，图像纹理和颜色渐变。

以下主题更详细地介绍了画笔的使用：

+   
    + 用纯色填充形状
    + 用填充图案填充形状
    + 用图像纹理填充形状
    + 用图像平铺形状
    + 用颜色渐变填充形状



+ ### 用纯色填充形状

若要使用纯色填充形状，请创建一个SolidBrush对象，然后将该SolidBrush对象的地址作为参数传递给Graphics类的某个填充方法。以下示例显示如何使用红色填充椭圆：

```
SolidBrush solidBrush(Color(255, 255, 0, 0));
stat = graphics.FillEllipse(&solidBrush, 0, 0, 100, 60);
```
在前面的示例中，SolidBrush构造函数将Color对象引用作为其唯一参数。Color构造函数使用的值表示颜色的alpha，red，green和blue组件。这些值中的每一个必须在0到255的范围内。前255个表示颜色完全不透明，第二个255表示红色成分处于全强度。两个零表示绿色和蓝色分量的强度均为0。

传递给Graphics :: FillEllipse方法的四个数字（0,0,100,60）指定椭圆的边界矩形的位置和大小。矩形的左上角为（0,0），宽度为100，高度为60。

+ ### 用填充图案填充形状

填充图案由两种颜色组成：一种用于背景，另一种用于在背景上形成图案的线条。要使用填充图案填充封闭形状，请使用HatchBrush对象。以下示例演示如何使用填充图案填充椭圆：

```
HatchBrush hBrush(HatchStyleHorizontal, Color(255, 255, 0, 0),
   Color(255, 128, 255, 255));
stat = graphics.FillEllipse(&hBrush, 0, 0, 100, 60);
```

该HatchBrush构造函数有三个参数：舱口风格，斑马线的颜色和背景的颜色。填充样式参数可以是HatchStyle枚举的任何元素。HatchStyle枚举中有五十多个元素; 其中一些元素显示在以下列表中：

*   HatchStyleHorizontal
    + HatchStyleVertical
    + HatchStyleForwardDiagonal
    + HatchStyleBackwardDiagonal
    + HatchStyleCross
    * HatchStyleDiagonalCross

+ ### 用图像纹理填充形状

您可以使用Image类和TextureBrush类使用纹理填充闭合的形状。

以下示例使用图像填充椭圆。该代码构造一个Image对象，然后将该Image对象的地址作为参数传递给TextureBrush构造函数。第三个代码语句缩放图像，第四个语句用缩放图像的重复副本填充椭圆：

```
Image image(L"ImageFile.jpg");
TextureBrush tBrush(&image);
stat = tBrush.SetTransform(&Matrix(75.0/640.0, 0.0f, 0.0f,
   75.0/480.0, 0.0f, 0.0f));
stat = graphics.FillEllipse(&tBrush,Rect(0, 150, 150, 250));
```
在前面的代码示例中，TextureBrush :: SetTransform方法设置在绘制图像之前应用于图像的变换。假设原始图像具有640像素的宽度和480像素的高度。通过设置水平和垂直缩放值，变换将图像缩小到75×75。

    备注

    在前面的示例中，图像大小为75×75，椭圆大小为150×250。因为图像小于它填充的椭圆，所以椭圆与图像平铺。平铺
    意味着水平和垂直重复图像，直到达到形状的边界。有关平铺的更多信息，请参见平铺带有图像的形状。


+ ### 用图像平铺形状

就像瓷砖可以彼此相邻放置以覆盖地板一样，矩形图像可以彼此相邻放置以填充（平铺）形状。要平铺形状的内部，请使用纹理画笔。构造TextureBrush对象时，传递给构造函数的其中一个参数是Image对象的地址。当您使用纹理画笔绘制形状的内部时，该形状将填充此图像的重复副本。

TextureBrush对象的wrap模式属性确定图像在矩形网格中重复时的方向。您可以使网格中的所有切片具有相同的方向，或者可以使图像从一个网格位置翻转到下一个网格位置。翻转可以是水平，垂直或两者。以下示例演示了使用不同类型的翻转进行平铺。

  + 平铺图像

    ```
    Image image(L"HouseAndTree.png");
    TextureBrush tBrush(&image);
    Pen blackPen(Color(255, 0, 0, 0));
    stat = graphics.FillRectangle(&tBrush, Rect(0, 0, 200, 200));
    stat = graphics.DrawRectangle(&blackPen, Rect(0, 0, 200, 200));
    ```

    + 平铺时水平翻转图像

        此示例使用75×75图像填充200×200矩形。换行模式设置为水平翻转图像。

        ```
        Image image(L"HouseAndTree.png");
        TextureBrush tBrush(&image);
        Pen blackPen(Color(255, 0, 0, 0));
        stat = tBrush.SetWrapMode(WrapModeTileFlipX);
        stat = graphics.FillRectangle(&tBrush, Rect(0, 0, 200, 200));
        stat = graphics.DrawRectangle(&blackPen, Rect(0, 0, 200, 200));
        ```

    + 平铺时垂直翻转图像

        此示例使用75×75图像填充200×200矩形。环绕模式设置为垂直翻转图像。

        ```
        Image image(L"HouseAndTree.png");
        TextureBrush tBrush(&image);
        Pen blackPen(Color(255, 0, 0, 0));
        stat = tBrush.SetWrapMode(WrapModeTileFlipY);
        stat = graphics.FillRectangle(&tBrush, Rect(0, 0, 200, 200));
        stat = graphics.DrawRectangle(&blackPen, Rect(0, 0, 200, 200));
        ```

    + 平铺时水平和垂直翻转图像

        此示例使用75×75图像平铺200×200矩形。换行模式设置为水平和垂直翻转图像。

        ```
        Image image(L"HouseAndTree.png");
        TextureBrush tBrush(&image);
        Pen blackPen(Color(255, 0, 0, 0));
        stat = tBrush.SetWrapMode(WrapModeTileFlipXY);
        stat = graphics.FillRectangle(&tBrush, Rect(0, 0, 200, 200));
        stat = graphics.DrawRectangle(&blackPen, Rect(0, 0, 200, 200));
        ```

    + ### 用颜色渐变填充形状

        有关渐变画笔的详细信息，请参阅使用渐变画笔填充形状。 
        https://docs.microsoft.com/zh-cn/windows/desktop/gdiplus/-gdiplus-filling-shapes-with-a-gradient-brush-use


## 使用图像，位图和图元文件

Windows GDI +提供了用于处理光栅图像（位图）和矢量图像（元文件）的Image类。该位图类和图元文件类无论是从继承的图像类。该位图上的功能扩展类的图像通过提供额外的方法用于加载，存储，和处理的光栅图像类。在图元文件上的功能扩展类的图像通过提供一种用于记录附加方法和检查矢量图像类。

* ### 加载和显示位图

要在屏幕上显示光栅图像（位图），您需要一个Image对象和一个Graphics对象。将文件名（或指向流的指针）传递给Image构造函数。创建Image对象后，将该Image对象的地址传递给Graphics对象的DrawImage方法。

下面的示例从JPEG文件创建一个Image对象，然后在左上角绘制图像（60,10）：

```
Image image(L"Grapes.jpg");
graphics.DrawImage(&image, 60, 10);
```

的图片类提供用于加载和显示光栅图像和矢量图像的基本方法。的位图类，它从继承图片类，提供了更多的专门的方法用于装载，显示和操纵光栅图像。例如，您可以从图标句柄（HICON）构造一个Bitmap对象。

以下示例获取图标的句柄，然后使用该句柄构造Bitmap对象。代码通过将Bitmap对象的地址传递给Graphics对象的DrawImage方法来显示图标。

```
HICON hIcon = LoadIcon(NULL, IDI_APPLICATION);
Bitmap bitmap(hIcon);
graphics.DrawImage(&bitmap, 10, 10);
```

* ### 加载和显示图元文件

的图片类提供用于加载和显示光栅图像和矢量图像的基本方法。在图元文件类，它从继承图片类，提供了一种用于记录，显示和检查矢量图像更专门的方法。

要在屏幕上显示矢量图像（图元文件），您需要一个Image对象和一个Graphics对象。将文件名（或指向流的指针）传递给Image构造函数。创建Image对象后，将该Image对象的地址传递给Graphics对象的DrawImage方法。

下面的示例从EMF（增强型图元文件）文件创建一个Image对象，然后在左上角绘制图像（60,10）：
```
Image image(L"SampleMetafile.emf");
graphics.DrawImage(&image, 60, 10);
```

* ### 将BMP图像转换为PNG图像

要将图像保存到磁盘文件，请调用Image类的Save方法。以下控制台应用程序从磁盘文件加载BMP图像，将图像转换为PNG格式，并将转换后的图像保存到新磁盘文件。main函数依赖于辅助函数GetEncoderClsid，它在检索编码器的类标识符时显示。

```
#include <windows.h>
#include <gdiplus.h>
#include <stdio.h>
using namespace Gdiplus;

INT GetEncoderClsid(const WCHAR* format, CLSID* pClsid);  // helper function

INT main()
{
   // Initialize GDI+.
   GdiplusStartupInput gdiplusStartupInput;
   ULONG_PTR gdiplusToken;
   GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

   CLSID   encoderClsid;
   Status  stat;
   Image*   image = new Image(L"Bird.bmp");

   // Get the CLSID of the PNG encoder.
   GetEncoderClsid(L"image/png", &encoderClsid);

   stat = image->Save(L"Bird.png", &encoderClsid, NULL);

   if(stat == Ok)
      printf("Bird.png was saved successfully\n");
   else
      printf("Failure: stat = %d\n", stat); 

   delete image;
   GdiplusShutdown(gdiplusToken);
   return 0;
}
```