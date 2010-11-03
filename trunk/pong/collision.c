/* collision.c		1.2		20101028
 * 
 * @author wws klehmc grewalk
 * @version 1.2
 * @date 20101102
 * @course cs3841-002
 *
 * This file was developed as part of CS3841 Design of Operating Systems at the 
 * Milwaukee School of Engineering.  This file is copyright 2008-2009 by MSOE.
 *
 * Copyright 2010 klehmc grewalk 
 *
 * This file manages the collision detection of the ball with other objects
 */
#define COLLISION_C

#include <stdlib.h>
#include <unistd.h>
#include "collision.h"
#include "ballctrl.h"
#include "pong.h"

/**
 * Checks the location of objects in the game and triggers a collision if so.
 *
 * @param vp This is a pointer to the parameters passed into the thread.  At
 * 				the present time, this parameter is not used.
 * @return This is the return value when the thread exits. Currently, it is
 * 				always NULL, as no data is directly returned by the thread.
 */
void* checkcollision(void* vp) {
	GameState gs;

    while (!state.quit) {
		while (state.isPaused) { usleep(state.timerDelay); }

		getGameState(&gs);

		// right paddle
		if ((gs.ballPos.x == gs.rightPaddlePos.x - 1) &&
			(gs.ballPos.y <= gs.rightPaddlePos.y + gs.paddleHeight) &&
			(gs.ballPos.y >= gs.rightPaddlePos.y) ) {

			collision(X);
		}
		// left paddle
		if ((gs.ballPos.x == gs.leftPaddlePos.x + gs.paddleWidth - 1) &&
			(gs.ballPos.y <= gs.leftPaddlePos.y + gs.paddleHeight) &&
			(gs.ballPos.y >= gs.leftPaddlePos.y) ) {

			collision(X);
		}
	
		// come up for air
		sched_yield();
	}

    return NULL;
}
