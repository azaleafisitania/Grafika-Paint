// FILE: drawellipse.c
#include "winbgim.h"  // Provides the BGI graphics functions for Windows
#include <stdio.h>
#include "Areafill.c"
#include "circle.c"
#include "ELLIPSE.c"
//Variabel Global
bool isClicked = false;
bool isDrawing = false;
bool isReleased = false;
bool isDragged = false;
int clickedx,clickedy,releasedx,releasedy;

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

void Pause(void)
{
	int c;
	c = getch();        /* Read a character from kbd    */
	if( 27 == c ){      /* Does user wish to leave?     */
		closegraph();   /* Change to text mode          */
		exit( 1 );      /* Return to OS                 */
	}
	if( 0 == c ){      /* Did use hit a non-ASCII key? */
		c = getch();   /* Read scan code for keyboard  */
	}
	cleardevice();     /* Clear the screen             */
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
	radx = rx;
	rady = ry;
	cx = sx+radx;
	cy = sy+rady;
	ellipseMidpoint(cx,cy,radx,rady,color);
}

int main()
{
    int maxx, maxy;  // Maximum x and y pixel coordinates
	int mx,my,cx,cy,radx,rady;
	int stateDraw = 0;
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
		if(isClicked && getpixel(clickedx,clickedy)==RED) stateDraw = 1;
		switch(stateDraw){
			case 0:{
				draw_circle(670,30,20,RED);
				break;
			}
			case 1:{
				if(!isClicked) stateDraw = 2;
				break;
			}
			case 2:{
				if(isClicked) stateDraw = 3;
				break;
			}
			case 3:{
				cleardevice();
				drawing_ellipse(clickedx,clickedy,cx,cy,radx,rady,2);
				if(!isClicked) stateDraw = 0;
				break;
			}
		}
		/*if(isClicked && getpixel(clickedx,clickedy)!=0){
			isDragged = true;
			//printf("dragged!\n");
		}else{
			isDragged = false;
			//printf("not dragged!\n");
		}
		if(isDragged){
			//cleardevice();
			//draw_circle(mousex(),mousey(),rad,2);
		}
		*/
	} 
	//close program
    closegraph();
	return 0;
}
