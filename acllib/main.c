#include "acllib.h"

int dx,dy;

void paint()
{
	beginPaint();
	setPenColor(RED);
	rectangle(0,0,200,200);
	moveTo(0,0);
	lineTo(dx,dy);
	endPaint();
}


void ms(int x,int y ,int f ,int s)
{
	dx = x;
	dy = y;
	paint();
}



int Main()
{
	ACL_Window a = initWindow("1",0,0,200,200);
	ACL_Window b = initWindow("2",300,0,200,200);

	selectWindow(a);
	RegisterMouseEvent(ms);
	selectWindow(b);
	RegisterMouseEvent(ms);

	return 0;
}
