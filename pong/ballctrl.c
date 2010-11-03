/* ballctrl.c		1.2		20101028
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
 * This file manages tthe motion of the ball.  This includes edge 
 * detections and scoring.
 */
#define BALLCTRL_C

#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "ballctrl.h"
#include "pong.h"

typedef enum scorer {PLAYER, COMPUTER} Scorer;

static float xactual;
static float yactual;
static float yadder;
static float xadder;

/**
 * Invoked when a ball collision is detected. It will fork a new child
 * process and play a beep sound. 
 */
void collision(Direction d) {
	pthread_mutex_lock(&stateLock);

	// fork and play beep (cmd line program)
	pid_t child = fork();
	if (child == 0) {
		// the child - play beep
		execlp("/bin/bash", "bash", "beep.sh", NULL);
		exit(EXIT_SUCCESS);
	}

	switch (d) {
	case X:
		xadder = -xadder;
	break;
	case Y:
		yadder = -yadder;
	break;
	default:
	break;
	}

	pthread_mutex_unlock(&stateLock);

	sched_yield();
	usleep(100000);
}

/**
 * Called when a goal is detected.
 *
 * @param p Whoe the score should get attributed to
 */
static void score(GameState* gs, Scorer p) {
	srand(time(NULL));
	// center the ball after a goal
	xactual = (gs->playFieldMax.x / 2) + rand() % 5;
	yactual = (gs->playFieldMax.y / 2) + rand() % 5;
	// reverse its direction
	xadder = -xadder;
	yadder = -yadder;

	pthread_mutex_lock(&stateLock);
	state.ballPos.x = xactual;
	state.ballPos.y = yactual;
	pthread_mutex_unlock(&stateLock);

	// fork and play sound
	pid_t child = fork();
	if (child == 0) {
		// the child - play beep
		execlp("/bin/bash", "bash", "horn.sh", NULL);
		exit(EXIT_SUCCESS);
	}

    switch (p) {
    case COMPUTER:
		++state.rightScore;
    break;
    case PLAYER:
		++state.leftScore;
    break;
    default:
    break;
    }

	sched_yield();
	usleep(state.ballDelay);
}

/**
 * This function is responsible for moving the ball within the game of pong.
 * It is spawned as a thread and ewill exit if and when quit is no longer true.
 *
 * @param vp This is a pointer to the parameters passed into the thread.  At
 * 				the present time, this parameter is not used.
 * @return This is the return value when the thread exits. Currently, it is
 * 				always NULL, as no data is directly returned by the thread.
 */
void* moveball(void* vp) {
	GameState gs;

	// these should be floating point to get slopes other than
	// +/- 45 degrees
	yadder = 1.0f;
	xadder = 1.0f;

	pthread_mutex_lock(&stateLock);
	xactual = state.ballPos.x;
	yactual = state.ballPos.y;
	pthread_mutex_unlock(&stateLock);

    while (!state.quit) {
		while (state.isPaused) { usleep(state.timerDelay); }

		getGameState(&gs);

		// erase old ball position
		drawChar(gs.ballPos.y, gs.ballPos.x, ' ' | A_NORMAL);

		yactual += yadder;
		xactual += xadder;
		
		pthread_mutex_lock(&stateLock);
		// truncate and update ball position
		state.ballPos.y = gs.ballPos.y = (int)(yactual);
		state.ballPos.x = gs.ballPos.x = (int)(xactual);
		pthread_mutex_unlock(&stateLock);

		drawChar(gs.ballPos.y, gs.ballPos.x, ' ' | A_REVERSE );

		// bottom boundary
		if (gs.ballPos.y >= gs.playFieldMax.y) {
			collision(Y);
		}
		// top boundry
		if (gs.ballPos.y <= gs.playFieldMin.y) {
			collision(Y);
		}
		// right boundary
		if (gs.ballPos.x >= gs.playFieldMax.x) {
			score(&gs, PLAYER);
		}
		// left boundary
		if (gs.ballPos.x <= gs.playFieldMin.x) {
			score(&gs, COMPUTER);
		}
		// right paddle
		if ((gs.ballPos.x == gs.rightPaddlePos.x - 1) &&
			(gs.ballPos.y <= gs.leftPaddlePos.y + gs.paddleHeight) &&
			(gs.ballPos.y >= gs.leftPaddlePos.y) ) {

			collision(X);
		}
		// left paddle
		if ((gs.ballPos.x == gs.leftPaddlePos.x + gs.paddleWidth) &&
			(gs.ballPos.y <= gs.leftPaddlePos.y + gs.paddleHeight) &&
			(gs.ballPos.y >= gs.leftPaddlePos.y) ) {

			collision(X);
		}

		sched_yield();
		// Do not want ball to move too fast...		
		usleep(gs.ballDelay);
	}

    return NULL;
}
