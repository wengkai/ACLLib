#define _CRT_SECURE_NO_WARNINGS

#include "acllib.h"

#include <math.h>

#include <mmsystem.h>

#include <olectl.h>

#include <stdio.h>

#include <Digitalv.h>

#include <assert.h>



#pragma comment(lib,"winmm.lib")

#pragma comment(lib,"msimg32.lib")



#ifdef _DEBUG

#define ACL_ASSERT(_Expression,errStr) (void)( (!!(_Expression)) || (acl_error(errStr),0) )

#else

#define ACL_ASSERT(flag,errStr) ((void)0)

#endif



#define ACL_ASSERT_HWND ACL_ASSERT(g_hWnd!=0, \
	_T("You should call function \"initWindow(...)\" befor use function \"") _T(__FUNCTION__) _T("\""))

#define ACL_ASSERT_BEGIN_PAINT ACL_ASSERT(g_hmemdc!=0, \
	_T("You should call function \"beginPaint()\" befor use function \"") _T(__FUNCTION__) _T("\""))



#if defined(_UNICODE) || defined(UNICODE)

#define itos _itow

#else

#define itos _itoa

#endif



	int Main(void);



const TCHAR g_wndClassName[] = TEXT ("ACL_WND_CLASS");

const TCHAR g_libName[] = _T("ACLLIB");



struct ACL_Window_Data{

	HWND hwnd;

	KeyboardEventCallback g_keyboard;

	MouseEventCallback g_mouse;

	TimerEventCallback g_timer;

} ACL_Windows[MAX_WINDOW_COUNT]={0,};



HWND g_hWnd = NULL;

HDC g_hmemdc = NULL;

HBITMAP g_hbitmap = NULL;



HPEN g_pen = NULL;

ACL_Color g_penColor = BLACK;

int g_penWidth = 1;

ACL_Pen_Style g_penStyle = SOLID_PEN;



HBRUSH g_brush = NULL;

ACL_Color g_brushColor = BLACK;

ACL_Brush_Style g_brushStyle = SOLID_BRUSH;



HFONT g_font = NULL;

TCHAR g_fontName[256] = _T("ËÎÌו");

int g_textSize = 12;

ACL_Color g_textColor = BLACK;

ACL_Color g_textBkColor = WHITE;



int g_soundID = 0;



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

ACL_Window mmPickByHwnd(HWND hwnd);



int acl_error(TCHAR *errStr)

{

	//

	MessageBox(g_hWnd,errStr,g_libName,MB_ICONERROR);

	abort();

	return 0;

}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)

{

	MSG          msg;

	WNDCLASS     wndclass;



	wndclass.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	wndclass.lpfnWndProc   = WndProc;

	wndclass.cbClsExtra    = 0;

	wndclass.cbWndExtra    = 0;

	wndclass.hInstance     = hInstance;

	wndclass.hInstance     = hInstance;

	wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION);

	wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW);

	wndclass.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);

	wndclass.lpszMenuName  = NULL;

	wndclass.lpszClassName = g_wndClassName;



	if (!RegisterClass(&wndclass))

	{

		MessageBox(NULL, TEXT ("This program requires Windows NT!"), g_libName, MB_ICONERROR);

		return 0;

	}



	Main();



	ACL_ASSERT(g_hWnd,_T("Did you call \"initWindow(...)\" in Main() ?"));



	while (GetMessage(&msg, NULL, 0, 0))

	{

		TranslateMessage (&msg);

		DispatchMessage (&msg);

	}

	return msg.wParam;

}



LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)

{ 

	ACL_Window mmWindow = mmPickByHwnd(hwnd);



	switch (message) 

	{

	case WM_CREATE:

		{

			HDC hdc;

			hdc = GetDC(hwnd);

			g_hbitmap = CreateCompatibleBitmap(

				hdc, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

			g_hmemdc = CreateCompatibleDC(hdc);

			SelectObject(g_hmemdc, g_hbitmap);

			BitBlt(g_hmemdc, 

				0, 0, 

				GetSystemMetrics(SM_CXSCREEN),

				GetSystemMetrics(SM_CYSCREEN), 

				g_hmemdc, 

				0, 0, 

				WHITENESS);

			DeleteDC(g_hmemdc);

			ReleaseDC(g_hWnd, hdc);

			break;

		}

	case WM_ERASEBKGND:

		break;

	case WM_PAINT:

		{

			HDC hdc;

			PAINTSTRUCT ps;

			RECT rect;

			hdc = BeginPaint(hwnd, &ps);

			g_hmemdc = CreateCompatibleDC(hdc);

			SelectObject(g_hmemdc, g_hbitmap);

			GetClientRect(hwnd,&rect);

			BitBlt(hdc, 0, 0, rect.right - rect.left,

				rect.bottom - rect.top, g_hmemdc, 0, 0, SRCCOPY);

			DeleteDC(g_hmemdc);

			g_hmemdc = 0;

			EndPaint(hwnd,&ps);

			break;

		}

	case WM_CHAR:

		break;



	case WM_KEYDOWN:

		if (mmWindow->g_keyboard != NULL)

			mmWindow->g_keyboard((int) wParam,KEY_DOWN);

		break;



	case WM_KEYUP:

		if(mmWindow->g_keyboard != NULL)

			mmWindow->g_keyboard((int) wParam,KEY_UP);

		break;



	case WM_LBUTTONDOWN:

		if (mmWindow->g_mouse != NULL)

			mmWindow->g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), LEFT_BUTTON, BUTTON_DOWN);

		break;



	case WM_LBUTTONUP:

		if (mmWindow->g_mouse != NULL)

			mmWindow->g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), LEFT_BUTTON, BUTTON_UP);

		break;



	case WM_LBUTTONDBLCLK:

		if (mmWindow->g_mouse != NULL)

			mmWindow->g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), LEFT_BUTTON, BUTTON_DOUBLECLICK);

		break;



	case WM_MBUTTONDOWN:

		if (mmWindow->g_mouse != NULL)

			mmWindow->g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), MIDDLE_BUTTON, BUTTON_DOWN);

		break;



	case WM_MBUTTONUP:

		if (mmWindow->g_mouse != NULL)

			mmWindow->g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), MIDDLE_BUTTON, BUTTON_UP);

		break;



	case WM_MBUTTONDBLCLK:

		if (mmWindow->g_mouse != NULL)

			mmWindow->g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), MIDDLE_BUTTON, BUTTON_DOUBLECLICK);

		break;



	case WM_RBUTTONDOWN:

		if (mmWindow->g_mouse != NULL)

			mmWindow->g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), RIGHT_BUTTON, BUTTON_DOWN);

		break;



	case WM_RBUTTONUP:

		if (mmWindow->g_mouse != NULL)

			mmWindow->g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), RIGHT_BUTTON, BUTTON_UP);

		break;



	case WM_RBUTTONDBLCLK:

		if (mmWindow->g_mouse != NULL)

			mmWindow->g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), RIGHT_BUTTON, BUTTON_DOUBLECLICK);

		break;



	case WM_MOUSEMOVE:

		if(mmWindow->g_mouse != NULL)

			mmWindow->g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), MOUSEMOVE, -1);

		break;



	case WM_MOUSEWHEEL:

		if(mmWindow->g_mouse == NULL)

			break;

		if(HIWORD(wParam) == 120)

			mmWindow->g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam),MIDDLE_BUTTON,ROLL_UP);

		else if(HIWORD(wParam)==65416)

			mmWindow->g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam),MIDDLE_BUTTON,ROLL_DOWN);

		break;



	case WM_TIMER:

		if (mmWindow->g_timer != NULL)

			mmWindow->g_timer(wParam);

		break;



	case WM_DESTROY:

		if(ACL_Windows == mmWindow) PostQuitMessage(0);

		break;

	default:

		return DefWindowProc(hwnd, message, wParam, lParam);

	}

	return 0;

}



ACL_Window initWindow(const TCHAR *wndName, int x, int y, int width, int height)

{

	RECT rect;

	ACL_Window ret = mmPickByHwnd( NULL );

	assert(ret);



	g_hWnd = CreateWindow (

		g_wndClassName, wndName,

		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX,

		x, y, 

		width, height,

		NULL, NULL, 0, NULL) ;

	if(!g_hWnd)

	{

		MessageBox(NULL,_T("Fail to create window"),g_libName,MB_ICONERROR);

		abort();

	}

	GetClientRect(g_hWnd,&rect);

	width += width - (rect.right-rect.left);

	height += height - (rect.bottom-rect.top);

	SetWindowPos(g_hWnd,HWND_TOP,0,0,width,height,SWP_NOMOVE);



	ShowWindow (g_hWnd,1);

	UpdateWindow (g_hWnd);



	ret->hwnd=g_hWnd;

	return ret;

}



ACL_Window selectWindow(ACL_Window targetWindow)

{

	ACL_Window previousWindow = mmPickByHwnd( g_hWnd );



	g_hWnd = targetWindow->hwnd;



	return previousWindow;

}



void updatePen();

void updateBrush();

void updateFont();



void beginPaint()

{

	HDC hdc;



	ACL_ASSERT_HWND;



	hdc = GetDC(g_hWnd);

	g_hmemdc = CreateCompatibleDC(hdc);

	SelectObject(g_hmemdc,g_hbitmap);



	updatePen();

	updateBrush();

	updateFont();

	setTextColor(g_textColor);

	setTextBkColor(g_textBkColor);

}



void endPaint()

{

	DeleteDC(g_hmemdc);	

	g_hmemdc = 0;

	InvalidateRect(g_hWnd,0,0);



	DeleteObject(g_pen);

	DeleteObject(g_brush);

	DeleteObject(g_font);

	g_pen = NULL;

	g_brush = NULL;

	g_font = NULL;

}



void clearDevice(void)

{

	ACL_ASSERT_BEGIN_PAINT;

	BitBlt(

		g_hmemdc, 

		0, 0, 

		GetSystemMetrics(SM_CXSCREEN), 

		GetSystemMetrics(SM_CYSCREEN) , 

		g_hmemdc, 

		0, 0,

		WHITENESS);	

}



void updatePen()

{

	if(g_pen)DeleteObject(g_pen);

	if(g_penColor==EMPTY)

		g_pen = (HPEN)GetStockObject(NULL_PEN);

	else

		g_pen = CreatePen(g_penStyle,g_penWidth,g_penColor);

	SelectObject(g_hmemdc,g_pen);

}



void updateBrush()

{

	if(g_brush)DeleteObject(g_brush);

	if(g_brushColor==EMPTY)

	{

		g_brush = (HBRUSH)GetStockObject(NULL_BRUSH);

	}

	else

	{

		if(g_brushStyle==-1)

			g_brush = CreateSolidBrush(g_brushColor);	

		else

			g_brush = CreateHatchBrush(g_brushStyle,g_brushColor);

	}

	SelectObject(g_hmemdc,g_brush);

}



void updateFont()

{

	if(g_font)DeleteObject(g_font);

	g_font = CreateFont(

		g_textSize,

		0,

		0,0,700,0,0,0,0,0,0,0,0,g_fontName);

	SelectObject(g_hmemdc,g_font);

}



void setPenColor(ACL_Color newColor)

{

	ACL_ASSERT_BEGIN_PAINT;

	g_penColor = newColor;    

	updatePen();

}



void setPenWidth(int width)

{

	ACL_ASSERT_BEGIN_PAINT;

	g_penWidth = width;

	updatePen();

}



void setPenStyle(ACL_Pen_Style newStyle)

{

	ACL_ASSERT_BEGIN_PAINT;

	g_penStyle = newStyle;

	updatePen();

}



void setBrushColor(ACL_Color newColor)

{

	ACL_ASSERT_BEGIN_PAINT;

	g_brushColor = newColor;

	updateBrush();

}



void setBrushStyle(ACL_Brush_Style newStyle)

{

	ACL_ASSERT_BEGIN_PAINT;

	g_brushStyle = newStyle;

	updateBrush();

}



void setTextColor(ACL_Color color)

{

	ACL_ASSERT_BEGIN_PAINT;

	ACL_ASSERT(color!=EMPTY,_T("text color can not be EMPTY"));

	g_textColor = color;

	SetTextColor(g_hmemdc,color);

}



void setTextBkColor(ACL_Color color)

{

	ACL_ASSERT_BEGIN_PAINT;

	g_textBkColor = color;

	if(color == EMPTY)

		SetBkMode(g_hmemdc,TRANSPARENT);

	else

	{

		SetBkMode(g_hmemdc,OPAQUE);

		SetBkColor(g_hmemdc,color);

	}	

}



void setTextSize(int size)

{

	ACL_ASSERT_BEGIN_PAINT;

	g_textSize = size;

	updateFont();

}



void setTextFont(TCHAR *pfn)

{

	size_t len;

	ACL_ASSERT_BEGIN_PAINT;

	len = _tcslen(pfn);

	_tcsncpy(g_fontName,pfn,len);

	updateFont();

}



void paintText(int x, int y, const TCHAR *textstring)

{	

	ACL_ASSERT_BEGIN_PAINT;

	TextOut(g_hmemdc, x, y, textstring, lstrlen(textstring));

}



void putpixel(int x, int y, ACL_Color color)

{

	ACL_ASSERT_BEGIN_PAINT;

	SetPixel(g_hmemdc, x, y, color);	

}



ACL_Color getpixel(int x, int y)

{

	ACL_ASSERT_BEGIN_PAINT;

	return GetPixel(g_hmemdc, x, y);

}



int getWidth(void)

{

	RECT rect;

	GetClientRect(g_hWnd, &rect);

	return rect.right;

}



int getHeight(void)

{

	RECT rect;

	GetClientRect(g_hWnd, &rect);

	return rect.bottom;

}



int getX(void)

{

	POINT point;

	ACL_ASSERT_BEGIN_PAINT;

	GetCurrentPositionEx(g_hmemdc, &point);

	return (int) point.x;

}



int getY(void)

{

	POINT point;

	ACL_ASSERT_BEGIN_PAINT;

	GetCurrentPositionEx(g_hmemdc, &point);

	return (int) point.y;

}



void moveTo(int x, int y)

{

	ACL_ASSERT_BEGIN_PAINT;

	MoveToEx(g_hmemdc, x, y,NULL);

}



void moveRel(int dx, int dy)

{

	POINT point;	

	ACL_ASSERT_BEGIN_PAINT;

	GetCurrentPositionEx(g_hmemdc, &point);

	MoveToEx(g_hmemdc, (int) point.x + dx, (int) point.y + dy,NULL);

}



void line(int x0, int y0, int x1, int y1)

{

	POINT point;	

	ACL_ASSERT_BEGIN_PAINT;

	GetCurrentPositionEx(g_hmemdc, &point);

	MoveToEx(g_hmemdc, x0, y0, NULL);

	LineTo(g_hmemdc, x1, y1);

	MoveToEx(g_hmemdc, (int) point.x, (int) point.y, NULL);

	LineTo(g_hmemdc, x1, y1);	

	MoveToEx(g_hmemdc,point.x,point.y,NULL);

}



void lineTo(int x, int y)

{

	ACL_ASSERT_BEGIN_PAINT;

	LineTo(g_hmemdc, x, y);

}



void lineRel(int dx, int dy)

{

	POINT point;

	ACL_ASSERT_BEGIN_PAINT;

	GetCurrentPositionEx(g_hmemdc, &point);

	LineTo(g_hmemdc, (int) point.x + dx, (int) point.y + dy);

	MoveToEx(g_hmemdc,point.x,point.y,NULL);

}



void arc(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)

{

	ACL_ASSERT_BEGIN_PAINT;

	Arc(g_hmemdc,x1,y1,x2,y2,x3,y3,x4,y4);

}



void rectangle(int left,int top,int right,int bottom)

{

	ACL_ASSERT_BEGIN_PAINT;

	Rectangle(g_hmemdc,left,top,right,bottom);

}



void roundrect(int left,int top,int right,int bottom,int width,int height)

{

	ACL_ASSERT_BEGIN_PAINT;

	RoundRect(g_hmemdc,left,top,right,bottom,width,height);

}



void ellipse(int left,int top,int right, int bottom)

{

	ACL_ASSERT_BEGIN_PAINT;

	Ellipse(g_hmemdc,left,top,right,bottom);

}



void pie(int left, int top, int right, int bottom, int xr1, int yr1, int xr2, int yr2)

{

	ACL_ASSERT_BEGIN_PAINT;

	Pie(g_hmemdc,left,top,right,bottom,xr1,yr1,xr2,yr2);

}



void chrod(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)

{

	ACL_ASSERT_BEGIN_PAINT;

	Chord(g_hmemdc,x1, y1, x2, y2, x3, y3, x4, y4);

}



void polygon(POINT *apt,int cpt)

{

	ACL_ASSERT_BEGIN_PAINT;

	Polygon(g_hmemdc,apt,cpt);

}



void polyline(POINT *apt,int cpt)

{

	ACL_ASSERT_BEGIN_PAINT;

	Polyline(g_hmemdc,apt,cpt);

}



void putImage(ACL_Image *pImage, int x, int y)

{

	HDC hbitmapdc;

	ACL_ASSERT_BEGIN_PAINT;

	hbitmapdc = CreateCompatibleDC(g_hmemdc);

	SelectObject(hbitmapdc, pImage->hbitmap);

	BitBlt(g_hmemdc, x, y, pImage->width, pImage->height, hbitmapdc,0,0,SRCCOPY);

	DeleteDC(hbitmapdc);

}



void putImageScale(ACL_Image *pImage,int x,int y,int width,int height)

{

	HDC hbitmapdc;

	ACL_ASSERT_BEGIN_PAINT;

	hbitmapdc = CreateCompatibleDC(g_hmemdc);

	SelectObject(hbitmapdc, pImage->hbitmap);

	if(width == -1)width = pImage->width;

	if(height == -1)height = pImage->height;

	StretchBlt( g_hmemdc,x,y,width,height,hbitmapdc,0,0,pImage->width,pImage->height,SRCCOPY);

	DeleteDC(hbitmapdc);

}



void putImageTransparent(ACL_Image *pImage,int x,int y,int width,int height, ACL_Color bkColor)

{

	HDC hbitmapdc;

	ACL_ASSERT_BEGIN_PAINT;

	hbitmapdc = CreateCompatibleDC(g_hmemdc);

	SelectObject(hbitmapdc, pImage->hbitmap);

	if(width == -1)width = pImage->width;

	if(height == -1)height = pImage->height;

	TransparentBlt(g_hmemdc,x,y,width,height,hbitmapdc,0,0,pImage->width,pImage->height,bkColor);

	DeleteDC(hbitmapdc);

}



void loadImage(const TCHAR *image, ACL_Image *mapbuf)

{

	HDC hmapdc;

	// TODO : check file format ?

	IPicture *ipicture;

	IStream *istream;

	DWORD filesize = 0, bytes;

	OLE_XSIZE_HIMETRIC width;

	OLE_YSIZE_HIMETRIC height;

	HANDLE file = NULL;

	HGLOBAL global = NULL;

	LPVOID data = NULL;



	ACL_ASSERT_HWND;



	file = CreateFile(image, GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL);

	if(file == INVALID_HANDLE_VALUE)

		acl_error(_T("Fail to load image, File not exist"));

	filesize = GetFileSize(file, NULL);



	global = GlobalAlloc(GMEM_MOVEABLE, filesize);

	data = GlobalLock(global);

	ReadFile(file, data, filesize, &bytes, NULL);

	GlobalUnlock(global);

	CreateStreamOnHGlobal(global, TRUE, &istream);



#ifdef _cplusplus

	OleLoadPicture(istream, filesize, TRUE, IID_IPicture, (LPVOID*)&ipicture);

	ipicture->get_Width(&width);

	ipicture->get_Height(&height);

#else 

	OleLoadPicture(istream, filesize, TRUE, &IID_IPicture, (LPVOID*)&ipicture);

	ipicture->lpVtbl->get_Width(ipicture, &width);

	ipicture->lpVtbl->get_Height(ipicture, &height);

#endif



	mapbuf->width = (int)(width / 26.45833333333);

	mapbuf->height = (int)(height / 26.45833333333);



	hmapdc = CreateCompatibleDC(GetDC(g_hWnd));

	if (mapbuf->hbitmap != NULL)

		DeleteObject(mapbuf->hbitmap);

	mapbuf->hbitmap = CreateCompatibleBitmap(GetDC(g_hWnd), mapbuf->width, mapbuf->height);

	SelectObject(hmapdc, mapbuf->hbitmap);



#ifdef _cplusplus

	ipicture->Render(hmapdc, 0, 0, mapbuf->width, mapbuf->height, 0, height, width, -height, NULL);

	ipicture->Release();

	istream->Release();

#else

	ipicture->lpVtbl->Render(ipicture, hmapdc, 0, 0, mapbuf->width, mapbuf->height, 0, height, width, -height, NULL);

	ipicture->lpVtbl->Release(ipicture);

	istream->lpVtbl->Release(istream);

#endif	



	DeleteDC(hmapdc);

	GlobalFree(global);

	CloseHandle(file);

} 



void freeImage(ACL_Image *mapbuf)

{

	if(mapbuf->hbitmap) return;

	DeleteObject(mapbuf->hbitmap);

	mapbuf->hbitmap = NULL;

}



void RegisterKeyboardEvent(KeyboardEventCallback callback)

{

	ACL_Window mmWindow = mmPickByHwnd(g_hWnd);

	mmWindow->g_keyboard = callback;

}



void RegisterMouseEvent(MouseEventCallback callback)

{

	ACL_Window mmWindow = mmPickByHwnd(g_hWnd);

	mmWindow->g_mouse = callback;

}



void RegisterTimerEvent(TimerEventCallback callback)

{

	ACL_Window mmWindow = mmPickByHwnd(g_hWnd);

	mmWindow->g_timer = callback;

}



void startTimer(int id,int timeinterval)

{

	SetTimer(g_hWnd, id, timeinterval, NULL);

}



void cancelTimer(int id)

{

	KillTimer(g_hWnd, id);

}



void loadSound(TCHAR *fileName,ACL_Sound *pSound)

{

	TCHAR *cmdStr;

	int len = _tcslen(fileName)*sizeof(TCHAR);

	len +=64;

	cmdStr = (TCHAR*)malloc(len);

	_stprintf(cmdStr,_T("open \"%s\" type mpegvideo alias S%d"),fileName,g_soundID);

	*pSound = g_soundID;

	++g_soundID;

	mciSendString(cmdStr,NULL,0,NULL);

	free(cmdStr);

}



void playSound(int sid,int repeat)

{

	TCHAR cmdStr[32];

	stopSound(sid);

	if(repeat)

		_stprintf(cmdStr,_T("play S%d from 0 repeat"),sid);

	else

		_stprintf(cmdStr,_T("play S%d from 0"),sid);

	mciSendString(cmdStr,NULL,0,NULL);

}



void stopSound(int sid)

{

	TCHAR cmdStr[32];

	_stprintf(cmdStr,_T("stop S%d"),sid);

	mciSendString(cmdStr,NULL,0,NULL);

}



ACL_Window mmPickByHwnd(HWND hwnd)

{

	ACL_Window ret = ACL_Windows;

	int i;

	for(i=MAX_WINDOW_COUNT;i;i--)

	{

		if(ret->hwnd == hwnd) return ret;

		ret++;

	}

	return NULL;

}

