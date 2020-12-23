#pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"


#include "drawing.h"
#include "font.h"
#include <stdio.h>


void drawRect(int x1, int y1, int x2, int y2, u16 clr) {
	drawRect2(x1, y1, x2 - x1, y2 - y1, clr);
}

void drawRect2(int x1, int y1, int width, int height, u16 clr) {
	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x)
			drawPixel(x1 + x, y1 + y, clr);
}

void drawString(int x, int y, char* msg, u16 clr) {
	int curr_char = *msg++;
	u16* dst = &vid_mem[y * SCREEN_WIDTH + x];

	while (curr_char != '\0') {
		if (curr_char == '\n') { // Line break
			dst += SCREEN_WIDTH * 8;
			x = 0;
		} else { // Normal character

			u32 row; // (3) point to glyph; each row is one byte

			u8* glyphBytes = (u8*)&fontTiles[2 * (curr_char - 32)];

			for (int iy = 0; iy < 8; iy++) {
				row = glyphBytes[iy];

				for (int ix = x; row > 0; row >>= 1, ix++)
					if (row & 1)
						dst[(y + iy) * SCREEN_WIDTH + (x + ix)] = clr;
			}
			x += 4; // 4 = width of glyph in nibbles?
		}

		curr_char = *msg++;
	}
}
