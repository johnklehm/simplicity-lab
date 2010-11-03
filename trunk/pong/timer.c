/* timer.c		1.2		20101028
 *
 * @author klehmc grewalk
 * @version 1.2
 * @date 20101028
 * @course cs3841-002
 *
 * Copyright 2010 klehmc grewalk
 *
 * This file manages the timer throughout the game of pong
 */
#define TIMER_C

#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include "timer.h"
#include "pong.h"

/**
 * Keeps track of and updates a timer display
 *
 * @param vp Generic parameter to pass information to this thread - unused
 * @return generic pointer to pass information from this thread - unused
 */
void* timer(void* vp) {
	GameState gs;
	static const uint8_t bufSize = 8;
    char timerBuf[bufSize];

	while (!state.quit) {
		while (state.isPaused) { usleep(state.timerDelay); }

		getGameState(&gs);

		memset(timerBuf, 0, bufSize);
		snprintf(timerBuf, bufSize, "%i", gs.ticks);

		// add the decimal for tenths of a second e.g. 13.5 seconds
		for (uint8_t i = bufSize - 1; i >= 0; --i) {
			if (timerBuf[i] != 0) {
				timerBuf[i + 1] = timerBuf[i];
				timerBuf[i] = '.';
				break;
			}
		}
		
		for (uint8_t i = 0; timerBuf[i] != 0 && i < bufSize; ++i) {
			drawChar(gs.timerPos.y, gs.timerPos.x + i, timerBuf[i]);
		}

		++state.ticks;

		usleep(gs.timerDelay);
	}

	return NULL;
}
