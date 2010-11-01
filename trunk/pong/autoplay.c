/* autoplay.c		1.2		20101101
 *
 * @author wws klehmc krewalk
 * @version 1.2
 * @date 20101101
 * @course cs3841-002
 *
 * Copyright 2010 klehmc krewalk
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
	while (!quit) {
		// sleep if we're paused or if autoplay is off
		while (isPaused || (!isPaused && !autoPlayEnabled && !quit)) {
			usleep(gameDelay);
		}

		// when ball is above the paddle
		if (bally <= (leftPaddleY + (paddleHeight / 2))) {
			--leftPaddleY;

			if (leftPaddleY < playFieldMinY) {
				leftPaddleY = playFieldMinY;
			}

			drawChar(leftPaddleY, leftPaddleX, ' ' | A_REVERSE);
			drawChar(leftPaddleY + paddleHeight, leftPaddleX, ' ' | A_NORMAL);

		// when ball is below the paddle
		} else if (bally > (leftPaddleY + (paddleHeight / 2))) {
			++leftPaddleY;

			if (leftPaddleY > (playFieldMaxY - paddleHeight)) {
				leftPaddleY = (playFieldMaxY - paddleHeight);
			}

			drawChar(leftPaddleY - 1, leftPaddleX, ' ' | A_NORMAL);
			drawChar(leftPaddleY + paddleHeight - 1, leftPaddleX, ' ' | A_REVERSE);
		}

		usleep(gameDelay);
	}

	return NULL;
}
