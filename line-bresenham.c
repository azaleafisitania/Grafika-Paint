#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>

//Gambar garis
void drawLineBresenham (float x, float y, float x2, float y2, int color) {
	//biar titik 0,0 nya di tengah window bet
	int centerAxis = 0;
	int centerOrdinat = 0;

	int w = x2 - x ;
    int h = y2 - y ;
    int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0 ;
    if (w<0) dx1 = -1 ; else if (w>0) dx1 = 1 ;
    if (h<0) dy1 = -1 ; else if (h>0) dy1 = 1 ;
    if (w<0) dx2 = -1 ; else if (w>0) dx2 = 1 ;
    int longest = fabs(w) ;
    int shortest = fabs(h) ;
    if (!(longest>shortest)) {
        longest = fabs(h) ;
        shortest = fabs(w) ;
        if (h<0) dy2 = -1 ; else if (h>0) dy2 = 1 ;
        dx2 = 0 ;            
    }
    int numerator = longest >> 1 ;
	int i;
    for (i=0;i<=longest;i++) {
        putpixel(x,y,color) ;
        numerator += shortest ;
        if (!(numerator<longest)) {
            numerator -= longest ;
            x += dx1 ;
            y += dy1 ;
        } else {
            x += dx2 ;
            y += dy2 ;
        }
    }
}

//Gambar koordinat, biar gaya, warna ungu loh #teruskenapa 
void drawKoordinatBresenham() {
	drawLineBresenham(getmaxx()/2*-1, 0, getmaxx()/2, 0, 5); //absis
	drawLineBresenham(0, getmaxy()/2*-1, 0, getmaxy()/2, 5); //ordinat
}