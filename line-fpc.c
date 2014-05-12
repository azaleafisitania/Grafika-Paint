#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>

//Gambar garis
void drawLineFPC (int x1, int y1, int x2, int y2, int color) {
	
	//biar titik 0,0 nya di tengah window bet
	int centerAxis = getmaxx()/2;
	int centerOrdinat = getmaxy()/2;
	
	//untuk menghitung gradien
	int dx = x2-x1;
	int dy = y2-y1;
	int y;
	if (dx==0) { //garis vertikal
		
		for (y=y1; y<y2 ;y++) { //iterasi pake y
			putpixel(x1+centerAxis,centerOrdinat-y,color); //yey gambar bot
		}

	} else { //garis non-vertical (horizontal dan miring)
		
		//untuk rumus garis
		float m = ((float) dy)/dx; //kalau salah satu dari dx atau dy ngga float, hasil yang 0.xx.. dibuletin ke 0 (int) terus baru di-cast ke 0.00.. (float) 
		float c = y2 - m*x2;
		int x;
		if(dx<0) { // x2<x1
			for (x=x1; x>x2; x--) {

				int y = m*x + c; //rumus garis
				putpixel(x+centerAxis,centerOrdinat-y,color); //yey gambar bot
			}

		} else { // x2>=x1
			for (x=x1; x<x2; x++) {

				int y = m*x + c; //rumus garis
				putpixel(x+centerAxis,centerOrdinat-y,color); //yey gambar bot
			}
		}
	}
}

//Gambar koordinat, biar gaya, warna ungu loh #teruskenapa 
void drawKoordinatFPC() {
	drawLineFPC(getmaxx()/2*-1, 0, getmaxx()/2, 0, 5); //absis
	drawLineFPC(0, getmaxy()/2*-1, 0, getmaxy()/2, 5); //ordinat
}