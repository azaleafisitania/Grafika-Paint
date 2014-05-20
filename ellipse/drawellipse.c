// FILE: drawellipse.c
#include "winbgim.h"  // Provides the BGI graphics functions for Windows
#include <stdio.h>
#include <stdlib.h>
#include "Areafill.c"
#include "circle.c"
#include "ELLIPSE.c"
//Variabel Global
bool isClicked = false;
bool isDrawing = false;
bool isReleased = false;
bool isDragged = false;
int stateDraw = 0;
int clickedx,clickedy,releasedx,releasedy;
int mx,my,cx,cy,radx,rady;

void click_handler(int x, int y){ 
	isClicked = true;
	clickedx = x;
	clickedy = y;
}

void rightclick_handler(int x, int y){ 
	floodFill(x, y, 2, 0);
}

void release_handler(int x, int y){ 
	isClicked = false; 
	releasedx = x;
	releasedy = y;
}

int keyhandler(){
	int c = kbhit();
	if(c!=0) c = getch();
	return c;
}

void drawing_circle(int sx, int sy, int cx, int cy, int rad){
	int fx = mousex();
	int fy = mousey();
	int r = (fx-sx)/2;
	rad = r;
	cx = sx+r;
	cy = sy+r;
	draw_circle(cx,cy,r,2);

}

void drawing_ellipse(int sx, int sy, int cx, int cy, int radx, int rady, int color){
	int fx = mousex();
	int fy = mousey();
	int rx = (fx-sx)/2;
	int ry = (fy-sy)/2;
	radx = abs(rx);
	rady = abs(ry);
	cx = sx+rx;
	cy = sy+ry;
	ellipseMidpoint(cx,cy,radx,rady,color);
}

void update(){
	if(isClicked && getpixel(clickedx,clickedy)==RED) stateDraw = 1;
	switch(stateDraw){
		case 0:	draw_circle(20,20,10,RED); outtextxy(40,12,"Klik tombol di kiri untuk mulai menggambar ellipse"); break;
		case 1:	if(isClicked && getpixel(clickedx,clickedy)!=RED) stateDraw = 2; break;
		case 2: if(!isClicked) stateDraw = 3; break;
		case 3:{
			if(isClicked){ stateDraw = 0; }
			else{ cleardevice(); drawing_ellipse(clickedx,clickedy,cx,cy,radx,rady,2); }
			break;
		}
		case 4:{
			
		}
	}
}

int main(){
    int maxx, maxy;  // Maximum x and y pixel coordinates
    // Put the machine into graphics mode and get the maximum coordinates:
    initwindow(700, 500);         
    maxx = getmaxx();
    maxy = getmaxy();
    // Register the function that handles a left mouse click
    registermousehandler(WM_LBUTTONDOWN, click_handler);
	registermousehandler(WM_RBUTTONDOWN, rightclick_handler);
    registermousehandler(WM_LBUTTONUP, release_handler);
    //main thread
    while (1){
		delay(50);
		update();
		if(keyhandler()==27) break;
	} 
	//close program
    closegraph();
	return 0;
}

