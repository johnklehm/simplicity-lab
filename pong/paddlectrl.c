/* paddlectrl.c			1.2			20101028
 *
 * @author wws klehmc krewalk
 * @version 1.2
 * @date 20101028
 * @course cs3841-002
 *
 * This file was developed as part of CS3841 Design of Operating Systems at the 
 * Milwaukee School of Engineering.  This file is copyright 2008-2009 by MSOE.
 * 
 * Copyright 2010 klehmc krewalk
 *
 * This file manages the motion of the users paddle.  It is responsible for 
 * reading commands from the keyboard and processing them appropriately.
 *
 */
#define PADDLECTRL_C

#include <unistd.h>
#include <curses.h>
#include <stdint.h>
#include "pong.h"

static const uint8_t paddleSize = 5;

/**
 * Changes the game delay and adjust the tick count in a thread safe manner
 *
 * @param newDelay The new value to delay the game by in microseconds.
 */
void setDelay(uint32_t newDelay) {
	pthread_mutex_lock(&ticksLock);
	// floating point cast so we can get a fraction
	ticks = ticks * ((float)gameDelay / newDelay);
	gameDelay = newDelay;
	pthread_mutex_unlock(&ticksLock);
}

/**
 * Moves the players paddle according to keyboard input
 *
 * @param vp Generic parameter to pass information to this thread - unused
 * @return generic pointer to pass information from this thread - unused
 */
void* moveme(void* vp) {
	int ch;
	uint16_t vpos = playFieldMinY;

	// draw the default paddle
	for (uint8_t i = 0; i < paddleSize; ++i) {
		drawChar(playFieldMinY + i, playFieldMinX, ' ' | A_REVERSE);
	}

	while (!quit) {
		ch = getch();

		switch (ch) {
		case KEY_UP:
			--vpos;

			if (vpos < playFieldMinY) {
	            vpos = playFieldMinY;
            }

			drawChar(vpos, 0, ' ' | A_REVERSE);
			drawChar(vpos + paddleSize, 0, ' ' | A_NORMAL);

			break;
		case KEY_DOWN:
			++vpos;

 			if (vpos > (playFieldMaxY - paddleSize)) {
				vpos = (playFieldMaxY - paddleSize);
			}

			drawChar(vpos - 1, 0, ' ' | A_NORMAL);
			drawChar(vpos + paddleSize - 1, 0, ' ' | A_REVERSE);

			break;
		// pause
		case 'p':
			isPaused = true;

			while (isPaused) {
				usleep(gameDelay);

				if (getch() == 'p') {
					isPaused = false;
				}
			}

			break;
		// quit
		case 'q':
			quit=true;

			break;
		// game speed slow
		case '1':
			setDelay(100000);

			break;
		// game speed med
		case '2':
			setDelay(50000);

			break;
		// game speed fast
		case '3':
			setDelay(25000);

			break;
		// game speed insane
		case '4':
			setDelay(10000);

			break;
		default:
			break;
		}
	}

	return NULL;
}
