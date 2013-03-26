#include "acllib.h"

void paint()
{
	beginPaint();
	
	setBrushColor(RED);
	rectangle(0,0,200,200);
	
	setTextColor(BLACK);
	setTextBkColor(WHITE);
	setTextSize(30);
	setTextFont("Tahoma");
	
	paintText(50,50,"жпнд");
	
	endPaint();
}

int Setup()
{
    initWindow("Paint",DEFAULT,DEFAULT,300,300);
	
	paint();
    return 0;
}
