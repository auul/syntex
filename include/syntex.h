#ifndef SYNTEX_H
#define SYNTEX_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SplitRGB(rgb) rgb >> 16, (rgb >> 8) & 0xff, rgb & 0xff
#define SplitRGBA(rgba) rgba >> 16, (rgba >> 8) & 0xff, rgba & 0xff, 0xff

// Window

#define WIN_INIT_TITLE "S y n t e x"
#define WIN_INIT_WIDTH 640
#define WIN_INIT_HEIGHT 480
#define WIN_BG_RGB 0x333333

bool WinInit(void);
bool WinExit(void);
void WinLoop(void);

#endif
