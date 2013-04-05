#include "acllib.h"


int Setup()
{
	initWindow("Test",DEFAULT,DEFAULT,800,600);
	
	beginPaint();

	putPixel(10,10,RED);

	endPaint();
	
	return 0;
}