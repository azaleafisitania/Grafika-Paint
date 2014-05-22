#include <graphics.h>
#include "winbgim.h"
#include "line-bresenham.c"
#include "areafill.c"
#include "drawellipse.c"
#include "clipping.c"
#include "bezier.c"
#include <stdio.h>

#define MBCOLOR LIGHTBLUE
#define HLCOLOR LIGHTCYAN
#define BGCOLOR WHITE
#define FONTCOLOR BLACK
#define NBAR 8
#define NLINE 100
#define NCURVE 100 //Curve
#define NPOINT 100 //Curve
#define MSELECT 0
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
int mx[3],my[3];
int PCOLOR = 0;

int spixel[640][480];

// for line
int nL=0;
int isClicked = 0;
int xa[NLINE],ya[NLINE],xb[NLINE],yb[NLINE], cl[NLINE];

//CLIPPING
int xclipa, yclipa, xclipb, yclipb, cclip;
int PCURRENT = 0;
GWindow clipWindow = makeWindow(-1,-1,0,0);

// polygon
int nPol=0;
int xPolA[NLINE], yPolA[NLINE], xPolB[NLINE], yPolB[NLINE], clPol[NLINE];
int xPolTemp, yPolTemp;

//curve
int nCurve = 0; 
int nPoint = 0;
int xCurve[NPOINT][NCURVE], yCurve[NPOINT][NCURVE], colorCurve[NCURVE];

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
			if((i<clipWindow.offsetX)||(j<clipWindow.offsetY)||(i>clipWindow.offsetX+clipWindow.width)||(j>clipWindow.offsetY+clipWindow.height)){
				if(getpixel(i,j)!=BGCOLOR){
					putpixel(i,j,BGCOLOR);
				}
			}
		}
	}
}

//ANTICLIPPING
void anticlip(){
	int i,j;
	int y1 = clipWindow.offsetY, y2 = clipWindow.offsetY+clipWindow.height;
	int x1 = clipWindow.offsetX, x2 = clipWindow.offsetX+clipWindow.width;
	for (j= y1; j <= y2; j++){
		for (i = x1; i <= x2; i++){
			if(getpixel(i,j)!=BGCOLOR){
				putpixel(i,j,BGCOLOR);
			}
		}
	}
}

void savestate(){
	int i,j;
	for (j=MaxY/6+1 ; j<MaxY ; j++) {
		for (i=0 ; i<MaxX ; i++) {
			if(getpixel(i,j)!=15){
				spixel[i][j] = getpixel(i,j);
			}
		}
	}
}

void drawAll(){
	int i,temp;
	temp = getactivepage();
	setactivepage(1);
	//clearscreen();
	/*for (i=0; i<nL ; i++) {
		drawLineBresenham(xa[i],ya[i], xb[i], yb[i],BGCOLOR);
	}
	for (i=0; i<nE ; i++) {
		ellipseMidpoint(cx[i],cy[i],radx[i],rady[i],BGCOLOR);
	}*/
	for (i=0; i<nL ; i++) {
		drawLineBresenham(xa[i],ya[i], xb[i], yb[i],cl[i]);
	}
	for (i=0; i<nE ; i++) {
		ellipseMidpoint(cx[i],cy[i],radx[i],rady[i],PCOLOR);
	}
	setactivepage(2);
	//clearscreen();
	/*for (i=0; i<nL ; i++) {
		drawLineBresenham(xa[i],ya[i], xb[i], yb[i],BGCOLOR);
	}
	for (i=0; i<nE ; i++) {
		ellipseMidpoint(cx[i],cy[i],radx[i],rady[i],BGCOLOR);
	}*/
	for (i=0; i<nL ; i++) {
		drawLineBresenham(xa[i],ya[i], xb[i], yb[i],cl[i]);
	}
	for (i=0; i<nE ; i++) {
		ellipseMidpoint(cx[i],cy[i],radx[i],rady[i],PCOLOR);
	}
	setactivepage(temp);
}

int length(int arr[]) { // get effective length 
	int i=0;
	while(arr[i]!=(-1)) {
		i++;
	}
	return i;
}

void initLine() {
	int i,j;
	for (i=0 ; i< NLINE ; i++) { // Line
		xa[i] = -1;
		ya[i] = -1;
		xb[i] = -1;
		yb[i] = -1;
	}
	for (i=0 ; i< NLINE ; i++) {
		xPolA[i] = -1;
		yPolA[i] = -1;
		xPolB[i] = -1;
		yPolB[i] = -1;
	}
	for (j=0 ; j<MaxY ; j++) {  
		for (i=0 ; i<MaxX ; i++) {
			spixel[i][j] = 15;
		}
		for (i=0 ; i< NLINE ; i++) {
			xPolA[i] = -1;
			yPolA[i] = -1;
			xPolB[i] = -1;
			yPolB[i] = -1;
		}
	}
	for (i=0; i<NCURVE;i++) { // Curve
		for (j=0;j<NPOINT;j++) {
			xCurve[i][j]=-1; 
			yCurve[i][j]=-1;
			//printf("%d,%d\n", xCurve[i][j], yCurve[i][j]);
		}
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
	outtextxy(MaxX/NBAR*MSELECT+15,MaxY/12-8,"SELECT");
	outtextxy(MaxX/NBAR*MLINE+27,MaxY/12-8,"LINE");
	outtextxy(MaxX/NBAR*MCIRCLE+15,MaxY/12-8,"CIRCLE");
	outtextxy(MaxX/NBAR*MAREA+9,MaxY/12-8,"AREAFILL");
	outtextxy(MaxX/NBAR*MPOLYGON+7,MaxY/12-8,"POLYGON");
	outtextxy(MaxX/NBAR*MCURVE+17,MaxY/12-8,"CURVE");
	outtextxy(MaxX/NBAR*MCLIP+8,MaxY/12-8,"CLIPPING");
	outtextxy(MaxX/NBAR*MANTI+11,MaxY/12-8,"ANTICLIP");
	 
	
}
//CLIPPING
void translasi(int *x, int *y, int transX, int transY){
	*x += transX;
	*y += transY;
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
	
	clearscreen(65,MaxY/6 + 10 , 480 , MaxY/6 + 30);
	outtextxy(20,MaxY/6 + 10, "Color : ");
	switch(selectedmenu){
		case MLINE : outtextxy(300,MaxY/6 + 10, "LIN "); break;
		case MCIRCLE : outtextxy(300,MaxY/6 + 10, "CIR "); break;
		case MPOLYGON : outtextxy(300,MaxY/6 + 10, "POL "); break;
		case MCURVE : outtextxy(300,MaxY/6 + 10, "CUR "); break;
		case MANTI : outtextxy(300,MaxY/6 + 10, "ACL "); break;
	}
	char str[4];
	outtextxy(400,MaxY/6 + 10, itoa(PCURRENT, str, 4));
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
	PCURRENT = 0;
}

void drawmenu(int x, int y) {
	printf("masuk sini, x = %d, y = %d, isClicked = %d\n", x, y, isClicked);
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
			drawAll();
		}
		break;
	case MCIRCLE : // Menu Ellipse
		if(isClicked==0){
			nE++;
			xea=x; yea=y;
			xeb=0; yeb=0;
			ce[nL-1] = PCOLOR;
			isClicked = 1;
		}else{
			xeb=x; yeb=y;
			isClicked = 0;
			drawAll();
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
			int temp = getactivepage();
			setactivepage(1);
			clip();
			setactivepage(2);
			clip();
			setactivepage(temp);
		}
		break;	
	// ANTI CLIP
	case MANTI :
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
			int temp = getactivepage();
			setactivepage(1);
			anticlip(); 
			setactivepage(2);
			anticlip(); 
			setactivepage(temp);
		}
	case MCURVE : // Menu Curve
		if (isClicked==0) {
			nCurve++; nPoint=1;
			xCurve[nCurve-1][nPoint-1]=x; yCurve[nCurve-1][nPoint-1]=y;
			colorCurve[nCurve-1] = PCOLOR;
			isClicked = 1;
		} else {
			nPoint++;
			xCurve[nCurve-1][nPoint-1]=x; yCurve[nCurve-1][nPoint-1]=y;
		}
		break;
	case MPOLYGON : // Menu Polygon
		if (isClicked==0) {
			nPol++;
			xPolTemp = x;
			yPolTemp = y;
			xPolA[nPol-1] = x; 
			yPolA[nPol-1] = y;
			clPol[nPol-1] = PCOLOR;
			isClicked = 1;
		} else {
			xPolB[nPol-1] = x; 
			yPolB[nPol-1] = y;
			if ((xPolB[nPol-1] > xPolTemp - 20) && (xPolB[nPol-1] < xPolTemp + 20) && 
				(yPolB[nPol-1] > yPolTemp - 20) && (yPolB[nPol-1] < yPolTemp + 20)) {
				isClicked = 0;
			} else {
				nPol++;
				xPolA[nPol-1] = x; 
				yPolA[nPol-1] = y;
				clPol[nPol-1] = PCOLOR;
			}
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
			//drawMenuBar();
			if (key == 75) { // Panah kiri
				PCOLOR--;
				if (PCOLOR == -1) PCOLOR = 15;
			} else if (key == 77) { // Panah kanan
				PCOLOR = (PCOLOR+1) % 16;
			}
			if (key == 80) { // Panah bawah
				int MAXN;
				if(selectedmenu == MLINE) MAXN = nL;
				else if(selectedmenu == MCIRCLE) MAXN = nE;
				else if(selectedmenu == MPOLYGON) MAXN = nPol;
				else if(selectedmenu == MCURVE) MAXN = nCurve;
				else MAXN = 0;
				PCURRENT--;
				if (PCURRENT== -1) PCURRENT = MAXN;
			} else if (key == 72) { // Panah atas
				int MAXN;
				if(selectedmenu == MLINE) MAXN = nL;
				else if(selectedmenu == MCIRCLE) MAXN = nE;
				else if(selectedmenu == MPOLYGON) MAXN = nPol;
				else if(selectedmenu == MCURVE) MAXN = nCurve;
				else MAXN = 0;
				PCURRENT = (PCURRENT+1) % MAXN;
			}
		}
		else if (key == 'w') {
			if(selectedmenu == MLINE){
				int temp = getactivepage();
				setactivepage(1);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], BGCOLOR);
				setactivepage(2);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], BGCOLOR);
				setactivepage(temp);
				translasi(&xa[PCURRENT], &ya[PCURRENT], 0, -20);
				translasi(&xb[PCURRENT], &yb[PCURRENT], 0, -20);
				temp = getactivepage();
				setactivepage(1);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], PCOLOR);
				setactivepage(2);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], PCOLOR);
				setactivepage(temp);
			}
		}
		else if (key == 's') {
			if(selectedmenu == MLINE){
				int temp = getactivepage();
				setactivepage(1);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], BGCOLOR);
				setactivepage(2);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], BGCOLOR);
				setactivepage(temp);
				translasi(&xa[PCURRENT], &ya[PCURRENT], 0, 20);
				translasi(&xb[PCURRENT], &yb[PCURRENT], 0, 20);
				temp = getactivepage();
				setactivepage(1);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], PCOLOR);
				setactivepage(2);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], PCOLOR);
				setactivepage(temp);
			}
		}
		else if (key == 'a') {
			if(selectedmenu == MLINE){
				int temp = getactivepage();
				setactivepage(1);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], BGCOLOR);
				setactivepage(2);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], BGCOLOR);
				setactivepage(temp);
				translasi(&xa[PCURRENT], &ya[PCURRENT], -20, 0);
				translasi(&xb[PCURRENT], &yb[PCURRENT], -20, 0);
				temp = getactivepage();
				setactivepage(1);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], PCOLOR);
				setactivepage(2);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], PCOLOR);
				setactivepage(temp);
			}
		}
		else if (key == 'd') {
			if(selectedmenu == MLINE){
				int temp = getactivepage();
				setactivepage(1);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], BGCOLOR);
				setactivepage(2);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], BGCOLOR);
				setactivepage(temp);
				translasi(&xa[PCURRENT], &ya[PCURRENT], 20, 0);
				translasi(&xb[PCURRENT], &yb[PCURRENT], 20, 0);
				temp = getactivepage();
				setactivepage(1);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], PCOLOR);
				setactivepage(2);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], PCOLOR);
				setactivepage(temp);
			}
		}
		
		else if (key == 'l') {
			if(selectedmenu == MLINE){
				int temp = getactivepage();
				setactivepage(1);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], BGCOLOR);
				setactivepage(2);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], BGCOLOR);
				setactivepage(temp);
				float centerx = ((float)(xa[PCURRENT] + xb[PCURRENT]))/2;
				float centery = ((float)(ya[PCURRENT] + yb[PCURRENT]))/2;
				translasi(&xa[PCURRENT], &ya[PCURRENT], (-1)*centerx, (-1)*centery);
				translasi(&xb[PCURRENT], &yb[PCURRENT], (-1)*centerx, (-1)*centery);
				MatrixTrans m = makeMatrixRotasi(10);
				Point p1 = makePoint(xa[PCURRENT], ya[PCURRENT]);
				Point p2 = makePoint(xb[PCURRENT], yb[PCURRENT]);
				transform(&p1, m);
				transform(&p2, m);
				xa[PCURRENT] = p1.x;
				ya[PCURRENT] = p1.y;
				xb[PCURRENT] = p2.x;
				yb[PCURRENT] = p2.y;
				translasi(&xa[PCURRENT], &ya[PCURRENT], centerx, centery);
				translasi(&xb[PCURRENT], &yb[PCURRENT], centerx, centery);
				temp = getactivepage();
				setactivepage(1);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], PCOLOR);
				setactivepage(2);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], PCOLOR);
				setactivepage(temp);
			}
		}
		else if (key == 'r') {
			if(selectedmenu == MLINE){
				int temp = getactivepage();
				setactivepage(1);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], BGCOLOR);
				setactivepage(2);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], BGCOLOR);
				setactivepage(temp);
				float centerx = ((float)(xa[PCURRENT] + xb[PCURRENT]))/2;
				float centery = ((float)(ya[PCURRENT] + yb[PCURRENT]))/2;
				translasi(&xa[PCURRENT], &ya[PCURRENT], (-1)*centerx, (-1)*centery);
				translasi(&xb[PCURRENT], &yb[PCURRENT], (-1)*centerx, (-1)*centery);
				MatrixTrans m = makeMatrixRotasi(-10);
				Point p1 = makePoint(xa[PCURRENT], ya[PCURRENT]);
				Point p2 = makePoint(xb[PCURRENT], yb[PCURRENT]);
				transform(&p1, m);
				transform(&p2, m);
				xa[PCURRENT] = p1.x;
				ya[PCURRENT] = p1.y;
				xb[PCURRENT] = p2.x;
				yb[PCURRENT] = p2.y;
				translasi(&xa[PCURRENT], &ya[PCURRENT], centerx, centery);
				translasi(&xb[PCURRENT], &yb[PCURRENT], centerx, centery);
				temp = getactivepage();
				setactivepage(1);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], PCOLOR);
				setactivepage(2);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], PCOLOR);
				setactivepage(temp);
			}
		}
		else if (key == '=') {
			if(selectedmenu == MLINE){
				int temp = getactivepage();
				setactivepage(1);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], BGCOLOR);
				setactivepage(2);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], BGCOLOR);
				setactivepage(temp);
				float centerx = ((float)(xa[PCURRENT] + xb[PCURRENT]))/2;
				float centery = ((float)(ya[PCURRENT] + yb[PCURRENT]))/2;
				translasi(&xa[PCURRENT], &ya[PCURRENT], (-1)*centerx, (-1)*centery);
				translasi(&xb[PCURRENT], &yb[PCURRENT], (-1)*centerx, (-1)*centery);
				MatrixTrans m = makeMatrixScale(2, 2);
				Point p1 = makePoint(xa[PCURRENT], ya[PCURRENT]);
				Point p2 = makePoint(xb[PCURRENT], yb[PCURRENT]);
				transform(&p1, m);
				transform(&p2, m);
				xa[PCURRENT] = p1.x;
				ya[PCURRENT] = p1.y;
				xb[PCURRENT] = p2.x;
				yb[PCURRENT] = p2.y;
				translasi(&xa[PCURRENT], &ya[PCURRENT], centerx, centery);
				translasi(&xb[PCURRENT], &yb[PCURRENT], centerx, centery);
				temp = getactivepage();
				setactivepage(1);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], PCOLOR);
				setactivepage(2);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], PCOLOR);
				setactivepage(temp);
			}
		}
		else if (key == '-') {
			if(selectedmenu == MLINE){
				int temp = getactivepage();
				setactivepage(1);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], BGCOLOR);
				setactivepage(2);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], BGCOLOR);
				setactivepage(temp);
				float centerx = ((float)(xa[PCURRENT] + xb[PCURRENT]))/2;
				float centery = ((float)(ya[PCURRENT] + yb[PCURRENT]))/2;
				translasi(&xa[PCURRENT], &ya[PCURRENT], (-1)*centerx, (-1)*centery);
				translasi(&xb[PCURRENT], &yb[PCURRENT], (-1)*centerx, (-1)*centery);
				MatrixTrans m = makeMatrixScale(0.5, 0.5);
				Point p1 = makePoint(xa[PCURRENT], ya[PCURRENT]);
				Point p2 = makePoint(xb[PCURRENT], yb[PCURRENT]);
				transform(&p1, m);
				transform(&p2, m);
				xa[PCURRENT] = p1.x;
				ya[PCURRENT] = p1.y;
				xb[PCURRENT] = p2.x;
				yb[PCURRENT] = p2.y;
				translasi(&xa[PCURRENT], &ya[PCURRENT], centerx, centery);
				translasi(&xb[PCURRENT], &yb[PCURRENT], centerx, centery);
				temp = getactivepage();
				setactivepage(1);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], PCOLOR);
				setactivepage(2);
				drawLineBresenham(xa[PCURRENT], ya[PCURRENT], xb[PCURRENT], yb[PCURRENT], PCOLOR);
				setactivepage(temp);
			}
		}
	}
	
	//LINE
	if (isClicked == 1 && selectedmenu == MLINE) {
		int i,xmin=MaxX,ymin=MaxY,xmax=0,ymax=0;
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
	}

	//CIRCLE/ELLIPSE
	else if (isClicked == 1 && selectedmenu == MCIRCLE) { 
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
	// ANTICLIP
	else if (isClicked == 1 && selectedmenu == MANTI) {
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

	//CURVE
	else if (isClicked == 1 && selectedmenu == MCURVE) { 
		int key = kbhit();
		if (key!=0) {
			isClicked=0;
		}

		int i;
		for (i=0; i<nCurve; i++) {
			//for(j=0; j<length(xCurve[i]); j++) {
			//	printf("Curve %d Point %d: (%d,%d)\n", i, j, xCurve[j][i], yCurve[j][i]);
			//}
			int nPointEff;
			nPointEff = length(xCurve[i]);	
			bezier(xCurve[i], yCurve[i], nPointEff, PCOLOR);

			// mekanisme clear bezier sebelumnya
			int nPointEffClr;
			nPointEffClr = length(xCurve[i])-1; 
			if(nPointEffClr>0) {
				int xCurveClr[nPointEffClr]; int yCurveClr[nPointEffClr];
				int j;
				for (j=0; j<nPointEffClr; j++) {
					xCurveClr[j] = xCurve[i][j]; yCurveClr[j] = yCurve[i][j];
					//printf("Curve %d Point %d x = %d, y = %d\n", i, j, xCurveClr[j], yCurveClr[j]);
				}
				bezier(xCurveClr, yCurveClr, nPointEffClr, BGCOLOR);	
			}
		}
	}

	// POLYGON
	else if (isClicked == 1 && selectedmenu == MPOLYGON) {
		int i, xmin=MaxX, ymin=MaxY, xmax = 0, ymax = 0;
		
		for (i=0; i<nPol ; i++) {
			//printf("xa[%d]:%d , ya[%d]:%d , xb[%d]:%d , yb[%d]:%d  \n",i,xa[i],i,ya[i],i,xb[i],i,yb[i]);
			if (xPolB[i] == -1) {
				if (my[getactivepage()] > MaxY/6 +1)
					drawLineBresenham(xPolA[i], yPolA[i], mx[getactivepage()], my[getactivepage()], BGCOLOR);
				else 
					drawLineBresenham(xPolA[i], yPolA[i], mx[getactivepage()], MaxY/6 +1, BGCOLOR);
			}
			else {
				drawLineBresenham(xPolA[i], yPolA[i], xPolB[i], yPolB[i], BGCOLOR);
			}
		}
		
		mx[getactivepage()] = mousex(); my[getactivepage()] = mousey();
		
		if ((mx[getactivepage()] > xPolTemp - 20) && (mx[getactivepage()] < xPolTemp + 20) && 
			(my[getactivepage()] > yPolTemp - 20) && (my[getactivepage()] < yPolTemp + 20)) {
				int temp = getactivepage();
				setactivepage(1);
				drawLineBresenham(xPolA[nPol-1], yPolA[nPol-1], xPolB[nPol-1], yPolB[nPol-1], BGCOLOR);
				setactivepage(2);
				drawLineBresenham(xPolA[nPol-1], yPolA[nPol-1], xPolB[nPol-1], yPolB[nPol-1], BGCOLOR);
				setactivepage(temp);
				xPolB[nPol-1] = xPolTemp;
				yPolB[nPol-1] = yPolTemp;
		} else {
			xPolB[nPol-1] = -1;
			yPolB[nPol-1] = -1;
		}
		
		for (i=0; i<nPol ; i++) {
			//printf("xa[%d]:%d , ya[%d]:%d , xb[%d]:%d , yb[%d]:%d  \n",i,xa[i],i,ya[i],i,xb[i],i,yb[i]);
			if (xPolB[i] == -1) {
				if (my[getactivepage()] > MaxY/6 +1)
					drawLineBresenham(xPolA[i], yPolA[i], mx[getactivepage()], my[getactivepage()], clPol[i]);
				else 
					drawLineBresenham(xPolA[i], yPolA[i], mx[getactivepage()], MaxY/6 +1, clPol[i]);
			}
			else {
				drawLineBresenham(xPolA[i], yPolA[i], xPolB[i], yPolB[i], clPol[i]);
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
	MaxX = getmaxx();
	MaxY = getmaxy();
	initLine();
	//CLIPPING
	initGWindow();
	initEllipse();
	setbkcolor(BGCOLOR);
	setcolor(FONTCOLOR);
	selectedmenu = 0;
	outtextxy(65,MaxY/6 + 10, "   -----  Please wait...  -----   ");
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
