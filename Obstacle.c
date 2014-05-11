#ifndef OBSTACLE_C
#define OBSTACLE_C

#include <stdio.h>
#include <graphics.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

//variable global untuk rock
Point mid,mid2;
int rad,temp,frame,r;
//variable global untuk kotak
Point midK,midK1,midK2,midK3,midK4;
int jar, tempK, frameK, rK;
//variable global untuk Roda
Point midR,midR2;
int radR1,radR2,tempR,frameR;
//score permainan
int score;

//OBSTACLE BATU
void spawnRockUpdate() {
	MatrixTrans m,mb,mb1,mb2,m1,m2;
	//animasi frame by frame
	if(frame==0){
		rad = 2;
		mid = makePoint(0,-5);
		mid2 = makePoint(mid.x,mid.y-rad+1);
		r = rand() % 3;
		frame++;
	}else if(frame>0 && frame<55){
		frame++;
	}else{
		frame=0;
		score++;
	}
	if ((frame >=0) && (frame<27)) {
		if (r == 0) { // KIRI 
				m = makeMatrixTranslasi(-1*(0.3*frame+1),-0.5*(frame+1));
			}
			else if (r == 1) { // KANAN
				m = makeMatrixTranslasi((0.3*frame+1),-0.5*(frame+1));
			}
			else { // TENGAH
				m = makeMatrixTranslasi(0,-0.5*(frame+1));
			}
		transform(&mid,m);
		rad += frame/9+1;
		mid2 = makePoint(mid.x,mid.y-rad+1);
		draw_circle(mid.x,mid.y, rad,LIGHTGRAY);
		draw_circle(mid2.x,mid2.y, 1,YELLOW);
		if (frame == 26) temp = mid.x;
	}
	else if ((frame >= 27) && (frame < 45)) {
		m = makeMatrixRotasi(10);
		m1 = makeMatrixTranslasi(-50-temp,180);
		m2 = makeMatrixTranslasi(50+temp,-180);
		mb = makeMatrixRotasi(-10);
		mb1 = makeMatrixTranslasi(50-temp,180);
		mb2 = makeMatrixTranslasi(-50+temp,-180);
		if (mid.x < 0) { // DI KIRI LAYAR
			transform(&mid,mb1);
			transform(&mid,mb);
			transform(&mid,mb2);
		}
		else {
			transform(&mid,m1);
			transform(&mid,m);
			transform(&mid,m2);
		}
		if (mid.x < 0) { // DI KIRI LAYAR
			transform(&mid2,mb1);
			transform(&mid2,mb);
			transform(&mid2,mb2);
		}
		else {
			transform(&mid2,m1);
			transform(&mid2,m);
			transform(&mid2,m2);
		}
		draw_circle(mid.x,mid.y, rad,LIGHTGRAY);
		draw_circle(mid2.x,mid2.y, 1,YELLOW);
		//floodFill(mid.x+getmaxx()/2,getmaxy()/2-mid.y,LIGHTGRAY,BLACK);
	}
	else {
		m = makeMatrixTranslasi(20,10);
		mb = makeMatrixTranslasi(-20,10);
		if (mid.x < 0) { // DI KIRI LAYAR
			transform(&mid,mb);
		}
		else if (mid.x > 0) {
			transform(&mid,m);
		}
		else {
			if ((rand() % 2) == 0) {
				transform(&mid,mb);
			}
			else {
				transform(&mid,m);
			}
		}
		if (mid.x < 0) { // DI KIRI LAYAR
			transform(&mid2,mb);
		}
		else if (mid.x > 0) {
			transform(&mid2,m);
		}
		else {
			if ((rand() % 2) == 0) {
				transform(&mid2,mb);
			}
			else {
				transform(&mid2,m);
			}
		}
		draw_circle(mid.x,mid.y, rad,LIGHTGRAY);
		draw_circle(mid2.x,mid2.y, 1,YELLOW);
	}
}
//OBSTACLE KOTAK
void spawnKotakUpdate() {
	MatrixTrans mK,mbK,mb1K,mb2K,m1K,m2K;
	//animasi frame by frame
	if(frameK==0){
		jar = 2;
		midK = makePoint(0,-5);
		rK = rand() % 3;
		frameK++;
	}else if(frameK>0 && frameK<55){
		frameK++;
	}else{
		frameK=0;
		score++;
	}
	if ((frameK >=0) && (frameK<27)) {
		if (rK == 1) { // KIRI 
				mK = makeMatrixTranslasi(-1*(0.3*frameK+1),-0.5*(frame+1));
			}
			else if (rK == 0) { // KANAN
				mK = makeMatrixTranslasi((0.3*frameK+1),-0.5*(frame+1));
			}
			else { // TENGAH
				mK = makeMatrixTranslasi(0,-0.5*(frameK+1));
			}
		transform(&midK,mK);
		jar += frameK/9+1;
		drawLineBresenham(midK.x-jar,midK.y+jar,midK.x+jar, midK.y+jar,BROWN);
		drawLineBresenham(midK.x+jar,midK.y+jar,midK.x+jar, midK.y-jar,BROWN);
		drawLineBresenham(midK.x+jar,midK.y-jar,midK.x-jar, midK.y-jar,BROWN);
		drawLineBresenham(midK.x-jar,midK.y-jar,midK.x-jar, midK.y+jar,BROWN);
		if (frameK == 26){ 
			tempK = midK.x;
			//4 titik sudut kotak
			midK1 = makePoint(midK.x-jar,midK.y+jar);
			midK2 = makePoint(midK.x+jar,midK.y+jar);
			midK3 = makePoint(midK.x+jar,midK.y-jar);
			midK4 = makePoint(midK.x-jar,midK.y-jar);
		}
	}
	else if ((frameK >= 27) && (frameK < 45)) {
		mK = makeMatrixRotasi(10);
		m1K = makeMatrixTranslasi(-50-tempK,180);
		m2K = makeMatrixTranslasi(50+tempK,-180);
		mbK = makeMatrixRotasi(-10);
		mb1K = makeMatrixTranslasi(50-tempK,180);
		mb2K = makeMatrixTranslasi(-50+tempK,-180);
		if (midK.x < 0) { // DI KIRI LAYAR
			transform(&midK,mb1K);
			transform(&midK1,mb1K);
			transform(&midK2,mb1K);
			transform(&midK3,mb1K);
			transform(&midK4,mb1K);
			transform(&midK,mbK);
			transform(&midK1,mbK);
			transform(&midK2,mbK);
			transform(&midK3,mbK);
			transform(&midK4,mbK);
			transform(&midK,mb2K);
			transform(&midK1,mb2K);
			transform(&midK2,mb2K);
			transform(&midK3,mb2K);
			transform(&midK4,mb2K);
		}
		else {
			transform(&midK,m1K);
			transform(&midK1,m1K);
			transform(&midK2,m1K);
			transform(&midK3,m1K);
			transform(&midK4,m1K);
			transform(&midK,mK);
			transform(&midK1,mK);
			transform(&midK2,mK);
			transform(&midK3,mK);
			transform(&midK4,mK);
			transform(&midK,m2K);
			transform(&midK1,m2K);
			transform(&midK2,m2K);
			transform(&midK3,m2K);
			transform(&midK4,m2K);
		}
		drawLineBresenham(midK1.x,midK1.y,midK2.x, midK2.y,BROWN);
		drawLineBresenham(midK2.x,midK2.y,midK3.x, midK3.y,BROWN);
		drawLineBresenham(midK3.x,midK3.y,midK4.x, midK4.y,BROWN);
		drawLineBresenham(midK1.x,midK1.y,midK4.x, midK4.y,BROWN);
	}
	else {
		mK = makeMatrixTranslasi(20,10);
		mbK = makeMatrixTranslasi(-20,10);
		if (midK.x < 0) { // DI KIRI LAYAR
			transform(&midK,mbK);
		}
		else if (midK.x > 0) {
			transform(&midK,mK);
		}
		else {
			if ((rand() % 2) == 0) {
				transform(&midK,mbK);
			}
			else {
				transform(&midK,mK);
			}
		}
		drawLineBresenham(midK.x-jar,midK.y+jar,midK.x+jar, midK.y+jar,BROWN);
		drawLineBresenham(midK.x+jar,midK.y+jar,midK.x+jar, midK.y-jar,BROWN);
		drawLineBresenham(midK.x+jar,midK.y-jar,midK.x-jar, midK.y-jar,BROWN);
		drawLineBresenham(midK.x-jar,midK.y-jar,midK.x-jar, midK.y+jar,BROWN);
	}
}
//OBSTACLE RODA
void spawnRodaUpdate() {
	MatrixTrans mR,mbR,mb1R,mb2R,m1R,m2R;
	
	if(frameR==0){
		radR1 = 2;
		//radR2 = radR1/2;
		radR2 = radR1*4/5;
		midR = makePoint(-10,-5);
		midR2 = makePoint(midR.x,midR.y-radR1+1);
		r = rand() % 3;
		frameR++;
	}else if(frameR>0 && frameR<55){
		frameR++;
	}else{
		frameR=0;
		score++;
	}
	if ((frameR >=0) && (frameR<27)) {
		if (r == 0) { // KIRI 
				mR = makeMatrixTranslasi(-1*(0.3*frameR+1),-0.5*(frameR+1));
			}
			else if (r == 1) { // KANAN
				mR = makeMatrixTranslasi((0.3*frameR+1),-0.5*(frameR+1));
			}
			else { // TENGAH
				mR = makeMatrixTranslasi(0,-0.5*(frameR+1));
			}
		transform(&midR,mR);
		radR1 += frame/9+1;
		radR2 = radR1*3/4;
		midR2 = makePoint(midR.x,midR.y-radR1+1);
		draw_circle(midR2.x,midR2.y, 1,YELLOW);
		draw_circle(midR.x,midR.y, radR1,61 /*EGA_LIGHTMAGENTA*/);
		draw_circle(midR.x,midR.y, radR2,61 /*EGA_LIGHTMAGENTA*/);
		floodFill(getmaxx()/2+midR.x-radR1+1,getmaxy()/2-midR.y,LIGHTGRAY,BLACK);
		if (frameR == 26) tempR = midR.x;
	}
	else if ((frameR >= 27) && (frameR < 45)) {
		mR = makeMatrixRotasi(10);
		m1R = makeMatrixTranslasi(-50-tempR,180);
		m2R = makeMatrixTranslasi(50+tempR,-180);
		mbR = makeMatrixRotasi(-10);
		mb1R = makeMatrixTranslasi(50-tempR,180);
		mb2R = makeMatrixTranslasi(-50+tempR,-180);
		if (midR.x < 0) { // DI KIRI LAYAR
			transform(&midR,mb1R);
			transform(&midR,mbR);
			transform(&midR,mb2R);
		}
		else {
			transform(&midR,m1R);
			transform(&midR,mR);
			transform(&midR,m2R);
		}
		if (midR.x < 0) { // DI KIRI LAYAR
			transform(&midR2,mb1R);
			transform(&midR2,mbR);
			transform(&midR2,mb2R);
		}
		else {
			transform(&midR2,m1R);
			transform(&midR2,mR);
			transform(&midR2,m2R);
		}
		draw_circle(midR2.x,midR2.y, 1,YELLOW);
		draw_circle(midR.x,midR.y, radR1,61 /*EGA_LIGHTMAGENTA*/);
		draw_circle(midR.x,midR.y, radR2,61 /*EGA_LIGHTMAGENTA*/);
		floodFill(getmaxx()/2+midR.x-radR1+1,getmaxy()/2-midR.y,LIGHTGRAY,BLACK);
	}
	else {
		mR = makeMatrixTranslasi(20,10);
		mbR = makeMatrixTranslasi(-20,10);
		if (midR.x < 0) { // DI KIRI LAYAR
			transform(&midR,mbR);
		}
		else if (midR.x > 0) {
			transform(&midR,mR);
		}
		else {
			if ((rand() % 2) == 0) {
				transform(&midR,mbR);
			}
			else {
				transform(&midR,mR);
			}
		}
		if (midR.x < 0) { // DI KIRI LAYAR
			transform(&midR2,mbR);
		}
		else if (midR.x > 0) {
			transform(&midR2,mR);
		}
		else {
			if ((rand() % 2) == 0) {
				transform(&midR2,mbR);
			}
			else {
				transform(&midR2,mR);
			}
		}
		draw_circle(midR2.x,midR2.y, 1,YELLOW);
		draw_circle(midR.x,midR.y, radR1,61 /*EGA_LIGHTMAGENTA*/);
		draw_circle(midR.x,midR.y, radR2,61 /*EGA_LIGHTMAGENTA*/);
		floodFill(getmaxx()/2+midR.x-radR1+1,getmaxy()/2-midR.y,LIGHTGRAY,BLACK);
	}
}
#endif