#ifndef ___META_H___
#define ___META_H___

#include <windows.h>
#include "resource.h"

#include <memory>
#include <time.h>

//#include <stdlib.h>
//#include <malloc.h>
//#include <tchar.h>

#ifndef ULONG_PTR
#define ULONG_PTR unsigned long*
#include <GdiPlus.h>
#include <GdiPlusBrush.h>
using namespace Gdiplus;
#pragma comment(lib, "GdiPlus.lib")
#endif

#endif // ___META_H___
