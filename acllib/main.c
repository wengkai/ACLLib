#include "acllib.h"

#include <stdlib.h>
#include <math.h>

#define RAD(x) ((x)/360.0*2*3.1415926535)

int h = 0;
int m = 0;
int s = 0;

void paint()
{
	static const int ox = 150;
	static const int oy = 150;

	static const int hl = 46;
	static const int ml = 74;
	static const int sl = 120;

	int i;

	beginPaint();

	clearDevice();

	// circle
	setPenWidth(2);
	setPenColor(BLACK);
	setBrushColor(WHITE);
	ellipse(25,25,275,275);

	// label
	setPenWidth(1);
	setPenColor(BLACK);
	for(i=0;i<12;++i)
	{
		moveTo(ox+115*sin(RAD(180-i*30)),oy+115*cos(RAD(180-i*30)));
		lineTo(ox+125*sin(RAD(180-i*30)),oy+125*cos(RAD(180-i*30)));
	}

	// hour
	setPenWidth(8);
	setPenColor(BLACK);
	moveTo(ox,oy);
	lineTo(ox+hl*sin(RAD(180-h*30)),oy+hl*cos(RAD(180-h*30)));

	// minute
	setPenWidth(4);
	setPenColor(GREEN);
	moveTo(ox,oy);
	lineTo(ox+ml*sin(RAD(180-m*6)),oy+ml*cos(RAD(180-m*6)));

	// second
	setPenWidth(2);
	setPenColor(RED);
	moveTo(ox,oy);
	lineTo(ox+sl*sin(RAD(180-s*6)),oy+sl*cos(RAD(180-s*6)));

	endPaint();
}

void timerEvent(int tid)
{
	++s;
	if(s==60)
	{
		s = 0;
		++m;
	}
	if(m==60)
	{
		m = 0;
		++h;
	}
	if(h==12)
		h = 0;
	paint();
}

int Setup()
{
    initWindow("Clock",DEFAULT,DEFAULT,300,300);

	registerTimerEvent(timerEvent);
	
	startTimer(0,1000);
	//startTimer(0,100);
	//startTimer(0,10);
	//startTimer(0,1);


	return 0;
}
