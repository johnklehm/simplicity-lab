/* autoplay.c		1.2		20101101
 *
 * @author wws klehmc grewalk
 * @version 1.2
 * @date 20101101
 * @course cs3841-002
 *
 * Copyright 2010 klehmc grewalk
 *
 * This file manages the motion of the player's paddle.
 */
#define AUTOPLAY_C

#include <unistd.h>
#include "autoplay.h"
#include "pong.h"

/**
 * This function is responsible for moving the players paddle. It is spawned as
 * a thread and ewill exit if and when quit is no longer true.
 * @param vp This is a pointer to the parameters passed into the thread.  At the
 * 				present time, this parameter is not used.
 * @return This is the return value when the thread exits. Currently, it is
 * 			always NULL, as no data is directly returned by the thread.
 */
void* moveplayer(void* vp) {
	GameState gs;

	while (!state.quit) {
		// sleep if we're paused or if autoplay is off
		while (state.isPaused ||
			(!state.isPaused && !state.autoPlayEnabled && !state.quit)) {
			usleep(state.timerDelay);
		}

		getGameState(&gs);

		// when ball is above the paddle
		if (gs.ballPos.y <= (gs.leftPaddlePos.y + (gs.paddleHeight / 2))) {
			--gs.leftPaddlePos.y;

			if (gs.leftPaddlePos.y < gs.playFieldMin.y) {
				gs.leftPaddlePos.y = gs.playFieldMin.y;
			}

			state.leftPaddlePos.y = gs.leftPaddlePos.y;

			drawChar(gs.leftPaddlePos.y, gs.leftPaddlePos.x, ' ' | A_REVERSE);
			drawChar(gs.leftPaddlePos.y + gs.paddleHeight, gs.leftPaddlePos.x, ' ' | A_NORMAL);

			// wait a bit after we  move
			usleep(gs.leftPaddleDelay);

		// when ball is below the paddle
		} else if (gs.ballPos.y > (gs.leftPaddlePos.y + (gs.paddleHeight / 2))) {
			++gs.leftPaddlePos.y;

			if (gs.leftPaddlePos.y > (gs.playFieldMax.y - gs.paddleHeight)) {
				gs.leftPaddlePos.y = (gs.playFieldMax.y - gs.paddleHeight);
			}

			state.leftPaddlePos.y = gs.leftPaddlePos.y;

			drawChar(gs.leftPaddlePos.y - 1, gs.leftPaddlePos.x, ' ' | A_NORMAL);
			drawChar(gs.leftPaddlePos.y + gs.paddleHeight - 1, gs.leftPaddlePos.x, ' ' | A_REVERSE);

			// wait a bit after we  move
			usleep(gs.leftPaddleDelay);
		}

		// give other threads a turn
		sched_yield();
	}

	return NULL;
}
