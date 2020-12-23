#ifndef GAME_H
#define GAME_H


#include <gba_input.h>


#define NUM_CELLS_X      28
#define NUM_CELLS_Y      16
#define SIZE_CELL        8
#define SIZE_FRAME       8
#define SIZE_PADDING_TOP 16
#define GAME_SPEED       6

#define STATE_PLAYING    0
#define STATE_WON        1
#define STATE_LOST       2
#define STATE_PAUSED     3


int getGameState();
int getFinalScore();
void tickGame();
void drawGame();
void restartGame();

void handleGameInput();

u8 getCellValue(int x, int y);
void setCellValue(int x, int y, u8 value);


#endif
