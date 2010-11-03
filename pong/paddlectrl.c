/* paddlectrl.c			1.2			20101028
 *
 * @author wws klehmc grewalk
 * @version 1.2
 * @date 20101028
 * @course cs3841-002
 *
 * This file was developed as part of CS3841 Design of Operating Systems at the 
 * Milwaukee School of Engineering.  This file is copyright 2008-2009 by MSOE.
 * 
 * Copyright 2010 klehmc grewalk
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

/**
 * Moves the players paddle according to keyboard input
 *
 * @param vp Generic parameter to pass information to this thread - unused
 * @return generic pointer to pass information from this thread - unused
 */
void* moveme(void* vp) {
	GameState gs;
	int ch;

	pthread_mutex_lock(&stateLock);
	// draw the default paddle
	for (uint8_t i = 0; i < state.paddleHeight; ++i) {
		drawChar(state.leftPaddlePos.y + i, state.leftPaddlePos.x, ' ' | A_REVERSE);
	}
	pthread_mutex_unlock(&stateLock);

	while (!state.quit) {
		getGameState(&gs);
		
		pthread_mutex_lock(&keyboardLock);
		ch = getch();
		pthread_mutex_unlock(&keyboardLock);

		switch (ch) {
		case KEY_UP:
			--gs.leftPaddlePos.y;

			if (gs.leftPaddlePos.y < gs.playFieldMin.y) {
	            gs.leftPaddlePos.y = gs.playFieldMin.y;
            }

			// update global pos
			state.leftPaddlePos.y = gs.leftPaddlePos.y;

			drawChar(gs.leftPaddlePos.y, 0, ' ' | A_REVERSE);
			drawChar(gs.leftPaddlePos.y + gs.paddleHeight, 0, ' ' | A_NORMAL);

			usleep(gs.leftPaddleDelay);

			break;
		case KEY_DOWN:
			++gs.leftPaddlePos.y;

 			if (gs.leftPaddlePos.y > (gs.playFieldMax.y - gs.paddleHeight)) {
				gs.leftPaddlePos.y = (gs.playFieldMax.y - gs.paddleHeight);
			}

			// update global pos
			state.leftPaddlePos.y = gs.leftPaddlePos.y;

			drawChar(gs.leftPaddlePos.y - 1, 0, ' ' | A_NORMAL);
			drawChar(gs.leftPaddlePos.y + gs.paddleHeight - 1, 0, ' ' | A_REVERSE);

			usleep(gs.leftPaddleDelay);

			break;
		// pause
		case 'p':
			state.isPaused = true;

			while (state.isPaused) {
				usleep(state.timerDelay);

				if (getch() == 'p') {
					state.isPaused = false;
				}
			}

			break;
		// autoplay
		case 'a':
			state.autoPlayEnabled = (state.autoPlayEnabled)? false : true;

			break;
		// quit
		case 'q':
			state.quit = true;

			break;
		// game speed slow
		case '1':
			state.ballDelay = 100000;
			state.rightPaddleDelay = 125000;

			break;
		// game speed med
		case '2':
			state.ballDelay = 50000;
			state.rightPaddleDelay = 50000;

			break;
		// game speed fast
		case '3':
			state.ballDelay = 25000;
			state.rightPaddleDelay = 10000;

			break;
		// game speed insane
		case '4':
			state.ballDelay = 10000;
			state.rightPaddleDelay = 1000;

			break;
		default:
			break;
		}

		sched_yield();
	}

	return NULL;
}
