#include <stdio.h>
#include <conio.h>
#include <graphics.h>

// Draw Lose Screen
void printLose() {
	int i, j;	// Iterator
	MatrixTrans m;
	m = makeMatrixScale(1.1, 1.1);

	Point Y[9];
	Y[0] = makePoint(-145/2,30/2);
	Y[1] = makePoint(-115/2,30/2);
	Y[2] = makePoint(-115/2,110/2);
	Y[3] = makePoint(-80/2,200/2);
	Y[4] = makePoint(-110/2,200/2);
	Y[5] = makePoint(-130/2,150/2);
	Y[6] = makePoint(-150/2,200/2);
	Y[7] = makePoint(-180/2,200/2);
	Y[8] = makePoint(-145/2,110/2);
	drawPolygon(Y, 9, YELLOW);
	Point y = makePoint(-130/2,50);
	//floodFill((getmaxx()/2) + y.x, (getmaxy()/2) - y.y, YELLOW, BLACK);
	
	Point SmallO1[4];
	SmallO1[0] = makePoint(-20/2,60/2);
	SmallO1[1] = makePoint(20/2,60/2);
	SmallO1[2] = makePoint(20/2,170/2);
	SmallO1[3] = makePoint(-20/2,170/2);
	drawPolygon(SmallO1, 4, YELLOW);
	Point o1 = makePoint(-10/2,80/2);
	//floodFill((getmaxx()/2) + o1.x, (getmaxy()/2) - o1.y, BLACK, YELLOW);
	
	Point BigO1[4];
	BigO1[0] = makePoint(-50/2,30/2);
	BigO1[1] = makePoint(50/2,30/2);
	BigO1[2] = makePoint(50/2,200/2);
	BigO1[3] = makePoint(-50/2,200/2);
	drawPolygon(BigO1, 4, YELLOW);
	Point o2 = makePoint(45/2,35/2);
	//floodFill((getmaxx()/2) + o2.x, (getmaxy()/2) - o2.y, YELLOW, BLACK);
	
	Point U[8];
	U[0] = makePoint(80/2,30/2);
	U[1] = makePoint(180/2,30/2);
	U[2] = makePoint(180/2,200/2);
	U[3] = makePoint(150/2,200/2);
	U[4] = makePoint(150/2,60/2);
	U[5] = makePoint(110/2,60/2);
	U[6] = makePoint(110/2,200/2);
	U[7] = makePoint(80/2,200/2);
	drawPolygon(U, 8, YELLOW);
	Point u = makePoint(85/2,40/2);
	//floodFill((getmaxx()/2) + u.x, (getmaxy()/2) - u.y, YELLOW, BLACK);
	
	Point L[6];
	L[0] = makePoint(-245/2,-200/2);
	L[1] = makePoint(-145/2,-200/2);
	L[2] = makePoint(-145/2,-170/2);
	L[3] = makePoint(-215/2,-170/2);
	L[4] = makePoint(-215/2,-30/2);
	L[5] = makePoint(-245/2,-30/2);
	drawPolygon(L, 6, YELLOW);
	Point l = makePoint(-240/2,-195/2);
	//floodFill((getmaxx()/2) + l.x, (getmaxy()/2) - l.y, YELLOW, BLACK);
	
	Point SmallO2[4];
	SmallO2[0] = makePoint(-85/2,-170/2);
	SmallO2[1] = makePoint(-45/2,-170/2);
	SmallO2[2] = makePoint(-45/2,-60/2);
	SmallO2[3] = makePoint(-85/2,-60/2);
	drawPolygon(SmallO2, 4, YELLOW);
	Point o3 = makePoint(-80/2,-165/2);
	//floodFill((getmaxx()/2) + o3.x, (getmaxy()/2) - o3.y, BLACK, YELLOW);
	
	Point BigO2[4];
	BigO2[0] = makePoint(-115/2,-200/2);
	BigO2[1] = makePoint(-15/2,-200/2);
	BigO2[2] = makePoint(-15/2,-30/2);
	BigO2[3] = makePoint(-115/2,-30/2);
	drawPolygon(BigO2, 4, YELLOW);
	Point o4 = makePoint(-110/2,-195/2);
	//floodFill((getmaxx()/2) + o4.x, (getmaxy()/2) - o4.y, YELLOW, BLACK);
	
	Point S[12];
	S[0] = makePoint(15/2,-200/2);
	S[1] = makePoint(115/2,-200/2);
	S[2] = makePoint(115/2,-95/2);
	S[3] = makePoint(45/2,-95/2);
	S[4] = makePoint(45/2,-60/2);
	S[5] = makePoint(115/2,-60/2);
	S[6] = makePoint(115/2,-30/2);
	S[7] = makePoint(15/2,-30/2);
	S[8] = makePoint(15/2,-125/2);
	S[9] = makePoint(85/2,-125/2);
	S[10] = makePoint(85/2,-170/2);
	S[11] = makePoint(15/2,-170/2);
	drawPolygon(S, 12, YELLOW);
	Point s = makePoint(20/2,-195/2);
	//floodFill((getmaxx()/2) + s.x, (getmaxy()/2) - s.y, YELLOW, BLACK);
	
	Point E[12];
	E[0] = makePoint(145/2,-200/2);
	E[1] = makePoint(245/2,-200/2);
	E[2] = makePoint(245/2,-170/2);
	E[3] = makePoint(175/2,-170/2);
	E[4] = makePoint(175/2,-130/2);
	E[5] = makePoint(245/2,-130/2);
	E[6] = makePoint(245/2,-100/2);
	E[7] = makePoint(175/2,-100/2);
	E[8] = makePoint(175/2,-60/2);
	E[9] = makePoint(245/2,-60/2);
	E[10] = makePoint(245/2,-30/2);
	E[11] = makePoint(145/2,-30/2);
	drawPolygon(E, 12, YELLOW);
	Point e = makePoint(150/2,-195/2);
	//floodFill((getmaxx()/2) + e.x, (getmaxy()/2) - e.y, YELLOW, BLACK);
	
	for (j = 0; j < 7; j++){
		// Transform setiap array huruf(point) pada polygon
		for (i = 0; i < 9; i++) {
			transform(&Y[i], m);
		}
		
		for (i = 0; i < 4; i++) {
			transform(&SmallO1[i], m);
		}
		
		for (i = 0; i < 4; i++) {
			transform(&BigO1[i], m);
		}
		
		for (i = 0; i < 8; i++) {
			transform(&U[i], m);
		}
		
		for (i = 0; i < 6; i++) {
			transform(&L[i], m);
		}
		
		for (i = 0; i < 4; i++) {
			transform(&SmallO2[i], m);
		}
		
		for (i = 0; i < 4; i++) {
			transform(&BigO2[i], m);
		}
		
		for (i = 0; i < 12; i++) {
			transform(&S[i], m);
		}
		
		for (i = 0; i < 12; i++) {
			transform(&E[i], m);
		}
		
		// Transform titik pusat untuk area fill
		transform(&y, m);
		transform(&o1, m);
		transform(&o2, m);
		transform(&u, m);
		transform(&l, m);
		transform(&o3, m);
		transform(&o4, m);
		transform(&s, m);
		transform(&e, m);
		
		delay(100);
		cleardevice();
		drawPolygon(Y, 9, YELLOW);
		//floodFill((getmaxx()/2) + y.x, (getmaxy()/2) - y.y, YELLOW, BLACK);
		drawPolygon(SmallO1, 4, YELLOW);
		//floodFill((getmaxx()/2) + o1.x, (getmaxy()/2) - o1.y, BLACK, YELLOW);
		drawPolygon(BigO1, 4, YELLOW);
		//floodFill((getmaxx()/2) + o2.x, (getmaxy()/2) - o2.y, YELLOW, BLACK);
		drawPolygon(U, 8, YELLOW);
		//floodFill((getmaxx()/2) + u.x, (getmaxy()/2) - u.y, YELLOW, BLACK);
		drawPolygon(L, 6, YELLOW);
		//floodFill((getmaxx()/2) + l.x, (getmaxy()/2) - l.y, YELLOW, BLACK);
		drawPolygon(SmallO2, 4, YELLOW);
		//floodFill((getmaxx()/2) + o3.x, (getmaxy()/2) - o3.y, BLACK, YELLOW);
		drawPolygon(BigO2, 4, YELLOW);
		//floodFill((getmaxx()/2) + o4.x, (getmaxy()/2) - o4.y, YELLOW, BLACK);
		drawPolygon(S, 12, YELLOW);
		//floodFill((getmaxx()/2) + s.x, (getmaxy()/2) - s.y, YELLOW, BLACK);
		drawPolygon(E, 12, YELLOW);
		//floodFill((getmaxx()/2) + e.x, (getmaxy()/2) - e.y, YELLOW, BLACK);
	}
	floodFill((getmaxx()/2) + y.x, (getmaxy()/2) - y.y, YELLOW, BLACK);
	floodFill((getmaxx()/2) + o1.x, (getmaxy()/2) - o1.y, BLACK, YELLOW);
	floodFill((getmaxx()/2) + o2.x, (getmaxy()/2) - o2.y, YELLOW, BLACK);
	floodFill((getmaxx()/2) + u.x, (getmaxy()/2) - u.y, YELLOW, BLACK);
	floodFill((getmaxx()/2) + l.x, (getmaxy()/2) - l.y, YELLOW, BLACK);
	floodFill((getmaxx()/2) + o3.x, (getmaxy()/2) - o3.y, BLACK, YELLOW);
	floodFill((getmaxx()/2) + o4.x, (getmaxy()/2) - o4.y, YELLOW, BLACK);
	floodFill((getmaxx()/2) + s.x, (getmaxy()/2) - s.y, YELLOW, BLACK);
	floodFill((getmaxx()/2) + e.x, (getmaxy()/2) - e.y, YELLOW, BLACK);
}

// Draw Win Screen
void printWin() {
	int i, j;	// Iterator
	MatrixTrans m;
	m = makeMatrixScale(1.1, 1.1);

	Point Y[9];
	Y[0] = makePoint(-145/2,30/2);
	Y[1] = makePoint(-115/2,30/2);
	Y[2] = makePoint(-115/2,110/2);
	Y[3] = makePoint(-80/2,200/2);
	Y[4] = makePoint(-110/2,200/2);
	Y[5] = makePoint(-130/2,150/2);
	Y[6] = makePoint(-150/2,200/2);
	Y[7] = makePoint(-180/2,200/2);
	Y[8] = makePoint(-145/2,110/2);
	drawPolygon(Y, 9, GREEN);
	Point y = makePoint(-130/2,50);
	//floodFill((getmaxx()/2) + y.x, (getmaxy()/2) - y.y, GREEN, BLACK);
	
	Point SmallO1[4];
	SmallO1[0] = makePoint(-20/2,60/2);
	SmallO1[1] = makePoint(20/2,60/2);
	SmallO1[2] = makePoint(20/2,170/2);
	SmallO1[3] = makePoint(-20/2,170/2);
	drawPolygon(SmallO1, 4, GREEN);
	Point o1 = makePoint(-10/2,80/2);
	//floodFill((getmaxx()/2) + o1.x, (getmaxy()/2) - o1.y, BLACK, GREEN);
	
	Point BigO1[4];
	BigO1[0] = makePoint(-50/2,30/2);
	BigO1[1] = makePoint(50/2,30/2);
	BigO1[2] = makePoint(50/2,200/2);
	BigO1[3] = makePoint(-50/2,200/2);
	drawPolygon(BigO1, 4, GREEN);
	Point o2 = makePoint(45/2,35/2);
	//floodFill((getmaxx()/2) + o2.x, (getmaxy()/2) - o2.y, GREEN, BLACK);
	
	Point U[8];
	U[0] = makePoint(80/2,30/2);
	U[1] = makePoint(180/2,30/2);
	U[2] = makePoint(180/2,200/2);
	U[3] = makePoint(150/2,200/2);
	U[4] = makePoint(150/2,60/2);
	U[5] = makePoint(110/2,60/2);
	U[6] = makePoint(110/2,200/2);
	U[7] = makePoint(80/2,200/2);
	drawPolygon(U, 8, GREEN);
	Point u = makePoint(85/2,40/2);
	//floodFill((getmaxx()/2) + u.x, (getmaxy()/2) - u.y, GREEN, BLACK);
	
	Point W[12];
	W[0] = makePoint(-130/2,-200/2);
	W[1] = makePoint(-100/2,-200/2);
	W[2] = makePoint(-95/2,-130/2);
	W[3] = makePoint(-90/2,-200/2);
	W[4] = makePoint(-60/2,-200/2);
	W[5] = makePoint(-45/2,-30/2);
	W[6] = makePoint(-75/2,-30/2);
	W[7] = makePoint(-85/2,-100/2);
	W[8] = makePoint(-95/2,-30/2);
	W[9] = makePoint(-105/2,-100/2);
	W[10] = makePoint(-115/2,-30/2);
	W[11] = makePoint(-145/2,-30/2);
	drawPolygon(W, 12, GREEN);
	Point w = makePoint(-125/2,-195/2);
	//floodFill((getmaxx()/2) + w.x, (getmaxy()/2) - w.y, GREEN, BLACK);
	
	Point I[4];
	I[0] = makePoint(-15/2,-200/2);
	I[1] = makePoint(15/2,-200/2);
	I[2] = makePoint(15/2,-30/2);
	I[3] = makePoint(-15/2,-30/2);
	drawPolygon(I, 4, GREEN);
	Point i2 = makePoint(-10/2,-195/2);
	//floodFill((getmaxx()/2) + i2.x, (getmaxy()/2) - i2.y, GREEN, BLACK);
	
	Point N[10];
	N[0] = makePoint(45/2,-200/2);
	N[1] = makePoint(75/2,-200/2);
	N[2] = makePoint(75/2,-115/2);
	N[3] = makePoint(115/2,-200/2);
	N[4] = makePoint(145/2,-200/2);
	N[5] = makePoint(145/2,-30/2);
	N[6] = makePoint(115/2,-30/2);
	N[7] = makePoint(115/2,-115/2);
	N[8] = makePoint(75/2,-30/2);
	N[9] = makePoint(45/2,-30/2);
	drawPolygon(N, 10, GREEN);
	Point n = makePoint(50/2,-195/2);
	//floodFill((getmaxx()/2) + n.x, (getmaxy()/2) - n.y, GREEN, BLACK);
	
	for (j = 0; j < 7; j++){
		// Transform setiap array huruf(point) pada polygon
		for (i = 0; i < 9; i++) {
			transform(&Y[i], m);
		}
		
		for (i = 0; i < 4; i++) {
			transform(&SmallO1[i], m);
		}
		
		for (i = 0; i < 4; i++) {
			transform(&BigO1[i], m);
		}
		
		for (i = 0; i < 8; i++) {
			transform(&U[i], m);
		}
		
		for (i = 0; i < 12; i++) {
			transform(&W[i], m);
		}
		
		for (i = 0; i < 4; i++) {
			transform(&I[i], m);
		}
		
		for (i = 0; i < 10; i++) {
			transform(&N[i], m);
		}
		
		// Transform titik pusat untuk area fill
		transform(&y, m);
		transform(&o1, m);
		transform(&o2, m);
		transform(&u, m);
		transform(&w, m);
		transform(&i2, m);
		transform(&n, m);
		
		delay(100);
		cleardevice();
		drawPolygon(Y, 9, GREEN);
		//floodFill((getmaxx()/2) + y.x, (getmaxy()/2) - y.y, GREEN, BLACK);
		drawPolygon(SmallO1, 4, GREEN);
		//floodFill((getmaxx()/2) + o1.x, (getmaxy()/2) - o1.y, BLACK, GREEN);
		drawPolygon(BigO1, 4, GREEN);
		//floodFill((getmaxx()/2) + o2.x, (getmaxy()/2) - o2.y, GREEN, BLACK);
		drawPolygon(U, 8, GREEN);
		//floodFill((getmaxx()/2) + u.x, (getmaxy()/2) - u.y, GREEN, BLACK);
		drawPolygon(W, 12, GREEN);
		//floodFill((getmaxx()/2) + w.x, (getmaxy()/2) - w.y, GREEN, BLACK);
		drawPolygon(I, 4, GREEN);
		//floodFill((getmaxx()/2) + i2.x, (getmaxy()/2) - i2.y, GREEN, BLACK);
		drawPolygon(N, 10, GREEN);
		//floodFill((getmaxx()/2) + n.x, (getmaxy()/2) - n.y, GREEN, BLACK);
	}
	floodFill((getmaxx()/2) + y.x, (getmaxy()/2) - y.y, GREEN, BLACK);
	floodFill((getmaxx()/2) + o1.x, (getmaxy()/2) - o1.y, BLACK, GREEN);
	floodFill((getmaxx()/2) + o2.x, (getmaxy()/2) - o2.y, GREEN, BLACK);
	floodFill((getmaxx()/2) + u.x, (getmaxy()/2) - u.y, GREEN, BLACK);
	floodFill((getmaxx()/2) + w.x, (getmaxy()/2) - w.y, GREEN, BLACK);
	floodFill((getmaxx()/2) + i2.x, (getmaxy()/2) - i2.y, GREEN, BLACK);
	floodFill((getmaxx()/2) + n.x, (getmaxy()/2) - n.y, GREEN, BLACK);
}
