#include "acllib.h"

void paint(int x,int y,ACL_Color c)
{
    beginPaint();
    
    setBrushColor(c);
    rectangle(x-10,y-10,x+10,y+10);

    endPaint();
}

void mouseEvent(int x,int y,int bt,int event)
{
    if(event!=BUTTON_DOWN)
        return;
    if(bt==LEFT_BUTTON)
        paint(x,y,RED);
    else if(bt==RIGHT_BUTTON)
        paint(x,y,BLUE);
}

int Setup()
{
    initWindow("",DEFAULT,DEFAULT,800,600);

    registerMouseEvent(mouseEvent);
}
