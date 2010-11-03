/* pong.h		1.2		20101028
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
 */
#ifndef PONG_H
#define PONG_H

#ifdef PONG_C
#define EXTERN_PFX 
#else
#define EXTERN_PFX extern
#endif

#include <curses.h>
#include <pthread.h>
#include <stdint.h>

typedef struct point {
	uint16_t x;
	uint16_t y;
} Point;

typedef struct gameState {
	bool quit;				// flag to stop all threads
	bool isPaused;			// flag to pause all threads
	bool autoPlayEnabled;	// flag to enable the auto play thread
	Point screenMax;		// max terminal size
	Point playFieldMin;		// play area
	Point playFieldMax;
	Point timerPos;
	Point ballPos;
	Point leftScorePos;
	Point rightScorePos;
	Point leftPaddlePos;
	Point rightPaddlePos;
	uint32_t ballDelay;
	uint32_t rightPaddleDelay;
	uint32_t leftPaddleDelay;
	uint32_t timerDelay;
	uint32_t collisionDelay;
	uint32_t ticks;
	uint8_t leftScore;
	uint8_t rightScore;
	uint8_t paddleHeight;
	uint8_t paddleWidth;
} GameState;

EXTERN_PFX WINDOW* win; 			// the curses window
EXTERN_PFX GameState state;			// the game state

EXTERN_PFX pthread_mutex_t stateLock;
EXTERN_PFX pthread_mutex_t screenLock;
EXTERN_PFX pthread_mutex_t keyboardLock;

EXTERN_PFX void drawChar(uint16_t y, uint16_t x, chtype c);
EXTERN_PFX void getGameState(GameState* gs);

#undef EXTERN_PFX
#endif
