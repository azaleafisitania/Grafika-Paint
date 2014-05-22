#include "InitGrafika.h"
#include "transform.c"

typedef struct {
	Point p1;
	Point p2;
	float m; // gradien
	float c; // konstanta
} Line;

typedef struct{
	int offsetX;
	int offsetY;
	int width;
	int height;
	Point origin;
} GWindow;

int getPos(Point p, GWindow w){
	// mengisi array berikut:
	//_________________________
	//|     |     |     |     |
	//|_____|_____|_____|_____|
	// Atas  Kanan Bawah  Kiri
	
	int pos = 0;
	//cek atas
	if(p.y < (w.offsetY)){
		pos = pos + 1;
	}
	pos = pos << 1;
	//cek kanan
	if (p.x > (w.offsetX + w.width)){
		pos = pos + 1;
	}
	pos = pos << 1;
	//cek bawah
	if (p.y > (w.offsetY - w.height)){
		pos = pos + 1;
	}
	pos = pos << 1;
	//cek kiri
	if (p.x < (w.offsetX)){
		pos = pos + 1;
	}
	return pos;
}

Line makeLine (Point p1, Point p2){
	Line l;
	l.p1 = p1;
	l.p2 = p2;
	int dx = p2.x - p1.x;
	int dy = p2.y - p1.y;
	l.m = ((float)dy)/dx;
	l.c = l.p2.y-(l.m*l.p2.x);
	return l;
}

GWindow makeWindow(int x, int y, int w, int h){
	GWindow window;
	window.offsetX = x;
	window.offsetY = y;
	window.width = w;
	window.height = h;
	int originX = (x+w+x)/2;
	int originY = (y+h+y)/2;
	Point P = makePoint(originX, originY);
	window.origin = P;
	return window;
}


void drawLine(Line l, int color){
	int x = l.p1.x;
	int y = l.p1.y;
	int w = l.p2.x - x ;
    int h = l.p2.y - y ;
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

void drawLineOnWindow(Line l, int color, GWindow g){
	int x = l.p1.x;
	int y = l.p1.y;
	int w = l.p2.x - x ;
    int h = l.p2.y - y ;
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
        putpixel(x + g.origin.x ,g.origin.y - y,color) ;
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

void clipLine(Line l, GWindow w, GWindow v, GWindow ref){
	if ((getPos(l.p1, w)&getPos(l.p2, w))==0){
		Line newL;
		newL.m = l.m;
		newL.c = l.c;
		newL.p1 = l.p1;
		newL.p2 = l.p2;
		Point pKiri = (l.p1.x <= l.p2.x ? l.p1 : l.p2);
		Point pKanan = (l.p1.x <= l.p2.x ? l.p2 : l.p1);
		if((getPos(pKanan, w) != 0)||(getPos(pKiri, w) != 0)){
			printf("a");
			if (getPos(pKiri, w)!=0){
				float intersectX;
				if (newL.m <=0){
					intersectX = (w.offsetY - l.c)/l.m;
				}
				else{
					intersectX = ((w.offsetY-w.height) - l.c)/l.m;
				}
				pKiri.x = (w.offsetX <= intersectX ? intersectX : w.offsetX);
				pKiri.y = newL.m * pKiri.x + newL.c;
				if (getPos(pKiri, w) == 0){
					newL.p1 = pKiri;
				}
			}
			if (getPos(pKanan, w)!=0){
				float intersectX;
				if (newL.m <= 0){
					intersectX = ((w.offsetY - w.height) - l.c)/l.m;
				}
				else{
					intersectX = (w.offsetY - l.c)/l.m;
				}
				pKanan.x = (w.offsetX + w.width <= intersectX ? (w.offsetX+w.width) : intersectX);
				pKanan.y = newL.m * pKanan.x + newL.c;
				if (getPos(pKanan, w) == 0){
					newL.p2 = pKanan;
				}
			}
		}
		if ((getPos(pKanan, w) == 0)||(getPos(pKiri, w) == 0)){
			Line newLine = makeLine(pKanan, pKiri);
			drawLineOnWindow(newLine, RED, ref);
		}
	}
}

void drawWindow(GWindow w, int color){
	int i;
	for (i=0; ((i<w.width)||(i>w.width)); (w.width>0)?i++:i--){
		putpixel(w.offsetX+i, w.offsetY, color);
		putpixel(w.offsetX+i, w.offsetY+w.height, color);
	}
	for (i=0; ((i<w.height)||i>w.height); (w.height>0)?i++:i--){
		putpixel(w.offsetX, w.offsetY+i, color);
		putpixel(w.offsetX+w.width, w.offsetY+i, color);
	}
}

void drawWindowOnWindow(GWindow w, GWindow g){
	int i;
	for (i=0; i<w.width; i++){
		putpixel(g.origin.x+w.offsetX+i, g.origin.y-w.offsetY, GREEN);
		putpixel(g.origin.x+w.offsetX+i, g.origin.y-w.offsetY+w.height, GREEN);
	}
	for (i=0; i<w.height; i++){
		putpixel(g.origin.x+w.offsetX, g.origin.y-w.offsetY+i, GREEN);
		putpixel(g.origin.x+w.offsetX+w.width, g.origin.y-w.offsetY+i, GREEN);
	}
}

/*int main(){
	int gd = DETECT, gm;
    int i;
    double t;
    initgraph (&gd, &gm, "");
	GWindow window = makeWindow(0,0,320,480);
	GWindow viewport = makeWindow(320,0,320,480);
	GWindow clipWindow = makeWindow(-40,60,80,120);
	Point p1 = makePoint(-70,-70);
	Point p2 = makePoint(0,70);
	Point p3 = makePoint(-100, 0);
	Point *corn = (Point *) malloc ((3)*sizeof (Point));
	corn[0] = p1;
	corn[1] = p2;
	corn[2] = p3;
	
	
	Polygon segitiga = makePolygon(3, RED, corn);
	char command;
	do{
		system("cls");
		cleardevice();
		drawWindow(viewport);
		drawWindow(window);
		drawWindowOnWindow(clipWindow, window);
		//drawLineOnWindow(l, RED, window);
		int i = 0;
		
		
		
		for(i=0; i<segitiga.nPoint; i++){
			Line nyuLine = makeLine(corn[i], corn[(i+1)%segitiga.nPoint]);
			clipLine(nyuLine,clipWindow,viewport,window);
		}
		
		int xx = getCenter(segitiga).x;
		int yy = getCenter(segitiga).y;
		if (getPos(makePoint(xx, yy), clipWindow) == 0)
			floodFill(xx + window.origin.x, window.origin.y - yy, 5, 0);
		
		xx += 5;
		yy += 5;
		if (getPos(makePoint(xx, yy), clipWindow) == 0)
			floodFill(xx + window.origin.x, window.origin.y - yy, 5, 0);
		
		xx = corn[0].x; yy = corn[0].y + 5;
		if (getPos(makePoint(xx, yy), clipWindow) == 0)
			floodFill(xx + window.origin.x, window.origin.y - yy, 5, 0);
		
		xx = corn[1].x - 10; yy = corn[1].y - 15;
		if (getPos(makePoint(xx, yy), clipWindow) == 0)
			floodFill(xx + window.origin.x, window.origin.y - yy, 5, 0);
			
		xx = corn[2].x + 5; yy = corn[2].y;
		if (getPos(makePoint(xx, yy), clipWindow) == 0)
			floodFill(xx + window.origin.x, window.origin.y - yy, 5, 0);
		
		command = getch();
		if(command == 'w'){
			if (clipWindow.offsetY < (window.height/2))
				clipWindow.offsetY += 5;
		}
		else if(command == 's'){
			if (clipWindow.offsetY > clipWindow.height-(window.height/2))
				clipWindow.offsetY -= 5;
		}
		else if(command == 'a'){
			if (clipWindow.offsetX > -(window.width/2))
				clipWindow.offsetX -= 5;
		}
		else if(command == 'd'){
			if (clipWindow.offsetX < (window.width/2)-clipWindow.width)
				clipWindow.offsetX += 5;
		}
		else if(command == '='){
			if (clipWindow.width<=320){
				clipWindow.width *= 2;
				clipWindow.height *= 2;
			}
		}
		else if(command == '-'){
			if (clipWindow.width>=20){
				clipWindow.width = clipWindow.width/2;
				clipWindow.height = clipWindow.height/2;
			}
			if (clipWindow.offsetX <= -(window.height/2))
				clipWindow.offsetX = -(window.height/2);
		}
		if (clipWindow.offsetY >= window.height/2)
				clipWindow.offsetY = window.height/2;
		if (clipWindow.offsetY <= clipWindow.height-(window.height/2))
				clipWindow.offsetY = clipWindow.height-(window.height/2);
		if (clipWindow.offsetX <= -(window.height/2))
				clipWindow.offsetX = -(window.height/2);
		if (clipWindow.offsetX >= (window.width/2)-clipWindow.width)
				clipWindow.offsetX = (window.width/2)-clipWindow.width;
	} while (command != 'x');
	return 0;
}*/