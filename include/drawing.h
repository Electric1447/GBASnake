#ifndef DRAWING_H
#define DRAWING_H


#include <gba_video.h>


#define vid_mem ((vu16*)(0x06000000))

#define COL_BLACK       RGB8(  0,   0,   0)
#define COL_WHITE       RGB8(255, 255, 255)
#define COL_RED         RGB8(255,   0,   0)
#define COL_GREEN       RGB8(  0, 255,   0)
#define COL_BLUE        RGB8(  0,   0, 255)
#define COL_CYAN        RGB8(  0, 255, 255)
#define COL_PINK        RGB8(255,   0, 255)
#define COL_YELLOW      RGB8(255, 255,   0)

#define COL_BG          RGB8(153, 204, 255)
#define COL_FRAME       RGB8( 51, 153, 255)
#define COL_SNAKE       RGB8( 48,  98,  48)
#define COL_SNAKE_HEAD  RGB8( 15,  56,  15)
#define COL_APPLE       COL_RED


inline void drawPixel (int x, int y, u16 clr) {
	vid_mem[y * SCREEN_WIDTH + x] = clr;
}

void drawRect(int x1, int y1, int x2, int y2, u16 clr);
void drawRect2(int x1, int y1, int width, int height, u16 clr);
void drawString(int x, int y, char* msg, u16 clr);


#endif
