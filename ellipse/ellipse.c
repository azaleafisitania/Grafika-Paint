/*** Program to Draw an Ellipse using Mid - Point Algorithm ***/
#include <stdio.h>
#include <conio.h>
#include <graphics.h>

void drawEllipse(int xc, int yc, int x, int y, int c)
{
	putpixel(xc+x, yc+y, c);
	putpixel(xc-x, yc+y, c);
	putpixel(xc+x, yc-y, c);
	putpixel(xc-x, yc-y, c);
}

void ellipseMidpoint(int xc, int yc, int rx, int ry, int color)
{
	int rxSq = rx * rx;
	int rySq = ry * ry;
	int x = 0, y = ry;
	double p;
	int px = 0, py = 2 * rxSq * y;
	//xc = xc + (getmaxx()/2);
	//yc = -yc + (getmaxy()/2);
	//drawCoordinate();
	drawEllipse(xc, yc, x, y, color);
	//Region 1
	p = rySq - (rxSq * ry) + (0.25 * rxSq);
	while (px < py)
	{
		x++;
		px = px + 2 * rySq;
		if (p < 0){
			p = p + rySq + px;
		}else{
			y--;
			py = py - 2 * rxSq;
			p = p + rySq + px - py;
		}
		drawEllipse(xc, yc, x, y, color);
		//delay(30);
	}
	//Region 2
	p = rySq*(x+0.5)*(x+0.5) + rxSq*(y-1)*(y-1) - rxSq*rySq;
	while (y > 0)
	{
		y--;
		py = py - 2 * rxSq;
		if (p > 0){
			p = p + rxSq - py;
		}else{
			x++;
			px = px + 2 * rySq;
			p = p + rxSq - py + px;
		}
		drawEllipse(xc, yc, x, y, color);
		//delay(30);
	}
	//floodFill(xc, yc, 14, 0);
}

