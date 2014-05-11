//Kumpulan prosedur untuk membuat musik dalam game
#include <stdio.h>

#if !(WIN32)
#define Beep(x,y) delay(y)
#endif
#if (WIN32)
#include <windows.h>
#include <conio.h>
#endif

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
//musik kalo kalah
void loseSound(){
	Beep(523.251,500);
	Beep(493.883,500);
	Beep(466.164,500);
	Beep(440,2000);
}
//musik kalo menang
void winSound(){
	Beep(523.251,200);
	Beep(523.251,1000);
}