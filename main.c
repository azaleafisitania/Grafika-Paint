#include <graphics.h>
#include "winbgim.h"
#include "line-bresenham.c"
#include "areafill.c"
#include "drawellipse.c"
#include "clipping.c"
#include <stdio.h>

#define MBCOLOR LIGHTBLUE
#define HLCOLOR LIGHTCYAN
#define BGCOLOR WHITE
#define FONTCOLOR BLACK
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

int MaxX, MaxY;              /* The maximum resolution of the screen */
int xc, yc;
int selectedmenu;
int nL=0;
int mx[3],my[3];
int PCOLOR = 0;

// for line
int isClicked = 0;
int xa[NLINE],ya[NLINE],xb[NLINE],yb[NLINE], cl[NLINE];
//CLIPPING
int xclipa, yclipa, xclipb, yclipb, cclip;
GWindow clipWindow = makeWindow(-1,-1,0,0);
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
//CLIPPING
void clip() {
	int i,j;
	for (j=MaxY/6+1 ; j<MaxY ; j++) {
		for (i=0 ; i<MaxX ; i++) {
			if((i<clipWindow.offsetX)||(j<clipWindow.offsetY)||(i>(clipWindow.offsetX)+(clipWindow.width))||(j>(clipWindow.offsetY)+(clipWindow.height))){
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
//CLIPPING
void initGWindow(){
	xclipa = -1;
	yclipa = -1;
	xclipb = -1;
	yclipb = -1;
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
//CLIPPING
void translasi(int transX, int transY){
	int i, j;
	clipWindow.offsetX += transX;
	clipWindow.offsetY += transY;
	/*for (i=0; ((i<w.width)||(i>w.width)); (w.width>0)?i++:i--){
		for (j=0; ((j<w.height)||j>w.height); (w.height>0)?j++:j--){
			putpixel(w.offsetX+i+transX, w.offsetY+j+transY, getpixel(w.offsetX+i, w.offsetY+j));
		}
	}*/
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
	
	clearscreen(65,MaxY/6 + 10 , 165 , MaxY/6 + 30);
	outtextxy(20,MaxY/6 + 10, "Color : ");
	switch(PCOLOR) {
	case 0 :
		outtextxy(65,MaxY/6 + 10, "Black"); break;
	case 1 :
		outtextxy(65,MaxY/6 + 10, "Blue"); break;
	case 2 :
		outtextxy(65,MaxY/6 + 10, "Green"); break;
	case 3 :
		outtextxy(65,MaxY/6 + 10, "Cyan"); break;
	case 4 :
		outtextxy(65,MaxY/6 + 10, "Red"); break;
	case 5 :
		outtextxy(65,MaxY/6 + 10, "Magenta"); break;
	case 6 :
		outtextxy(65,MaxY/6 + 10, "Brown"); break;
	case 7 :
		outtextxy(65,MaxY/6 + 10, "Light Gray"); break;
	case 8 :
		outtextxy(65,MaxY/6 + 10, "Dark Gray"); break;
	case 9 :
		outtextxy(65,MaxY/6 + 10, "Light Blue"); break;
	case 10 :
		outtextxy(65,MaxY/6 + 10, "Light Green"); break;
	case 11 :
		outtextxy(65,MaxY/6 + 10, "Light Cyan"); break;
	case 12 :
		outtextxy(65,MaxY/6 + 10, "Light Red"); break;
	case 13 :
		outtextxy(65,MaxY/6 + 10, "Light Magenta"); break;
	case 14 :
		outtextxy(65,MaxY/6 + 10, "Yellow"); break;
	case 15 :
		outtextxy(65,MaxY/6 + 10, "White"); break;
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
			cl[nL-1] = PCOLOR;
			isClicked = 1;
		} else {
			xb[nL-1]=x; yb[nL-1]=y;
			isClicked = 0;
		}
		break;
	case MCIRCLE : // Menu Ellipse
		if(isClicked==0){
			nE++;
			xea=x; yea=y;
			xeb=0; yeb=0;
			isClicked = 1;
		}else{
			xeb=x; yeb=y;
			isClicked = 0;
		}
		break;
	case MAREA : // Menu AreaFill
		int tempc;
		tempc = getpixel(x,y);
		int temp;
		temp = getactivepage();
		if (tempc != PCOLOR) {
			setactivepage(1);
			floodFill(x,y,PCOLOR,tempc);
			setactivepage(2);
			floodFill(x,y,PCOLOR,tempc);
			setactivepage(temp);
		}
		break;
	//CLIPPING
	case MCLIP :	// Menu Clip
		if (isClicked==0) {
			if(clipWindow.offsetX!=-1){
				int temp = getactivepage();
				setactivepage(1);
				drawWindow(clipWindow, BGCOLOR);
				setactivepage(2);
				drawWindow(clipWindow, BGCOLOR);
				setactivepage(temp);
			}
			xclipa=x; yclipa=y;
			xclipb=-1; yclipb=-1;
			cclip = BLACK;
			isClicked = 1;
		} else {
			xclipb=x; yclipb=y;
			//xclipa=-1; yclipa=-1;
			isClicked = 0;
		}
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
	
	// COLOR TEXT
	int key = kbhit();
	if (key!=0) {
		key = getch();
		if (key == 0) {
			key = getch();
			drawMenuBar();
			if (key == 75) { // Panah kiri
				PCOLOR--;
				if (PCOLOR == -1) PCOLOR = 15;
			} else if (key == 77) { // Panah kanan
				PCOLOR = (PCOLOR+1) % 16;
			}
		}
		else if (key == 'w') {
			int temp = getactivepage();
			setactivepage(1);
			drawWindow(clipWindow, BGCOLOR);
			setactivepage(2);
			drawWindow(clipWindow, BGCOLOR);
			setactivepage(temp);
			translasi(0, -20);
			temp = getactivepage();
			setactivepage(1);
			drawWindow(clipWindow, cclip);
			setactivepage(2);
			drawWindow(clipWindow, cclip);
			setactivepage(temp);
		}
		else if (key == 's') {
			int temp = getactivepage();
			setactivepage(1);
			drawWindow(clipWindow, BGCOLOR);
			setactivepage(2);
			drawWindow(clipWindow, BGCOLOR);
			setactivepage(temp);
			translasi(0, 20);
			temp = getactivepage();
			setactivepage(1);
			drawWindow(clipWindow, cclip);
			setactivepage(2);
			drawWindow(clipWindow, cclip);
			setactivepage(temp);
		}
		else if (key == 'a') {
			int temp = getactivepage();
			setactivepage(1);
			drawWindow(clipWindow, BGCOLOR);
			setactivepage(2);
			drawWindow(clipWindow, BGCOLOR);
			setactivepage(temp);
			translasi(-20, 0);
			temp = getactivepage();
			setactivepage(1);
			drawWindow(clipWindow, cclip);
			setactivepage(2);
			drawWindow(clipWindow, cclip);
			setactivepage(temp);
		}
		else if (key == 'd') {
			int temp = getactivepage();
			setactivepage(1);
			drawWindow(clipWindow, BGCOLOR);
			setactivepage(2);
			drawWindow(clipWindow, BGCOLOR);
			setactivepage(temp);
			translasi(20, 0);
			temp = getactivepage();
			setactivepage(1);
			drawWindow(clipWindow, cclip);
			setactivepage(2);
			drawWindow(clipWindow, cclip);
			setactivepage(temp);
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
					drawLineBresenham(xa[i],ya[i], mx[getactivepage()], my[getactivepage()],cl[i]);
				else 
					drawLineBresenham(xa[i],ya[i], mx[getactivepage()], MaxY/6 +1,cl[i]);
			}
			else {
				drawLineBresenham(xa[i],ya[i], xb[i], yb[i],cl[i]);
			}
		}
	}else if (isClicked == 1 && selectedmenu == MCIRCLE) { //CIRCLE/ELLIPSE
		int i;
		for (i=0; i<nE ; i++) {
			if (xeb == 0) {
				if (my[getactivepage()] > MaxY/6 +1)
					drawing_ellipse(xea,yea, mx[getactivepage()], my[getactivepage()],i,BGCOLOR);
				else 
					drawing_ellipse(xea,yea, mx[getactivepage()], MaxY/6 +1,i,BGCOLOR);
			}
			else {
				ellipseMidpoint(cx[i],cy[i],radx[i],rady[i],BGCOLOR);
			}
		}
		mx[getactivepage()] = mousex(); my[getactivepage()] = mousey();
		for (i=0; i<nE ; i++) {
			if (xeb == 0) {
				if (my[getactivepage()] > MaxY/6 +1)
					drawing_ellipse(xea,yea, mx[getactivepage()], my[getactivepage()],i,PCOLOR);
				else 
					drawing_ellipse(xea,yea, mx[getactivepage()], MaxY/6 +1,i,PCOLOR);
			}
			else {
				ellipseMidpoint(cx[i],cy[i],radx[i],rady[i],PCOLOR);
			}
		}
	}
	//CLIPPING
	else if (isClicked == 1 && selectedmenu == MCLIP) {
		int i,xmin=MaxX,ymin=MaxY,xmax=0,ymax=0;
		if (xclipb == -1) {
			if (my[getactivepage()] > MaxY/6 +1){
				clipWindow = makeWindow(xclipa,yclipa, mx[getactivepage()]-xclipa, my[getactivepage()]-yclipa);
				drawWindow(clipWindow, BGCOLOR);
			}
			else{
				clipWindow = makeWindow(xclipa,yclipa, mx[getactivepage()]-xclipa, (MaxY/6 +1)-yclipa);
				drawWindow(clipWindow, BGCOLOR);
			}
		}
		else {
			clipWindow = makeWindow(xclipa,yclipa, xclipb-xclipa, yclipb-yclipa);
			drawWindow(clipWindow, BGCOLOR);
		}
		mx[getactivepage()] = mousex(); my[getactivepage()] = mousey();
		if (xclipb == -1) {
			if (my[getactivepage()] > MaxY/6 +1){
				clipWindow = makeWindow(xclipa,yclipa, mx[getactivepage()]-xclipa, my[getactivepage()]-yclipa);
				drawWindow(clipWindow, cclip);
			}
			else{ 
				clipWindow = makeWindow(xclipa,yclipa, mx[getactivepage()]-xclipa, (MaxY/6 +1)-yclipa);
				drawWindow(clipWindow, cclip);
			}
		}
		else {
			clipWindow = makeWindow(xclipa,yclipa, xclipb-xclipa, yclipb-yclipa);
			drawWindow(clipWindow, BGCOLOR);
		}
	}
}

int main() {
	initwindow(640,480);
	initLine();
	//CLIPPING
	initGWindow();
	initEllipse();
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
