#include <graphics.h>
#include "winbgim.h"
#include "line-bresenham.c"
#include "areafill.c"

#define MBCOLOR LIGHTBLUE
#define HLCOLOR CYAN
#define BGCOLOR BLACK
#define NBAR 7
#define FPS 30

int    MaxX, MaxY;              /* The maximum resolution of the screen */
int xc, yc;
int selectedmenu;

// for line
int isClicked = 0;
int xa=-1,ya=-1,xb=-1,yb=-1;


void clearscreen() {
	int i,j;
	for (j=MaxY/6+1 ; j<MaxY ; j++) {
		for (i=0 ; i<MaxX ; i++) {
			if(getpixel(i,j)!=BGCOLOR){
				putpixel(i,j,BGCOLOR);
			}
		}
	}
}

void drawMenuBar() {
	drawLineBresenham(0,MaxY/6, MaxX, MaxY/6, MBCOLOR);
	
	int i;
	for (i=1 ; i<NBAR ; i++) {
		drawLineBresenham(MaxX/NBAR*i,0 , MaxX/NBAR*i,MaxY/6, MBCOLOR);
	}
	outtextxy(MaxX/NBAR*0+30,MaxY/12-8,"LINE");
	outtextxy(MaxX/NBAR*1+22,MaxY/12-8,"CIRCLE");
	outtextxy(MaxX/NBAR*2+14,MaxY/12-8,"AREAFILL");
	
	if (selectedmenu != -1) {
		for (i=0 ; i<NBAR ; i++) {
			floodFill(i*MaxX/NBAR+2,2, BGCOLOR, HLCOLOR);
		}
		floodFill(selectedmenu*MaxX/NBAR+2,2, HLCOLOR, BGCOLOR);
	}
}

void setmenu(int x) {
	selectedmenu = x * NBAR / MaxX;
}

void drawmenu(int x, int y) {
	//clearscreen();
	switch(selectedmenu) {
	case 0 :	// Menu Line
		if (isClicked==0) {
			xa=x; ya=y;
			isClicked = 1;
		} else {
			xb=x; yb=y;
			isClicked = 0;
		}
		break;
	}
}

void render() {
	//clearscreen();
	//drawMenuBar();
	if (ismouseclick(WM_LBUTTONDOWN)) {
		getmouseclick(WM_LBUTTONDOWN, xc, yc);
		if (yc < MaxY/6)
			setmenu(xc);
		else {
			drawmenu(xc,yc);
		}
		drawMenuBar();
	}
	
	// LINE
	
	if (xa != -1) {
		if (xb == -1) {
			drawLineBresenham(xa,ya, mousex(), mousey(),1);
		}
		else {
			drawLineBresenham(xa,ya, xb, yb,1);
		}
	}
}

int main() {
	initwindow(640,480);
	selectedmenu = 0;
	MaxX = getmaxx();
	MaxY = getmaxy();
	drawMenuBar();
	while (1) {
		//delay(1000/FPS);
		//render();
		
		//setactivepage(1);
		render();
		//setvisualpage(1);
		//setactivepage(2);
		//render();
		//setvisualpage(2);
	}
	
	closegraph();
	return 0;
}

