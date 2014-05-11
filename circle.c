#include <conio.h>
#include <graphics.h>
#include <stdio.h>

/**
 * Draw cartesian coordinate with origin
 * @param x0: as absis
 * @param y0: as ordinat
 */
void draw_cartesian(int x0, int y0) {
	// Temporal variable
	int it; // for iteration purpose
	
	// Draw absis
	for (it = 0; it < getmaxx(); it++) {
		putpixel(it, y0, 10);
	}
	
	// Draw ordinat
	for (it = 0; it < getmaxy(); it++) {
		putpixel(x0, it, 10);
	}
}

/**
 * Draw 8 point in 8 region in circle
 * @param x0: absis of center point
 * @param y0: ordinat of center point
 * @param x: absis of point
 * @param y: ordinat of point
 */
// Draw circle with 8 region
void draw_8pointcircle(int x0, int y0, int x, int y, int color) {
	putpixel(x0 + x, y0 + y, color);	// Region 1
	putpixel(x0 - x, y0 + y, color);	// Region 4
	putpixel(x0 - x, y0 - y, color);	// Region 5
	putpixel(x0 + x, y0 - y, color);	// Region 8
	putpixel(x0 + y, y0 + x, color);	// Region 2
	putpixel(x0 - y, y0 + x, color);	// Region 3
	putpixel(x0 - y, y0 - x, color);	// Region 6
	putpixel(x0 + y, y0 - x, color);	// Region 7
}

/**
 * Draw circle with
 * @param x0: absis of center point
 * @param y0: ordinat of center point
 * @param r: radius
 */
void draw_circle(int x0, int y0, int r, int color) {
	int x, y;
	int dx, dy;
	int radiusError;
	
	x = r;
	y = 0;
	dx = 1 - (2 * r);
	dy = 1;
	radiusError = 0;
	
	x0 = x0 + (getmaxx()/2);
	y0 = -y0 + (getmaxy()/2);
	
	while (x >= y) {
		draw_8pointcircle(x0, y0, x, y, color);
		y++;
		radiusError = radiusError + dy;
		dy = dy + 2;
		
		if ((2 * radiusError) + dx > 0) {
			x--;
			radiusError = radiusError + dx;
			dx = dx + 2;
		}
	}
	//floodFill(x0, y0, color, 0);
}
