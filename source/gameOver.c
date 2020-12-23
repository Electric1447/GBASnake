#include "gameOver.h"
#include "drawing.h"
#include <gba_input.h>


static int state = END_PLAYING;
static int result = 0;


void SetMatchResult(int didPlayerWin) {
    result = didPlayerWin;
}

void beginGameOverScreen() {
    state = END_PLAYING;

    if (result) {
        drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COL_BLACK);
        drawString(25, 25, "You Won!", COL_GREEN);
        drawString(11, 35, "Press Start To Play Again ", COL_GREEN);
    } else {
        drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COL_RED);
        drawString(25, 25, "You Lost", COL_BLACK);
        drawString(13, 35, "Press Start To Retry ", COL_BLACK);
    }
}

void handleGameOverInput() {
	u16 key_down = keysDown();
	
	if (key_down & KEY_START)
		state = END_RESTART;
}

int getGameOverState() {
    return state;
}
