/* score.c		1.2		20101028
 *
 * @author klehmc grewalk
 * @version 1.2
 * @date 20101101
 * @course cs3841-002
 *
 * Copyright 2010 klehmc grewalk
 *
 * This file manages the score throughout the game of pong
 */
#define SCORE_C

#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include "score.h"
#include "pong.h"

/**
 * Keeps track of and updates a score display for left and right paddles
 *
 * @param vp Generic parameter to pass information to this thread - unused
 * @return generic pointer to pass information from this thread - unused
 */
void* score(void* vp) {
	GameState gs;
	static const uint8_t bufSize = 5;
    char scoreBuf[bufSize];

	while (!state.quit) {
		while (state.isPaused) { usleep(state.timerDelay); }

		getGameState(&gs);

		memset(scoreBuf, 0, bufSize);
		snprintf(scoreBuf, bufSize, "%i", gs.leftScore);

		for (uint8_t i = 0; scoreBuf[i] != 0 && i < bufSize; ++i) {
			drawChar(gs.leftScorePos.y, gs.leftScorePos.x + i, scoreBuf[i]);
		}

		memset(scoreBuf, 0, bufSize);
		snprintf(scoreBuf, bufSize, "%i", gs.rightScore);
		
		for (uint8_t i = 0; scoreBuf[i] != 0 && i < bufSize; ++i) {
			drawChar(gs.rightScorePos.y, gs.rightScorePos.x + i, scoreBuf[i]);
		}

		sched_yield();
		usleep(state.timerDelay);
	}

	return NULL;
}
