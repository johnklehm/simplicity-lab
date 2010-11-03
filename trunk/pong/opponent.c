/* opponent.c		1.2		20101028
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
 * This file manages tthe motion of the oponent's paddle.
 */
#define OPPONENT_C

#include <unistd.h>
#include "opponent.h"
#include "pong.h"

/**
 * This function is responsible for moving the oponents paddle. It is spawned as
 * a thread and ewill exit if and when quit is no longer true.
 * @param vp This is a pointer to the parameters passed into the thread.  At the
 * 				present time, this parameter is not used.
 * @return This is the return value when the thread exits. Currently, it is
 * 			always NULL, as no data is directly returned by the thread.
 */
void* moveopponent(void* vp) {
	GameState gs;

	pthread_mutex_lock(&stateLock);
	// draws the computer's paddle
	for (uint8_t i = 0; i < state.paddleHeight; ++i) {
		drawChar(state.rightPaddlePos.y + i, state.rightPaddlePos.x, ' ' | A_REVERSE);
	}
	pthread_mutex_unlock(&stateLock);

	while (!state.quit) {
		while (state.isPaused) { usleep(state.timerDelay); }

		getGameState(&gs);

		// when ball is above the paddle
		if (gs.ballPos.y <= (gs.rightPaddlePos.y + (gs.paddleHeight / 2))) {
			--gs.rightPaddlePos.y;

			if (gs.rightPaddlePos.y < gs.playFieldMin.y) {
				gs.rightPaddlePos.y = gs.playFieldMin.y;
			}

			state.rightPaddlePos.y = gs.rightPaddlePos.y;

			drawChar(gs.rightPaddlePos.y, gs.rightPaddlePos.x, ' ' | A_REVERSE);
			drawChar(gs.rightPaddlePos.y + gs.paddleHeight, gs.rightPaddlePos.x, ' ' | A_NORMAL);

			usleep(gs.rightPaddleDelay);

		// when ball is below the paddle
		} else if (gs.ballPos.y > (gs.rightPaddlePos.y + (gs.paddleHeight / 2))) {
			++gs.rightPaddlePos.y;

			if (gs.rightPaddlePos.y > (gs.playFieldMax.y - gs.paddleHeight)) {
				gs.rightPaddlePos.y = (gs.playFieldMax.y - gs.paddleHeight);
			}

			state.rightPaddlePos.y = gs.rightPaddlePos.y;

			drawChar(gs.rightPaddlePos.y - 1, gs.rightPaddlePos.x, ' ' | A_NORMAL);
			drawChar(gs.rightPaddlePos.y + gs.paddleHeight - 1, gs.rightPaddlePos.x, ' ' | A_REVERSE);

			usleep(gs.rightPaddleDelay);
		}

		sched_yield();
	}

	return NULL;
}
