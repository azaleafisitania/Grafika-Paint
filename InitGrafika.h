#ifndef INIT_H
#define INIT_H
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>
int originX(int x){
	return ((getmaxx()/2)+x);
}

int originY(int y){
	return ((getmaxy()/2)-y);
}

void drawCoordinate(){
	int i;
	for(i = 0; i < getmaxy(); i++){
		putpixel(originX(0), i, 3);
	}
	for(i = 0; i < getmaxx(); i++){
		putpixel(i, originY(0), 3);
	}
}
#endif

