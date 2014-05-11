#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <stdbool.h>

#include "line-fpc.c"
#include "line-dda.c"
#include "line-bresenham.c"

//Gambar garis
void drawLine(int x1, int y1, int x2, int y2, int color, int teknik) {
	switch(teknik) {
		case 1: drawLineFPC(x1, y1, x2, y2, color); break;
		case 2: drawLineDDA(x1, y1, x2, y2, color); break;
		case 3: drawLineBresenham(x1, y1, x2, y2, color); break;
		default: printf("Input salah"); break;
	}
	
}	

//Gambar koordinat, biar gaya, warna ungu loh #teruskenapa 
void drawKoordinat(int teknik) {
	switch(teknik) {
		case 1: drawKoordinatFPC(); break;
		case 2: drawKoordinatDDA(); break;
		case 3: drawKoordinatBresenham(); break;
		default: printf("Input salah"); break;
	}	
}

int main() {
	
	printf("Ayo gambar garis!\n");
	bool cont = true; //lanjut ngga
	int driver = DETECT,gmode;
	initgraph(&driver,&gmode,"");
	
	while(cont) {
		
		//pilih teknik
		int tline;
		printf("\nTeknik gambar yang tersedia:\n1. FPC\n2. DDA\n3. Bresenham\nPilihan: ");
		scanf("%d", &tline);

		if((tline>=1)&&(tline<=3)) {
			//input user
			int x1, y1, x2, y2, color;
			printf("x1 y1 x2 y2 color: ");
			scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &color); //jangan. pake. scanf. :|
	
			//draw	
			drawKoordinat(tline);
			drawLine(x1, y1, x2, y2, color, tline);

		} else {
			printf("Input salah\n");
		}
		
		//continue or not
		printf("continue? 0/1: ");
		scanf("%d", &cont);
	
		cleardevice(); //cuma clear screen graph, kalo mau close pake closegraph()
	}
	
	return 0;
}