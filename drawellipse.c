// FILE: drawellipse.c
#include <graphics.h>
#include "winbgim.h"
#include <stdio.h>
#include <stdlib.h>
#include "ellipse.c"
#include "circle.c"
//Variabel Global
#define NELLIPSE 100
int nE = 0;
int xea,yea,xeb,yeb;
int cx[NELLIPSE],cy[NELLIPSE],radx[NELLIPSE],rady[NELLIPSE];

void initEllipse() {
	int i;
	for (i=0 ; i< NELLIPSE ; i++) {
		cx[i] = -1;
		cy[i] = -1;
		radx[i] = 0;
		rady[i] = 0;
	}
}

/*void drawing_circle(int sx, int sy, int cx, int cy, int rad){
	int fx = mousex();
	int fy = mousey();
	int r = (fx-sx)/2;
	rad = r;
	cx = sx+r;
	cy = sy+r;
	draw_circle(cx,cy,r,2);

}*/

void drawing_ellipse(int sx, int sy, int fx, int fy, int index, int color){
	int rx = (fx-sx)/2;
	int ry = (fy-sy)/2;
	radx[index] = abs(rx);
	rady[index] = abs(ry);
	cx[index] = sx+rx;
	cy[index] = sy+ry;
	ellipseMidpoint(cx[index],cy[index],radx[index],rady[index],color);
}

