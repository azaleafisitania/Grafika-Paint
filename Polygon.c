#include <stdio.h>
#include <conio.h>
#include <graphics.h>

void drawPolygon(Point* lp, int num, int color) {
	int i;
	for (i=0 ; i<num-1 ; i++) {
		drawLineBresenham(lp[i].x , lp[i].y , lp[i+1].x, lp[i+1].y, color);
	}
	drawLineBresenham(lp[num-1].x , lp[num-1].y , lp[0].x, lp[0].y, color);
}
