#include "InitGrafika.h"
#define PI 3.14159265

typedef struct {
	double tabel[3][3];
} MatrixTrans;

typedef struct {
	int x;
	int y;
	int mul;
} Point;

Point makePoint(int x, int y){
	Point p;
	p.x = x;
	p.y = y;
	p.mul = 1;
	return p;
}

MatrixTrans makeMatrix(int a, int b, int c, int d, int e, int f, int g, int h, int i){
	MatrixTrans m;
	m.tabel[0][0] = a;
	m.tabel[0][1] = b;
	m.tabel[0][2] = c;
	m.tabel[1][0] = d;
	m.tabel[1][1] = e;
	m.tabel[1][2] = f;
	m.tabel[2][0] = g;
	m.tabel[2][1] = h;
	m.tabel[2][2] = i;
	return m;
}

MatrixTrans makeMatrixTranslasi(int tx, int ty){
	MatrixTrans m;
	m.tabel[0][0] = 1;
	m.tabel[0][1] = 0;
	m.tabel[0][2] = tx;
	m.tabel[1][0] = 0;
	m.tabel[1][1] = 1;
	m.tabel[1][2] = ty;
	m.tabel[2][0] = 0;
	m.tabel[2][1] = 0;
	m.tabel[2][2] = 1;
	return m;
}

MatrixTrans makeMatrixScale(double sx, double sy){
	MatrixTrans m;
	m.tabel[0][0] = sx;
	m.tabel[0][1] = 0;
	m.tabel[0][2] = 0;
	m.tabel[1][0] = 0;
	m.tabel[1][1] = sy;
	m.tabel[1][2] = 0;
	m.tabel[2][0] = 0;
	m.tabel[2][1] = 0;
	m.tabel[2][2] = 1;
	return m;
}

MatrixTrans makeMatrixShear(int shx, int shy){
	MatrixTrans m;
	m.tabel[0][0] = 1;
	m.tabel[0][1] = shx;
	m.tabel[0][2] = 0;
	m.tabel[1][0] = shy;
	m.tabel[1][1] = 1;
	m.tabel[1][2] = 0;
	m.tabel[2][0] = 0;
	m.tabel[2][1] = 0;
	m.tabel[2][2] = 1;
	return m;
}

MatrixTrans makeMatrixRotasi(int deg){
	double rad = (deg * (-1))% 360;
	rad = (rad * PI) / 180;
	MatrixTrans m;
	m.tabel[0][0] = cos(rad);
	m.tabel[0][1] = (-1) * sin(rad);
	m.tabel[0][2] = 0;
	m.tabel[1][0] = sin(rad);
	m.tabel[1][1] = cos(rad);
	m.tabel[1][2] = 0;
	m.tabel[2][0] = 0;
	m.tabel[2][1] = 0;
	m.tabel[2][2] = 1;
	return m;
}

Point dotProduct(MatrixTrans m, Point p){
	Point newP;
	newP.x = round(m.tabel[0][0]*p.x) + round(m.tabel[0][1]*p.y) + round(m.tabel[0][2]*p.mul);
	newP.y = round(m.tabel[1][0]*p.x) + round(m.tabel[1][1]*p.y) + round(m.tabel[1][2]*p.mul);
	newP.mul = round(m.tabel[2][0]*p.x) + round(m.tabel[2][1]*p.y) + round(m.tabel[2][2]*p.mul);
	return newP;
}

void transform(Point *p, MatrixTrans m){
	*p = dotProduct(m, *p);
}

void printPoint(Point p){
	printf("(%d,%d)\n", p.x, p.y);
}

void printMatrix(MatrixTrans m){
	printf("[%d %d %d]\n[%d %d %d]\n[%d %d %d]\n", m.tabel[0][0], m.tabel[0][1], m.tabel[0][2], m.tabel[1][0], m.tabel[1][1], m.tabel[1][2], m.tabel[2][0], m.tabel[2][1], m.tabel[2][2]);
}

/*void Translasi(Point p, MatrixTrans){
	p.x += transX;
	p.y += transY;
}

int main(){
	int x, y, a, b;
	int command;
	printf("masukkan Point (x <spasi> y) : " );
	scanf("%d %d", &x, &y);
	Point p = makePoint(x, y);
	printf("masukkan tipe transformasi (1. translasi, 2. rotasi, 3.scale, 4.shear) : ");
	scanf("%d", &command);
	MatrixTrans m;
	if (command == 2){
		printf("masukkan sudut rotasi (dalam derajat, positif colockwise, negatif, counter-clockwise) : ");
		scanf ("%d", &a);
		m = makeMatrixRotasi(a);
	}
	else if (command == 1){
		printf("masukkan arah translasi (arahX <spasi> arahY) : ");
		scanf ("%d %d", &a, &b);
		m = makeMatrixTranslasi(a, b);
	}
	else if (command == 3){
		printf("masukkan scaling ke arah X dan Y (arahX <spasi> arahY) : ");
		scanf ("%d %d", &a, &b);
		m = makeMatrixScale(a, b);
	}
	else if (command == 4){
		printf("masukkan shear ke arah X dan Y (arahX <spasi> arahY) : ");
		scanf ("%d %d", &a, &b);
		m = makeMatrixShear(a, b);
	}
	transform(&p, m);
	printPoint(p);
	return 0;
}*/