#ifndef __ACLLIB_H__
#define __ACLLIB_H__

#include <windows.h>
#include <tchar.h>

typedef enum
{ 
	SOLID_PEN	= PS_SOLID,
	DOT_PEN		= PS_DOT,
	DASH_PEN	= PS_DASH,
	DASHDOT_PEN	= PS_DASHDOT,
	DASHDOTDOT_PEN  = PS_DASHDOTDOT,
} ACL_Pen_Style;

typedef enum
{
	SOLID_BRUSH		= -1,
	HORIZONTAL_BRUSH= HS_HORIZONTAL,
	VERTICAL_BRUSH	= HS_VERTICAL,
	FDIAGONAL_BRUSH	= HS_FDIAGONAL,
	BDIAGONAL_BRUSH	= HS_BDIAGONAL,
	CROSS_BRUSH		= HS_CROSS,
	DIAGCROSS_BRUSH	= HS_DIAGCROSS,
}  ACL_Brush_Style;

typedef enum
{
    NO_BUTTON = 0,
    LEFT_BUTTON,
    MIDDLE_BUTTON,
    RIGHT_BUTTON
}ACL_Mouse_Button ;

typedef enum 
{
    BUTTON_DOWN,
    BUTTON_DOUBLECLICK,
    BUTTON_UP,
    ROLL_UP,
    ROLL_DOWN,
    MOUSEMOVE	
}ACL_Mouse_Event ;

typedef enum 
{
	KEY_DOWN,
	KEY_UP
}ACL_Keyboard_Event;

typedef struct
{
	HBITMAP hbitmap;
	int width;
	int height;
} ACL_Image;

#define MAX_WINDOW_COUNT 16

#define BLACK			RGB(0, 0, 0)
#define RED				RGB(255, 0, 0)
#define GREEN			RGB(0, 255, 0)
#define BLUE			RGB(0, 0, 255)
#define CYAN			RGB(0, 255, 255)
#define MAGENTA			RGB(255, 0, 255)
#define YELLOW			RGB(255, 255, 0)
#define WHITE			RGB(255, 255, 255)

#define BROWN			RGB(165, 42, 42)
#define LIGHTGRAY		RGB(211, 211, 211)
#define DARKGRAY		RGB(169, 169, 169)
#define LIGHTBLUE		RGB(173, 216, 230)
#define LIGHTGREEN		RGB(144, 238, 144)
#define LIGHTCYAN		RGB(224, 255, 255)
#define LIGHTRED		RGB(255, 192, 203)
#define LIGHTMAGENTA	RGB(221, 160, 221)

#define EMPTY			0xffffffff
#define DEFAULT			CW_USEDEFAULT

struct ACL_Window_Data;
typedef COLORREF ACL_Color;
typedef int ACL_Sound;
typedef struct ACL_Window_Data* ACL_Window;

typedef void (*KeyboardEventCallback) (int key,int event);
typedef void (*MouseEventCallback) (int x, int y, int button, int event);
typedef void (*TimerEventCallback) (int timerID);

ACL_Window initWindow(const TCHAR title[], int left, int top, int width, int height);
ACL_Window selectWindow(ACL_Window targetWindow);

void RegisterKeyboardEvent(KeyboardEventCallback callback);
void RegisterMouseEvent(MouseEventCallback callback);
void RegisterTimerEvent(TimerEventCallback callback);

void startTimer(int timerID, int timeinterval);
void cancelTimer(int timerID);

void loadSound(TCHAR *fileName,ACL_Sound *pSound);
void playSound(ACL_Sound soundID,int repeat);
void stopSound(ACL_Sound soundID);

void beginPaint();
void endPaint();
void clearDevice(void);

void setPenColor(ACL_Color color);
void setPenWidth(int width);
void setPenStyle(ACL_Pen_Style style);

void setBrushColor(ACL_Color color);
void setBrushStyle(ACL_Brush_Style style);

void setTextColor(ACL_Color color);
void setTextBkColor(ACL_Color color);
void setTextSize(int size);
void setTextFont(TCHAR *pFontName);

void paintText(int x, int y, const TCHAR *pStr);

void putPixel(int x, int y, ACL_Color color);
ACL_Color getPixel(int x, int y);

int getWidth();
int getHeight();
int getX(void);
int getY(void);

void moveTo(int x, int y);
void moveRel(int dx, int dy);

void line(int x0, int y0, int x1, int y1);
void lineTo(int x, int y);
void lineRel(int dx, int dy);

void arc(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4);
void rectangle(int left,int top,int right,int bottom);
void roundrect(int left,int top,int right,int bottom,int width,int height);
void ellipse(int left,int top,int right, int bottom);
void pie(int left, int top, int right, int bottom, int xr1, int yr1, int xr2, int yr2);
void chrod(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
void polygon(POINT *apt,int cpt);
void polyline(POINT *apt,int cpt);

void loadImage(const TCHAR *pImageFileName, ACL_Image *pImage);
void freeImage(ACL_Image *pImage);
void putImage(ACL_Image *pImage, int x, int y);
void putImageScale(ACL_Image *pImage,int x,int y,int width,int height);
void putImageTransparent(ACL_Image *pImage,int x,int y,int width,int height,ACL_Color bkColor);

#endif
