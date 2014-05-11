/*** Tugas Pengganti UTS GRAFIKA - KARS 3 GAME, PIJAR Inc. ***/
#include "headergame.c"

//Deklarasi variabel global
Point carpos; //posisi mobil
int itime; //waktu permainan dalam detik
bool win; //kondisi menang
time_t curtime; //untuk perhitungan detik
char stime[3],sscore[3]; //text score dan waktu permainan

//render atau gambar ulang objek dalam game
void render(){
	int x,y;
	for(y=getmaxy()/2;y<getmaxy();y++){
		for(x=0;x<getmaxx();x++){
			if(getpixel(x,y)!=0){
				putpixel(x,y,0);
			}
		}
	}
	settextstyle(0, HORIZ_DIR, 10);
	outtextxy(50,getmaxy()/2+10,"Time: ");
	outtextxy(90,getmaxy()/2+10,stime);
	outtextxy(55,getmaxy()/2+30,"Score: ");
	outtextxy(95,getmaxy()/2+30,sscore);
}
//update objek dalam game
void update(){
	spawnRodaUpdate();
	spawnRockUpdate();
	spawnKotakUpdate();	
	drawRoad();
	roadLineNext();
	drawCar(carpos.x,carpos.y);
}
//menggambar objek awal game
void startDraw(){
	setcolor(15);
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	outtextxy(getmaxx()/2,0,"Kars 3 - Arcade Game from PIJAR inc.");
	outtextxy(getmaxx()/2,10,"Tekan tombol arrow kiri atau kanan untuk menggerakan mobil");
	outtextxy(getmaxx()/2,20,"Tekan tombol ESC untuk keluar dari permainan");
	drawLineBresenham(-getmaxx()/2,getmaxy()/2-32,getmaxx()/2,getmaxy()/2-32,12);
	drawMountain();
	drawSun();
	drawClouds();
	drawBird();
	floodFill(10,35,3,0);
}
//untuk menggerakan mobil
int movecar(){
	MatrixTrans m;
	int key = anykeypressed();
	if(key!=0){
		key = readkey();
		//jika tombol arraow ditekan
		if(key==0){
			key = readkey();
			if(key==75){
				//printf("Tombol kiri ditekan!");
				if(carpos.x-20>=-270){
					m = makeMatrixTranslasi(-20,0);
					transform(&carpos, m);
				}
			}else if(key==77){
				//printf("Tombol kanan ditekan!");
				if(carpos.x+20<=270){
					m = makeMatrixTranslasi(20,0);
					transform(&carpos, m);
				}
			}
			//render();
		}
	}
	return key;
}
//untuk mengecek terjadinya tabrakan antara mobil dan obstacle
int detectCollision(){
	if((mid.x<carpos.x+50 && mid.x>carpos.x-50 && mid.y<carpos.y+45)||(midK.x<carpos.x+50 && midK.x>carpos.x-50 && midK.y<carpos.y+45)){
		return 1;
	}else{
		return 0;
	}
}
//Gameloop!
void gameloop(){
	int statuskey;
	do{
		statuskey = movecar(); //cek jika tombol ditekan
		if((double)time(NULL)-(double)curtime>=1){
			curtime = time(NULL);
			itime--;
			itoa(itime,stime,10);
		}
		itoa(score,sscore,10);
		render();
		update();
		if(statuskey==75 || statuskey==77){
			Beep(523.251,ANIMATION_DELAY);
		}else{
			delay(ANIMATION_DELAY);
		}
		if(detectCollision()!=0){
			statuskey = KEY_ESCAPE;
			win = false;
		}
		if(itime==0){
			statuskey = KEY_ESCAPE;
			win = true;
		}
    } while(statuskey != KEY_ESCAPE);
}
//musik intro
void introSound(){
	Beep(523.251,100);
	Beep(493.883,100);
	Beep(523.251,100);
	Beep(440,500);
	Beep(440,500);
	Beep(493.883,500);
	Beep(587.330,500);
	Beep(659.255,800);
}
//main function
void main(){
	//inisialisasi
	srand(time(NULL));
	int gd = DETECT, gm, command,i,r;
	initgraph(&gd, &gm, "");
	itime = 30;
	curtime = time(NULL);
	win = false;
	carpos = makePoint(0,-190);
	//Game dimulai
	startDraw();
	introSound();
	gameloop();
	//game selesai, cek kondisi menang
	if(!win){ //kalah
		cleardevice();
		printLose();
		Beep(523.251,500);
		Beep(493.883,500);
		Beep(466.164,500);
		Beep(440,2000);
		readkey();
	}else{ //menang
		cleardevice();
		printWin();
		Beep(523.251,200);
		Beep(523.251,1000);
		readkey();
	}
	closegraph(); //finalisasi
}