#include "acllib.h"

int cx = 0;
int cy = 0;

void paint()
{
    beginPaint();

    clearDevice();
    setPenWidth(5);
    setPenColor(RED);
    lineTo(cx,cy);

    endPaint();
}

void mouseEvent(int x,int y,int key,int event)
{
    if(event==MOUSEMOVE)
    {
        cx = x;
        cy = y;
    }
    paint();
}

int Setup()
{
    initWindow("",DEFAULT,DEFAULT,800,600);

    registerMouseEvent(mouseEvent);
    return 0;
}
