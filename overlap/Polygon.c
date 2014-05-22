#ifndef polygon_c
#define polygon_c
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include "line-bresenham.c"
#include "point.h"

typedef struct{
	Point *lp;
	int nPoint;
	int color;
} Polygon;

Point getBottomLeft(Polygon poly){	
	return poly.lp[0];
}

Point getTopRight(Polygon poly){
	return poly.lp[2];
}


Polygon makePolygon(int npoint, int color, Point* corners){
	Polygon p;
	p.nPoint = npoint;
	p.lp = (Point *) malloc ((p.nPoint)*sizeof (Point));
	int i;
	for(i=0; i<npoint; i++){
		p.lp[i] = corners[i];
	}
	p.color = color;
	return p;
}

float cross(Point p1, Point p2, Point p3)
{
  return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

int isOnLine(Point pt, Point v1, Point v2)
{
  float dx1 = pt.x - v1.x, dy1 = pt.y - v1.y;
  float dx2 = pt.x - v2.x, dy2 = pt.y - v2.y;
  
  float dd1 = sqrt(dx1*dx1 + dy1 * dy1);
  float dd2 = sqrt(dx2*dx2 + dy2 * dy2);
  
  float dxr = v1.x - v2.x, dyr = v1.y - v2.y;
  float dr = sqrt(dxr * dxr + dyr * dyr);
  
  float d = fabs(dr-dd1-dd2);
  
  return (d < 0.001f)? 1 : 0;
} 

int isPointInTriangle(Point pt, Point v1, Point v2, Point v3)
{
  if (isOnLine(pt, v1, v2)) return 0;
  if (isOnLine(pt, v2, v3)) return 0;
  if (isOnLine(pt, v3, v1)) return 0;
  
  int b1, b2, b3;

  b1 = (cross(pt, v1, v2) < 0.0f)?1:0;
  b2 = (cross(pt, v2, v3) < 0.0f)?1:0;
  b3 = (cross(pt, v3, v1) < 0.0f)?1:0;
  
  return ((b1 == b2) && (b2 == b3))?1:0;
}

Point getCenter(Polygon p){
	Point newp;
	int centerx = 0;
	int centery = 0;
	int i;
	for (i=0; i<p.nPoint; i++){
		centerx += p.lp[i].x;
		centery += p.lp[i].y;
	}
	newp = makePoint(centerx/3, centery/3);
	return newp;
}

void drawPolygon(Polygon p) {
	int i;
	for (i=0 ; i<p.nPoint-1 ; i++) {
		drawLineBresenham(p.lp[i].x , p.lp[i].y , p.lp[i+1].x, p.lp[i+1].y, p.color);
	}
	drawLineBresenham(p.lp[p.nPoint-1].x , p.lp[p.nPoint-1].y , p.lp[0].x, p.lp[0].y, p.color);
}
#endif