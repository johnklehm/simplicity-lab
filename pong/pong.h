/* pong.h		1.2		20101028
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

EXTERN_PFX uint16_t ballx;			//coordinates of the ball
EXTERN_PFX uint16_t bally;
EXTERN_PFX WINDOW *win; 			// the curses window
EXTERN_PFX bool quit;				// flag to stop all threads
EXTERN_PFX bool isPaused;			// flag to pause all threads
EXTERN_PFX bool autoPlayEnabled;	// flag to enable the auto play thread
EXTERN_PFX uint16_t maxx;			// max raw terminal size
EXTERN_PFX uint16_t maxy;
EXTERN_PFX uint16_t playFieldMaxX;	// coordinates of the play area
EXTERN_PFX uint16_t playFieldMaxY;
EXTERN_PFX uint16_t playFieldMinX;
EXTERN_PFX uint16_t playFieldMinY;
EXTERN_PFX uint16_t timerX;			// coordinates of the timer
EXTERN_PFX uint16_t timerY;
EXTERN_PFX uint16_t lScoreX;
EXTERN_PFX uint16_t lScoreY;
EXTERN_PFX uint16_t rScoreX;
EXTERN_PFX uint16_t rScoreY;
EXTERN_PFX uint16_t leftPaddleX;
EXTERN_PFX uint16_t leftPaddleY;
EXTERN_PFX uint16_t rightPaddleX;
EXTERN_PFX uint16_t rightPaddleY;
EXTERN_PFX uint32_t gameDelay;		// time to delay the game in microseconds
EXTERN_PFX uint32_t ticks;			// total ticks of the timer. fluxuates with the delay
EXTERN_PFX uint8_t leftScore;
EXTERN_PFX uint8_t rightScore;
EXTERN_PFX uint8_t paddleHeight;
EXTERN_PFX uint8_t paddleWidth;
EXTERN_PFX pthread_mutex_t ticksLock;
EXTERN_PFX pthread_mutex_t screenLock;

EXTERN_PFX void drawChar(uint16_t y, uint16_t x, chtype c);

#undef EXTERN_PFX
#endif
