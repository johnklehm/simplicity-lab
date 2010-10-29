/* pong.c		1.2		20101028
 *
 * @author klehmc krewalk
 * @version 1.2
 * @date 20101028
 * @course cs3841-002
 *
 * Copyright 2010 klehmc krewalk
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
	while (!quit) {
		while (isPaused) { usleep(gameDelay); }

		static const uint8_t bufSize = 32;
        char timerBuf[bufSize];

		memset(timerBuf, 0, bufSize);
		snprintf(timerBuf, bufSize, "%i", ticks++ / (100000 / gameDelay));

		for (uint8_t i = bufSize - 1; i >= 0; --i) {
			if (timerBuf[i] != 0) {
				timerBuf[i + 1] = timerBuf[i];
				timerBuf[i] = '.';
				break;
			}
		}
		
		for (uint8_t i = 0; timerBuf[i] != 0 && i < bufSize; ++i) {
			drawChar(timerY, timerX + i, timerBuf[i]);
		}

		usleep(gameDelay);
	}

	return NULL;
}
