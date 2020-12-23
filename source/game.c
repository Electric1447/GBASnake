#include "game.h"
#include "snake.h"
#include "drawing.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#define gridStartX SIZE_FRAME
#define gridStartY SIZE_FRAME + SIZE_PADDING_TOP


u8 grid[NUM_CELLS_Y * NUM_CELLS_X];
u8 gameState, gameTick = 0;

Snake snake;
SnakeNode targetNode;


void spawnTargetNode();

u8 getCellValue(int x, int y) {
	return grid[y * NUM_CELLS_X + x];
}

void setCellValue(int x, int y, u8 value) {
	grid[y * NUM_CELLS_X + x] = value;
}

int getGameState() {
	return gameState;
}

int getFinalScore() {
	return snake.length;
}

void tickGame() {
	// Check for lose conditions
	if (snake.head.x > NUM_CELLS_X - 1 || snake.head.x < 0 || snake.head.y > NUM_CELLS_Y - 1 || snake.head.y < 0 ) {
		gameState = STATE_LOST;
		return;
	}

	// Check for win conditions
	if (snake.length == NUM_CELLS_Y * NUM_CELLS_X) {
		gameState = STATE_WON;
		return;
	}

	if (gameTick > GAME_SPEED)
		gameTick = 0;

	if (gameTick / GAME_SPEED)
		drawGame();

	gameTick++;
}

void drawGame() {
	if (snake.head.x == targetNode.x && snake.head.y == targetNode.y) {
		AddNode(&snake);
		spawnTargetNode();
	}

	// Clear the tail cell, it's the only part of the grid that needs to clear
	drawRect2(gridStartX + snake.tail->x * SIZE_CELL, gridStartY + snake.tail->y * SIZE_CELL, SIZE_CELL, SIZE_CELL, COL_BG);

	setCellValue(snake.tail->x, snake.tail->y, 0);

	if (snake.length > 1)
		drawRect2(gridStartX + snake.head.x * SIZE_CELL, gridStartY + snake.head.y * SIZE_CELL, SIZE_CELL, SIZE_CELL, COL_SNAKE);

	if (!UpdateSnake(&snake)) {
		gameState = STATE_LOST;
		return;
	}

	drawRect2(gridStartX + snake.head.x * SIZE_CELL, gridStartY + snake.head.y * SIZE_CELL, SIZE_CELL, SIZE_CELL, COL_SNAKE_HEAD);

	setCellValue(snake.head.x, snake.head.y, 1);

	// Score
	char score[5];
	sprintf(score, "%d", snake.length);
	drawRect2(4, 4, 24, 8, COL_BG);
	drawString(2, 2, score, COL_YELLOW);
}

void renderGame() {
	spawnTargetNode();
}

void restartGame() {
	gameState = STATE_PLAYING;
	gameState = 0;
	srand(time(NULL));
	memset(&grid[0], 0, sizeof(u8) * NUM_CELLS_Y * NUM_CELLS_X);

	int snakeStartX = NUM_CELLS_X / 2 - 1;
	int snakeStartY = NUM_CELLS_Y / 2 - 1;
	InitSnake(&snake, snakeStartX, snakeStartY, NUM_CELLS_Y * NUM_CELLS_X);

	drawRect2(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COL_BG); // Clear screen

	// Draw frame
	drawRect2(0,                         SIZE_PADDING_TOP, SCREEN_WIDTH, SIZE_FRAME,                       COL_FRAME);
	drawRect2(0,               SCREEN_HEIGHT - SIZE_FRAME, SCREEN_WIDTH, SIZE_FRAME,                       COL_FRAME);
	drawRect2(0,                         SIZE_PADDING_TOP, SIZE_FRAME,   SCREEN_HEIGHT - SIZE_PADDING_TOP, COL_FRAME);
	drawRect2(SCREEN_WIDTH - SIZE_FRAME, SIZE_PADDING_TOP, SIZE_FRAME,   SCREEN_HEIGHT - SIZE_PADDING_TOP, COL_FRAME);
	spawnTargetNode();
}

void spawnTargetNode() {
	int tX = -1, tY = -1, lastR = -1;

	for (int y = 0; y < NUM_CELLS_Y; ++y) for (int x = 0; x < NUM_CELLS_X; ++x) {
		u16 r = rand();
		if (grid[y * NUM_CELLS_X + x] != 1) if (tY == -1 || (r > lastR)) {
			tY = y;
			tX = x;
			lastR = r;
		}
	}

	targetNode.x = tX;
	targetNode.y = tY;

	drawRect2(gridStartX + tX * SIZE_CELL, gridStartY + tY * SIZE_CELL, SIZE_CELL, SIZE_CELL, COL_APPLE);
}

void handleGameInput() {
	u16 key_down = keysDown();

	if      (gameState == STATE_PLAYING && key_down & KEY_START) gameState = STATE_PAUSED;
	else if (gameState == STATE_PAUSED  && key_down & KEY_START) gameState = STATE_PLAYING;

	if (gameState == STATE_PAUSED)
		return;

	if      (key_down & KEY_RIGHT) UpdateVelocityX(&snake, SNAKE_RIGHT);
	else if (key_down & KEY_LEFT ) UpdateVelocityX(&snake, SNAKE_LEFT );

	if      (key_down & KEY_UP   ) UpdateVelocityY(&snake, SNAKE_UP   );
	else if (key_down & KEY_DOWN ) UpdateVelocityY(&snake, SNAKE_DOWN );
}
