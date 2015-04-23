#include "acllib.h"

int x = 400;
int y = 300;

void paint()
{
    beginPaint();

    clearDevice();
    rectangle(x-10,y-10,x+10,y+10);

    endPaint();
}

void keyboardEvent(int key,int event)
{
    if(event!=KEY_DOWN)
        return;
    switch(key)
    {
    case VK_UP:
        y-=10;
        break;
    case VK_DOWN:
        y+=10;
        break;
    case VK_LEFT:
        x-=10;
        break;
    case VK_RIGHT:
        x+=10;
        break;
    }
    paint();
}

int Setup()
{
    initWindow("",DEFAULT,DEFAULT,800,600);

    registerKeyboardEvent(keyboardEvent);

    paint();
    return 0;
}
