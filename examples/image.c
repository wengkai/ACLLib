#include "acllib.h"

ACL_Image img;

int Setup()
{
    initWindow("Image",DEFAULT,DEFAULT,640,480);

	loadImage("lena.jpg",&img);

    beginPaint();
    putImage(&img,0,0);
    endPaint();
    return 0;
}
