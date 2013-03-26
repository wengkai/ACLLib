#include "acllib.h"

int Setup()
{
    initWindow("Title",DEFAULT,DEFAULT,640,480);

    beginPaint();

    char str[100];
    snprintf(str,5,"Printf Test %d",1000);
    setTextSize(50);
    setTextBkColor(RED);
    paintText(100,100,str);

    endPaint();
    return 0;
}

