// FILE: drawcurve.c
#include <graphics.h>
#include "winbgim.h"
#include <stdio.h>
#include <stdlib.h>
#include "bezier.c"
//Variabel Global
#define NCURVE 100
#define NPOINT 100

int nC = 0; 
int nP = 0;
int xca[NPOINT][NCURVE],yca[NPOINT][NCURVE],xcb[NPOINT][NCURVE],ycb[NPOINT][NCURVE], cc[NCURVE];

void initCurve() {
	int i;
	for (i=0 ; i< NCURVE ; i++) {
		cx[i] = -1;
		cy[i] = -1;
		radx[i] = 0;
		rady[i] = 0;
	}
}
