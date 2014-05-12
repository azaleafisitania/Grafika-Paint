#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>

//Make numbers absolute 
int absolute(int num) {
	if(num<0) {
		num = num*-1;
	}
	return num;
}

//Gambar garis
//butuh dungsi absolute()
void drawLineDDA (float x1, float y1, float x2, float y2, int color) {
	
	//biar titik 0,0 nya di tengah window bet
	int centerAxis = getmaxx()/2;
	int centerOrdinat = getmaxy()/2;
	
	//untuk menghitung gradien
	int dx = x2-x1;
	int dy = y2-y1;

	//sangat algoritma DDA
	int steps, k;
	float xinc, yinc, x, y; 
	
	if (absolute(dx)>absolute(dy)) {
		steps = absolute(dx);
	} else {
		steps = absolute(dy);
	}
	
	xinc = dx/steps; yinc = dy/steps;
	x = x1; y = y1;
	putpixel(x+centerAxis,centerOrdinat-y,color); //yey gambar bot
	
	for (k=1; k<steps; k++) {
		x = x+xinc; y = y+yinc;
		putpixel(x+centerAxis,centerOrdinat-y,color); //yey gambar bot
	}
}

//Gambar koordinat, biar gaya, warna ungu loh #teruskenapa 
void drawKoordinatDDA() {
	drawLineDDA(getmaxx()/2*-1, 0, getmaxx()/2, 0, 5); //absis
	drawLineDDA(0, getmaxy()/2*-1, 0, getmaxy()/2, 5); //ordinat
}