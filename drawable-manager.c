//Kumpulan prosedur untuk menggambar objek-objek dalam game
#include <stdio.h>
#include <graphics.h>
#include "bezier.c"

int roadLineFrame; //untuk animasi gambar jalan

//Gambar jalan frame 1
void drawRoadLine() {
	Point line1[3];
	Point line2[4];
	Point line3[4];
	Point line4[4];
	Point line5[4];

	line1[0] = makePoint(0,-10);
	line1[1] = makePoint(-2,-20);
	line1[2] = makePoint(2,-20);

	line2[0] = makePoint(-3,-25);
	line2[1] = makePoint(3,-25);
	line2[2] = makePoint(5,-40);
	line2[3] = makePoint(-5,-40);

	line3[0] = makePoint(-6,-50);
	line3[1] = makePoint(6,-50);
	line3[2] = makePoint(10,-80);
	line3[3] = makePoint(-10,-80);

	line4[0] = makePoint(-12,-100);
	line4[1] = makePoint(12,-100);
	line4[2] = makePoint(17,-150);
	line4[3] = makePoint(-17,-150);

	line5[0] = makePoint(-18,-170);
	line5[1] = makePoint(18,-170);
	line5[2] = makePoint(26,-240);
	line5[3] = makePoint(-26,-240);

	drawPolygon(line1, 3, WHITE);
	drawPolygon(line2, 4, WHITE);
	drawPolygon(line3, 4, WHITE);
	drawPolygon(line4, 4, WHITE);
	drawPolygon(line5, 4, WHITE);
}
//Gambar jalan frame 2
void drawRoadLine2() {
	Point line1[4];
	Point line2[4];
	Point line3[4];
	Point line4[4];

	line1[0] = makePoint(-1,-20);
	line1[1] = makePoint(1,-20);
	line1[2] = makePoint(3,-32);
	line1[3] = makePoint(-3,-32);

	line2[0] = makePoint(-4,-40);
	line2[1] = makePoint(4,-40);
	line2[2] = makePoint(6,-65);
	line2[3] = makePoint(-6,-65);

	line3[0] = makePoint(-7,-80);
	line3[1] = makePoint(7,-80);
	line3[2] = makePoint(11,-125);
	line3[3] = makePoint(-11,-125);

	line4[0] = makePoint(-13,-150);
	line4[1] = makePoint(13,-150);
	line4[2] = makePoint(18,-205);
	line4[3] = makePoint(-18,-205);

	drawPolygon(line1, 4, WHITE);
	drawPolygon(line2, 4, WHITE);
	drawPolygon(line3, 4, WHITE);
	drawPolygon(line4, 4, WHITE);
}
//gambar pinggir jalan
void drawRoad() {
	Point mid = makePoint(0,0);
	Point lroad = makePoint(-1*getmaxx()/2 , -1*getmaxy()/2);
	Point rroad = makePoint(getmaxx()/2 , -1*getmaxy()/2);
	drawLineBresenham(mid.x,mid.y , lroad.x,lroad.y , WHITE);
	drawLineBresenham(mid.x,mid.y , rroad.x,rroad.y , WHITE);
}
//animasi gambar jalan
void roadLineNext(){
	roadLineFrame++;
	if(roadLineFrame<2){
		drawRoadLine();
	}else if(roadLineFrame==2){
		//render();
		drawRoadLine2();
	}else if(roadLineFrame>2 && roadLineFrame<4){
		drawRoadLine2();
	}else{
		roadLineFrame=0;
		//render();
	}
}
// Gambar matahari
void drawSun() {
	int colorSun = 62; //light yellow
	draw_circle(0, 150, 30, colorSun);
	floodFill(getmaxx()/2,getmaxy()/2-179, colorSun, 0);
}
//gambar gunung
void drawMountain() {
	int colorMountain = 9; //blue
	int centerAxis = getmaxx()/2;
	drawLineBresenham (-centerAxis-50, 0, -150, 120, colorMountain); //kiri
	drawLineBresenham (100, 0, -150, 120, colorMountain);  //kanan
	drawLineBresenham (-centerAxis-50, 0, 100, 0, colorMountain);  //bawah
	drawLineBresenham (-centerAxis-50+275, 0, -150+275, 120, colorMountain); //kiri 2
	drawLineBresenham (100+275, 0, -150+275, 120, colorMountain);  //kanan 2
	drawLineBresenham (-centerAxis-50+275, 0, 100+275, 0, colorMountain);  //bawah 2
	floodFill(getmaxx()/2,getmaxy()/2-10,colorMountain,0);
	floodFill(getmaxx()/2-140,getmaxy()/2-10,colorMountain,0);
	floodFill(getmaxx()/2+140,getmaxy()/2-10,
	colorMountain,0);
}

//gambar burung
void drawBird(){
	int x1[7] = {-220, -190, -185, -180, -175, -170, -140 };
	int y1[7] = {140, 180, 150, 120, 140, 175, 130 };
	
	int x2[7] = {180, 210, 215, 220, 225, 230, 260 };
	int y2[7] = {160, 200, 160, 130, 160, 200, 160 };
	
	bezier(x1, y1, 7, WHITE);
	bezier(x2, y2, 7, WHITE);
	
}

void drawClouds(){
	int colorCloud = 8; //GRAY
	
	draw_circle(-120,  180, 15, colorCloud);
	floodFill(-120 - 14 + getmaxx()/2, getmaxy()/2 - 180, colorCloud, BLACK);
	draw_circle(-150 ,  180, 27, colorCloud);
	floodFill(-150- 26  + getmaxx()/2, getmaxy()/2 - 180, colorCloud, BLACK);
	draw_circle(-180,  180, 20, colorCloud);
	floodFill(-180 - 19 + getmaxx()/2, getmaxy()/2 - 180, colorCloud, BLACK);
	draw_circle(-200,  180, 10, colorCloud);
	floodFill(-200 - 9 + getmaxx()/2, getmaxy()/2 - 180, colorCloud, BLACK);
	
	draw_circle(-220,  100, 15, colorCloud);
	floodFill(-220 - 14 + getmaxx()/2, getmaxy()/2 - 100, colorCloud, BLACK);
	draw_circle(-250 ,  100, 27, colorCloud);
	floodFill(-250- 26  + getmaxx()/2, getmaxy()/2 - 100, colorCloud, BLACK);
	draw_circle(-280,  100, 20, colorCloud);
	floodFill(-280 - 19 + getmaxx()/2, getmaxy()/2 - 100, colorCloud, BLACK);
	draw_circle(-300,  100, 10, colorCloud);
	floodFill(-300 - 9 + getmaxx()/2, getmaxy()/2 - 100, colorCloud, BLACK);
	
	draw_circle(300,  100, 10, colorCloud);
	floodFill(300 - 9 + getmaxx()/2, getmaxy()/2 - 100, colorCloud, BLACK);
	
	draw_circle(280,  100, 20, colorCloud);
	floodFill(280 - 19 + getmaxx()/2, getmaxy()/2 - 100, colorCloud, BLACK);
	draw_circle(250 ,  100, 27, colorCloud);
	floodFill(250- 26  + getmaxx()/2, getmaxy()/2 - 100, colorCloud, BLACK);
	
	draw_circle(220,  100, 15, colorCloud);
	floodFill(220 - 14 + getmaxx()/2, getmaxy()/2 - 100, colorCloud, BLACK);
}


// Draw cars
// x: titik pusat dari sumbu x, y: titik pusat dari sumbu y
void drawCar(int x, int y) {
	int colorWheel = 7; //green
	int colorCar = 4; //red
	// Ini sangat nguli
	ellipseMidpoint(-25 + x, -37 + y, 5, colorWheel);
	ellipseMidpoint(25 + x, -37 + y, 5, colorWheel);
	drawLineBresenham (-20 + x, 35 + y, 20 + x, 35 + y, colorCar);  // Atas
	drawLineBresenham (50 + x, -30 + y, 50 + x, 0 + y, colorCar);  // Kanan
	drawLineBresenham (-50 + x, -30 + y, 50 + x, -30 + y, colorCar);  // Bawah
	drawLineBresenham (-50 + x, -30 + y, -50 + x, 0 + y, colorCar);  // Kiri
	drawLineBresenham (-40 + x, 0 + y, -20 + x, 35 + y, colorCar);  // Miring Kiri
	drawLineBresenham (40 + x, 0 + y, 20 + x, 35 + y, colorCar);  // Miring Kanan
	drawLineBresenham (-50 + x, 0 + y, -40 + x, 0 + y, colorCar);  // Tengah Kiri
	drawLineBresenham (40 + x, 0 + y, 50 + x, 0 + y, colorCar);  // Tengah Kanan
}