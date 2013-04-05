#include "acllib.h"

#define MLEN 64

int len = 0;
char str[MLEN];

void paint()
{
    beginPaint();
    
    setTextSize(16);
    paintText(0,16,str);

    endPaint();
}

void charEvent(char c)
{
    if(len+1>=MLEN)
    {
        memset(str,0,sizeof(str));
        len = 0;
    }
    str[len] = c;
    ++len;
    paint();
}

int Setup()
{
    initWindow("",DEFAULT,DEFAULT,800,600);

    registerCharEvent(charEvent);

    return 0;
}
