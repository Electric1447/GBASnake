#include "title.h"
#include "drawing.h"
#include <gba_input.h>


u8 state = TITLE_PLAYING;


int getTitleScreenState() {
	return state;
}

void beginTitleScreeen() {
	state = TITLE_PLAYING;
	drawTitleScreen();
}

void drawTitleScreen() {
	drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COL_GREEN);
	drawString(25, 25, "GBA SNAKE", COL_BLACK);
}

void handleTitleInput() {
	u16 key_down = keysDown();

	if (key_down & KEY_START)
		state = TITLE_END;
}
