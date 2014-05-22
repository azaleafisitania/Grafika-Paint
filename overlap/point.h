#ifndef POINT_H
#define POINT_H
typedef struct {
	int x;
	int y;
	int mul;
} Point;

Point makePoint(int x, int y){
	Point p;
	p.x = x;
	p.y = y;
	p.mul = 1;
	return p;
}

#endif