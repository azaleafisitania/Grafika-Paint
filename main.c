#include <graphics.h>
#include "winbgim.h"
#include "line-bresenham.c"
#include "areafill.c"

#define MBCOLOR LIGHTBLUE
#define HLCOLOR LIGHTCYAN
#define BGCOLOR WHITE
#define FONTCOLOR BLACK
#define LINECOLOR BLUE
#define FILLCOLOR GREEN
#define NBAR 8
#define NLINE 100
#define MLINE 1
#define MCIRCLE 2
#define MAREA 3
#define MPOLYGON 4
#define MCURVE 5
#define MCLIP 6
#define MANTI 7

#ifndef max
	#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef min
	#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

int    MaxX, MaxY;              /* The maximum resolution of the screen */
int xc, yc;
int selectedmenu;
int nL=0;
int mx[3],my[3];

// for line
int isClicked = 0;
int xa[NLINE],ya[NLINE],xb[NLINE],yb[NLINE];

void clear() {
	int i,j;
	for (j=0 ; j<MaxY ; j++) {
		for (i=0 ; i<MaxX ; i++) {
			if(getpixel(i,j)!=BGCOLOR){
				putpixel(i,j,BGCOLOR);
			}
		}
	}
}

void clearscreen(int x1, int y1, int x2, int y2) {
	int i,j;
	for (j=min(y1,y2) ; j<max(y1,y2) ; j++) {
		for (i=min(x1,x2) ; i<max(x1,x2) ; i++) {
			if(getpixel(i,j)!=BGCOLOR){
				putpixel(i,j,BGCOLOR);
			}
		}
	}
}

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

void initLine() {
	int i;
	for (i=0 ; i< NLINE ; i++) {
		xa[i] = -1;
		ya[i] = -1;
		xb[i] = -1;
		yb[i] = -1;
	}
}

void drawMenuBar() {
	drawLineBresenham(0,MaxY/6, MaxX, MaxY/6, MBCOLOR);
	
	int i;
	for (i=1 ; i<NBAR ; i++) {
		drawLineBresenham(MaxX/NBAR*i,0 , MaxX/NBAR*i,MaxY/6, MBCOLOR);
	}
	setcolor(FONTCOLOR);
	outtextxy(MaxX/NBAR*0+15,MaxY/12-8,"SELECT");
	outtextxy(MaxX/NBAR*MLINE+27,MaxY/12-8,"LINE");
	outtextxy(MaxX/NBAR*MCIRCLE+15,MaxY/12-8,"CIRCLE");
	outtextxy(MaxX/NBAR*MAREA+9,MaxY/12-8,"AREAFILL");
	outtextxy(MaxX/NBAR*MPOLYGON+7,MaxY/12-8,"POLYGON");
	outtextxy(MaxX/NBAR*MCURVE+17,MaxY/12-8,"CURVE");
	outtextxy(MaxX/NBAR*MCLIP+8,MaxY/12-8,"CLIPPING");
	outtextxy(MaxX/NBAR*MANTI+11,MaxY/12-8,"ANTICLIP");
	
	
}

void colorMenuBar() {
	int i;
	if (selectedmenu != -1) {
		for (i=0 ; i<NBAR ; i++) {
			if (getpixel(i*MaxX/NBAR+2,2) == HLCOLOR && i != selectedmenu)
				floodFill(i*MaxX/NBAR+2,2, BGCOLOR, HLCOLOR);
		}
		if (getpixel(selectedmenu*MaxX/NBAR+2,2) != HLCOLOR)
			floodFill(selectedmenu*MaxX/NBAR+2,2, HLCOLOR, BGCOLOR);
	}
}

void setmenu(int x) {
	selectedmenu = x * NBAR / MaxX;
}

void drawmenu(int x, int y) {
	//clearscreen();
	switch(selectedmenu) {
	case MLINE :	// Menu Line
		if (isClicked==0) {
			nL++;
			xa[nL-1]=x; ya[nL-1]=y;
			isClicked = 1;
		} else {
			xb[nL-1]=x; yb[nL-1]=y;
			isClicked = 0;
		}
		break;
	case MAREA : // Menu AreaFill
		int tempc = getpixel(x,y);
		int temp = getactivepage();
		setactivepage(1);
		floodFill(x,y,FILLCOLOR,tempc);
		setactivepage(2);
		floodFill(x,y,FILLCOLOR,tempc);
		setactivepage(temp);
		break;
	}
}

void render() {
	colorMenuBar();
	if (ismouseclick(WM_LBUTTONDOWN)) {
		getmouseclick(WM_LBUTTONDOWN, xc, yc);
		if (yc < MaxY/6) {
			setmenu(xc);
		}
		else {
			drawmenu(xc,yc);
		}
	}
	
	//LINE
	if (isClicked == 1 && selectedmenu == MLINE) {
		int i,xmin=MaxX,ymin=MaxY,xmax=0,ymax=0;
		// for (i=0 ; i<nL ; i++) {
			// if (xb[i] == -1) {
				// xmin = min(xmin,xa[i]);
				// ymin = min(ymin,ya[i]);
			// }
			// else {
				// xmin = min(min(xmin,xa[i]),xb[i]);
				// ymin = min(min(ymin,ya[i]),yb[i]);
			// }
			// xmax = max(max(xmax,xa[i]),xb[i]);
			// ymax = max(max(ymax,ya[i]),yb[i]);
			// if (isClicked == 1 && i == nL-1) {
				// xmax = mx;
				// ymax = my;
			// }
		// }
		// clearscreen(xmin,ymin,xmax,ymax);
		
		for (i=0; i<nL ; i++) {
			//printf("xa[%d]:%d , ya[%d]:%d , xb[%d]:%d , yb[%d]:%d  \n",i,xa[i],i,ya[i],i,xb[i],i,yb[i]);
			if (xb[i] == -1) {
				if (my[getactivepage()] > MaxY/6 +1)
					drawLineBresenham(xa[i],ya[i], mx[getactivepage()], my[getactivepage()],BGCOLOR);
				else 
					drawLineBresenham(xa[i],ya[i], mx[getactivepage()], MaxY/6 +1,BGCOLOR);
			}
			else {
				drawLineBresenham(xa[i],ya[i], xb[i], yb[i],BGCOLOR);
			}
		}
		
		mx[getactivepage()] = mousex(); my[getactivepage()] = mousey();
		
		for (i=0; i<nL ; i++) {
			//printf("xa[%d]:%d , ya[%d]:%d , xb[%d]:%d , yb[%d]:%d  \n",i,xa[i],i,ya[i],i,xb[i],i,yb[i]);
			if (xb[i] == -1) {
				if (my[getactivepage()] > MaxY/6 +1)
					drawLineBresenham(xa[i],ya[i], mx[getactivepage()], my[getactivepage()],LINECOLOR);
				else 
					drawLineBresenham(xa[i],ya[i], mx[getactivepage()], MaxY/6 +1,LINECOLOR);
			}
			else {
				drawLineBresenham(xa[i],ya[i], xb[i], yb[i],LINECOLOR);
			}
		}
	}
	// int i;
	// for (i=0; i<nL ; i++) {
		// if (xb[i] != -1) {
			// drawLineBresenham(xa[i],ya[i], xb[i], yb[i],LINECOLOR);
		// }
	// }
	
}

int main() {
	initwindow(640,480);
	initLine();
	setbkcolor(BGCOLOR);
	selectedmenu = 0;
	MaxX = getmaxx();
	MaxY = getmaxy();
	setactivepage(1);
	clear();
	drawMenuBar();
	mx[getactivepage()] = 0;
	my[getactivepage()] = MaxY/6+1;
	setactivepage(2);
	clear();
	drawMenuBar();
	mx[getactivepage()] = 0;
	my[getactivepage()] = MaxY/6+1;
	while (1) {
		//delay(1000/FPS);
		//render()
		setactivepage(1);
		render();
		setvisualpage(1);
		setactivepage(2);
		render();
		setvisualpage(2);
		
	}
	
	closegraph();
	return 0;
}

