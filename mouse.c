// FILE: bgimdemo.cpp
// Written by: Michael Main (main@colorado.edu) -- Oct 17, 1998
// A small demonstration program using Borland's BGI.
// This version has been modified to use the winbgim library that runs
// under Borland C++ 5.02 for Windows instead of the usual BGI files.
// This version also has a modification to wait for a mouse click at
// the end.

#include "winbgim.h"  // Provides the BGI graphics functions for Windows
#include <stdio.h>
#include "Areafill.c"
#include "circle.c"
// The click_handler will be called whenever the left mouse button is
// clicked. It checks copies the x,y coordinates of the click to
// see if the click was on a red pixel. If so, then the boolean
// variable red_clicked is set to true. Note that in general
// all handlers should be quick. If they need to do more than a little
// work, they should set a variable that will trigger the work going,
// and then return.
bool isClicked = false;
void click_handler(int x, int y){ isClicked = true; }
void release_handler(int x, int y){ isClicked = false; }

void Pause(void)
{
	int c;
	c = getch();                          /* Read a character from kbd    */
	if( 27 == c ){                       /* Does user wish to leave?     */
		closegraph();                       /* Change to text mode          */
		exit( 1 );                          /* Return to OS                 */
	}
	if( 0 == c ){                         /* Did use hit a non-ASCII key? */
		c = getch();                        /* Read scan code for keyboard  */
	}
	cleardevice();                        /* Clear the screen             */
}

int main()
{
    int maxx, maxy;  // Maximum x and y pixel coordinates
    // Put the machine into graphics mode and get the maximum coordinates:
    initwindow(700, 500);         
    maxx = getmaxx();
    maxy = getmaxy();
	int mx,my;
    // Register the function that handles a left mouse click
    registermousehandler(WM_LBUTTONDOWN, click_handler);
    registermousehandler(WM_LBUTTONUP, release_handler);
    // Draw a white circle with red inside and a radius of 50 pixels:
    draw_circle(320,220,20,RED);
    //bool isClose = false;
    while (1){
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,mx,my);
			if(getpixel(mx,my) == RED) break;
		}
	} 
	//printf("%d,%d\n",mousex(),mousey());
    // Switch back to text mode:
    closegraph( );
	return 0;
}
