#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include "transform.c"
#include "line-bresenham.c"
#include "areafill.c"
#include "circle.c"
#include "ellipse.c"
#include "polygon.c"
#include "drawable-manager.c"
#include "Obstacle.c"
#include "finalscreen.c"

#if !(WIN32)
#define Beep(x,y)
#endif
#if (WIN32)
#include <windows.h>
#endif

#define ANIMATION_DELAY 50