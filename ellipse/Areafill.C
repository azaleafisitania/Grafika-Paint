#include <graphics.h>

void floodFill(int x, int y, int fillColor, int oldColor) {
	if ((getpixel(x,y) == oldColor) && (x < getmaxx()) && (x > 0) && (y < getmaxy()) && (y > 0)) {
		putpixel(x,y,fillColor);
		floodFill(x+1 , y , fillColor, oldColor);
		floodFill(x-1 , y , fillColor, oldColor);
		floodFill(x , y+1 , fillColor, oldColor);
		floodFill(x , y-1 , fillColor, oldColor);
	}
}

void boundaryFill4(int x, int y, int fillcol, int boundcol) {
	int currcol;
	currcol = getpixel(x,y);
	if ((currcol != boundcol) && (currcol != fillcol) && (x < getmaxx()) && (x > 0) && (y < getmaxy()) && (y > 0)) {
		putpixel(x,y,fillcol);
		boundaryFill4(x+1 , y , fillcol, boundcol);
		boundaryFill4(x-1 , y , fillcol, boundcol);
		boundaryFill4(x , y+1 , fillcol, boundcol);
		boundaryFill4(x , y-1 , fillcol, boundcol);
	}
}

void boundaryFill8(int x, int y, int fillcol, int boundcol) {
	int currcol;
	currcol = getpixel(x,y);
	if ((currcol != boundcol) && (currcol != fillcol) && (x < getmaxx()) && (x > 0) && (y < getmaxy()) && (y > 0)) {
		putpixel(x,y,fillcol);
		boundaryFill8(x+1 , y , fillcol, boundcol);
		boundaryFill8(x-1 , y , fillcol, boundcol);
		boundaryFill8(x , y+1 , fillcol, boundcol);
		boundaryFill8(x , y-1 , fillcol, boundcol);
		boundaryFill8(x+1 , y-1 , fillcol, boundcol);
		boundaryFill8(x-1 , y+1 , fillcol, boundcol);
		boundaryFill8(x+1 , y+1 , fillcol, boundcol);
		boundaryFill8(x-1 , y-1 , fillcol, boundcol);
	}
}
