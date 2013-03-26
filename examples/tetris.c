#include "acllib.h"

#define I RGB(255,0,0)
#define J RGB(255,0,255)
#define L RGB(255,255,0)
#define O RGB(0,255,255)
#define S RGB(0,0,255)
#define T RGB(192,192,192)
#define Z RGB(0,255,0)

ACL_Color square[24][10];
ACL_Color temp_square[4][10];
extern ACL_Color piece[7][4][16];

typedef enum 
{
    GS_TITLE,
    GS_GAME,
    GS_FAIL
}GameState;

GameState g_gameState;

int g_pieceX;
int g_pieceY;
int g_pieceID;
int g_pieceState;

int g_paintCount = 0;
int g_paintTime = 0;

int g_score;

double g_dt; 

void paint();

void initGame()
{
    startTimer(0,0);
    g_paintTime = clock();
    memset(square,0,sizeof(square));
}

void gameKeyboardEvent(int key)
{
}

void keyboardEvent(int key, int event)
{
    if(event==KEY_UP)
        return;
    switch(g_gameState)
    {
    case GS_TITLE:
        if(key != VK_RETURN)
            break;
        g_gameState = GS_GAME;
        initGame();
        break;
    case GS_GAME:
        gameKeyboardEvent(key);
        break;
    case GS_FAIL:
        if(key != VK_RETURN)
            break;
        cancelTimer(0);
        g_gameState = GS_TITLE;
        break;
    default:
        break;
    }
    paint();
}

void paintTitle()
{
    beginPaint();
    clearDevice();
    setTextSize(200);
    paintText(10,10,"tetris");
    endPaint();
}

void transSquareLine(ACL_Color *pl,ACL_Color *pp)
{


}

void transSquare(int )
{
    ACL_Color *pp = piece[g_pieceID][g_pieceState];
    int i;

    memset(temp_square,0,sizeof(temp_square));

    for(i=0;i<4;++i)
        transSquareLine(i+
    
}

void paintGame()
{
    int i,j;
    char tstr[100];

    beginPaint();
    clearDevice();
    
    setBrushColor(RGB(32,32,32));
    rectangle(-1,-1,801,601);

    g_paintCount += 1;
    sprintf(tstr,"%f",g_paintCount/
        ( ((double)(clock()-g_paintTime)) / 1000)
    );
    setTextSize(20);
    paintText(10,10,tstr);
    
    //paintText(10,10,"GAMING");
    //
    const int ox = 260;
    const int oy = 20;
    const int square_size = 28;

    setPenColor(RGB(192,192,192));
    rectangle(ox-1,oy-1,ox+square_size*10+1,oy+square_size*20+1);
    for(i=0;i<20;++i)
    {
        for(j=0;j<10;++j)
        {
            setBrushColor(square[i+4][j]);
            rectangle(
                ox+j*square_size,oy+i*square_size,
                ox+(j+1)*square_size,oy+(i+1)*square_size
            );
        }
    }

    endPaint();
}

void paintFail()
{
    beginPaint();
    clearDevice();
    paintText(10,10,"FAILED");
    endPaint();
}

void paint()
{
    switch(g_gameState)
    {
    case GS_TITLE:
        paintTitle();
        break;
    case GS_GAME:
        paintGame();
        break;
    case GS_FAIL:
        paintFail();
        break;
    default:
        break;
    }
}

void timerEvent(int tid)
{
    if(tid!=0)
        return;
    paint();   
}

int Main()
{
    initWindow("1",0,0,800,600);

    registerKeyboardEvent(keyboardEvent);
    registerTimerEvent(timerEvent);

    paint();

	return 0;
}


ACL_Color piece[7][4][16] =
{
	// 0
    {
        {0,I,0,0,0,I,0,0,0,I,0,0,0,I,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,I,I,I,I},    
		{0,I,0,0,0,I,0,0,0,I,0,0,0,I,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,I,I,I,I}  
    },
	// 1
    {
		{0,0,0,0,0,0,0,0,J,J,J,0,0,0,J,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	},
	// 2
	{
		{0,0,0,0,0,0,0,0,L,L,L,0,L,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	},
	// 3
	{
		{0,0,0,0,0,0,0,0,O,O,0,0,O,O,0,0},
		{0,0,0,0,0,0,0,0,O,O,0,0,O,O,0,0},
		{0,0,0,0,0,0,0,0,O,O,0,0,O,O,0,0},
		{0,0,0,0,0,0,0,0,O,O,0,0,O,O,0,0}
	},
	// 4
	{
		{0,0,0,0,0,0,0,0,O,O,0,0,O,O,0,0},
		{0,0,0,0,0,0,0,0,O,O,0,0,O,O,0,0},
		{0,0,0,0,0,0,0,0,O,O,0,0,O,O,0,0},
		{0,0,0,0,0,0,0,0,O,O,0,0,O,O,0,0}
	},
	// 5
	{
		{0,0,0,0,0,0,0,0,O,O,0,0,O,O,0,0},
		{0,0,0,0,0,0,0,0,O,O,0,0,O,O,0,0},
		{0,0,0,0,0,0,0,0,O,O,0,0,O,O,0,0},
		{0,0,0,0,0,0,0,0,O,O,0,0,O,O,0,0}
	},
	// 6
	{
		{0,0,0,0,0,0,0,0,O,O,0,0,O,O,0,0},
		{0,0,0,0,0,0,0,0,O,O,0,0,O,O,0,0},
		{0,0,0,0,0,0,0,0,O,O,0,0,O,O,0,0},
		{0,0,0,0,0,0,0,0,O,O,0,0,O,O,0,0}
	}	
};

