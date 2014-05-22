#ifndef OVERLAP_H
#define OVERLAP_H
#include <stdio.h>
#include <stdlib.h>
#include "Polygon.c"


typedef struct{
	int size;
	Polygon polygons[255];
} Layers;

typedef struct{
	int startX;
	int startY;
	int width;
	int height;
}Envelope;

Layers makeLayers(int n, Polygon* pol);
int isFilled(int* scan, int indexScan);
Envelope makeEnvelope(int, int, int, int);
int* fillScanline(int i, int* scanline, Envelope e, Polygon p, int nomor_layer);
void fill(int* scanline, int color);
#endif