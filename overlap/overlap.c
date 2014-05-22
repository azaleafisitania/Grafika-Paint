#include "overlap.h"
#include "Polygon.c"
#include "point.h"
#include "string.h"
#include "stdlib.h"
#include "Areafill.C"

Layers makeLayers(int n, Polygon* pol){
	Layers l;
	l.size = n;
	int k;
	for(k=0; k<l.size; k++){
		l.polygons[k] = pol[k];
	}
	return l;
}

/*int isFilled(int* scan, int indexScan, int nomor_layer){
	if(scan[indexScan] != 0)&&(scan[indexScan]!=nomor_layer) return 1;
	else return 0;
}*/
Envelope makeEnvelope(int _startX, int _startY, int _width, int _height){
	Envelope e;
	e.startX = _startX;
	e.startY = _startY;
	e.width = _width;
	e.height = _height;
	return e;
}

void fill(int* scanline, int color){
	int isFilling = 0;
	
}

int nearestleft(int currentx, int num_layer, int size, int* scanline){
	int i = currentx;
	while ((i<size)&&(scanline[i]!=0)&&(scanline[i]!=num_layer)){
		i++;
	}
	if (i<size) return i;
	else return -1;
}

int* fillScanline(int i, int* scanline, Envelope envelope, Polygon pol, int nomor_layer){
	int j = 0;
	int counter = 0;
	int previous_idx;
	for (j=0; j<envelope.width; j++){
		//printf("%d, %d %d, %d ", j, i, getpixel(j,i), pol.color);
		if (getpixel(j+(getmaxx()/2), (getmaxy()/2)-i)==pol.color){
			//printf("a");
			//cek apakah dia titik ujung (titik polygonnya) apa bukan
			// harusnya masuk bawah sini kalo bukan titik ujung.
			counter++;
			//printf("%d", scanline[j]);
			int k;
			if (counter%2==0){
				//printf("%d %d", counter, j);
				//if((!isFilled(scanline, j))&&(j>previous_idx)){
					scanline[j] = nomor_layer;
					for (k = previous_idx+1; k<=j; k++){
						scanline[k]=nomor_layer;
						putpixel(k+(getmaxx()/2), (getmaxy()/2)-i, pol.color);
					}
				//}
			}
			else if(counter%2!=0){
				//if(!isFilled(scanline, j)){
					previous_idx = j;
					putpixel(j+(getmaxx()/2), (getmaxy()/2)-i, pol.color);
				//}
				/*else{
					previous_idx = nearestleft(j, nomor_layer, envelope.width, scanline);
				}*/
			}
			//fill(scanline, pol.color);			
		}
	}
	return scanline;
	//printf("\n");
}

int main(){
	int gd = DETECT, gm;
	initgraph(&gd, &gm, "");
	while (1){
	int i=0; int j=0; int k = 0;
	
	int x1, x2, x3;
	scanf("%d %d %d", &x1, &x2, &x3);
	x1--; x2--; x3--;
	Polygon poly[3];
	
	Point pa[4];
	pa[0] = makePoint(0, 0);
	pa[1] = makePoint(100,0);
	pa[2] = makePoint(100,100);
	pa[3] = makePoint(0,100);	
	poly[x1] = makePolygon(4, 1, pa);
	
	Point pb[4];
	pb[0] = makePoint(20, 20);
	pb[1] = makePoint(80,20);
	pb[2] = makePoint(80,60);
	pb[3] = makePoint(20,60);	
	poly[x2] = makePolygon(4, 2, pb);
	
	Point pc[4];
	pc[0] = makePoint(50, 10);
	pc[1] = makePoint(120,10);
	pc[2] = makePoint(120,85);
	pc[3] = makePoint(50,85);	
	poly[x3] = makePolygon(4, 3, pc);
	
	for (j = 0; j < 3; j++) drawPolygon(poly[j]);
	
	Envelope envelope = makeEnvelope(0,0,150,150);
	for (i=0; i<envelope.height; i++){	
		int freeLine[151];
		for(j = 0; j <= 150; j++) freeLine[j] = j;
	
		for (j = 0; j < 3; j++){
			Point l = getBottomLeft(poly[j]);
			Point r = getTopRight(poly[j]);
		
			if (i < l.y || i > r.y) continue;
			
			for (k = freeLine[l.x]; k <= r.x; ){
				putpixel(k+(getmaxx()/2), (getmaxy()/2)-i, poly[j].color);
				int temp = freeLine[k];
				if (r.x > freeLine[k]){
					freeLine[k] = r.x;
				}
				k = temp+1;
			}
			getch();
		}
	}
	getch();
	boundaryFill4(50+(getmaxx()/2), (getmaxy()/2)-50, 0, 0);
	}
	//getch();
	closegraph();
	return 0;
}