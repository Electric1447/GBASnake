#include <gba.h>
#include "game.h"
#include "title.h"
#include "gameOver.h"


#define STATE_TITLE         0
#define STATE_GAME          1
#define STATE_END           2


u8 AppState = STATE_TITLE;


int main() {
    irqInit();
	irqEnable(IRQ_VBLANK);
	
    REG_DISPCNT = MODE_3 | BG2_ENABLE;
	REG_IME = 1;				

	beginTitleScreeen();

	while (1) {
		VBlankIntrWait();
		scanKeys();
		
		switch (AppState) {
			case STATE_TITLE:
				handleTitleInput();
				
				if (getTitleScreenState() == TITLE_END) {
					restartGame();
					AppState = STATE_GAME;
				}
				break;
			case STATE_GAME:
				handleGameInput();
				
				if (getGameState() == STATE_PAUSED)
					break;
					
				if (getGameState() == STATE_PLAYING) {
					tickGame();
				} else {
					beginGameOverScreen();
					AppState = STATE_END;
				}
				break;
			case STATE_END:
				handleGameOverInput();
				
				if (getGameOverState() == END_RESTART) {
					restartGame();
					AppState = STATE_GAME;
				}
				break;
		}
	}

    return 0;
}
