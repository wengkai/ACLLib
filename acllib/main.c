#include "acllib.h"


int Setup()
{
	initWindow("Test",DEFAULT,DEFAULT,800,600);
	
  initConsole();
  printf("Hello\n");
  
	beginPaint();

	putPixel(10,10,RED);

	endPaint();
	
	return 0;
}