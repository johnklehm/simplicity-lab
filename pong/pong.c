/* pong.c		1.2		20101028
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
 * This file manages serves as the main program for the pong game.
 * It is responsible for spawning all other threads and managing the overall 
 * behavior of the game.  All global variables are owned by this file.
 */
#define PONG_C

#include <stdlib.h>
#include <curses.h>
#include <sys/types.h>
#include <unistd.h>

#include "pong.h"
#include "paddlectrl.h"
#include "ballctrl.h"
#include "opponent.h"
#include "timer.h"
#include "score.h"
#include "autoplay.h"
#include "collision.h"

/**
 * Draws a character to the screen. Thread safe.
 *
 * @param y Y coordinate of the draw position
 * @param x X coordinate of the draw position
 * @param c The character to draw
 */
void drawChar(uint16_t y, uint16_t x, chtype c) {
	pthread_mutex_lock(&screenLock);
	mvaddch(y, x, c);
	pthread_mutex_unlock(&screenLock);
}

/**
 * Allocates a copy of the game's state.
 *
 * @param gs A location to store a copy of the game's state
 */
void getGameState(GameState* gs) {
	if (gs) {
		pthread_mutex_lock(&stateLock);
		// don't have to use memcopy since no pointers in the stuct
		*gs = state;
		pthread_mutex_unlock(&stateLock);
	}
}

/**
 * This function is responsible for moving the users paddle. It is spawned as a
 * thread and ewill exit if and when quit is no longer true.
 *
 * @param argc This is a count of the number of command line parameters passed
 *				by the operating system.
 * @param argv This is the array of strings which is passed to program.
 * @return EXIT_SUCESS (0) will be returned upon normal exiting of the program.
 *			A negative value will indicate an error.
 */
int main(int argc, char* argv[]) {
	pthread_mutex_init(&screenLock, NULL);
	pthread_mutex_init(&stateLock, NULL);
	pthread_mutex_init(&keyboardLock, NULL);

	// init window - see curses documentation for guidance
	win = initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(win, TRUE);
	nodelay(win, TRUE);
	refresh();
	// get the extents of the screen
	getmaxyx(win, state.screenMax.y, state.screenMax.x);

	// Initialize all of the variables.
	// Global data - for inter-thread communication
	state.playFieldMin.x = 0;
	state.playFieldMax.x = state.screenMax.x;
	state.playFieldMin.y = 2; // save space at the top for score and timer
	state.playFieldMax.y = state.screenMax.y;

	// center the timer
	state.timerPos.x = state.screenMax.x / 2;
	state.timerPos.y = 0;

	// score position
	state.leftScorePos.x = state.timerPos.x - 5;
	state.rightScorePos.x = state.timerPos.x + 10;
	state.leftScorePos.y = state.timerPos.y;
	state.rightScorePos.y = state.timerPos.y;	

	// center the ball
	state.ballPos.x = state.playFieldMax.x / 2;
	state.ballPos.y = state.playFieldMax.y / 2;

	// left paddle 
	state.leftPaddlePos = state.playFieldMin;

	// right paddle
	state.rightPaddlePos.x = state.playFieldMax.x - 1;
	state.rightPaddlePos.y = state.playFieldMin.y;

	//starting score
	state.leftScore = 0;
	state.rightScore = 0;

	// settings
	state.timerDelay = 100000;
	state.paddleHeight = 5;
	state.paddleWidth  = 1;
	state.quit = false;
	state.isPaused = false;
	state.autoPlayEnabled = false;
	state.leftPaddleDelay = 25000;
	state.rightPaddleDelay = state.timerDelay * 1.25;
	state.ballDelay = state.timerDelay;
	state.collisionDelay = 1000;
	

	//draw boundary
	for (uint8_t i = state.playFieldMin.x; i < state.playFieldMax.x; ++i) {
		drawChar(state.playFieldMin.y - 1, i, '_');
	}
	
	// thread function pointer type
	typedef void* (*ThreadFunction)(void*);

	// assign functions to threads
	ThreadFunction threadFuncs[] = {
		moveball, moveopponent, moveme, timer, score, moveplayer,
		checkcollision
	};
	static const uint8_t numThreads = sizeof(threadFuncs) / sizeof(threadFuncs[0]);
	pthread_t threads[numThreads];

	// Start the threads
	for (uint8_t i = 0; i < numThreads; ++i) {
		if (pthread_create(&threads[i], NULL, threadFuncs[i], NULL)) 	{
		  fprintf(stderr, "Thread %i creation failed", i);
		}
	}

	// Wait for the threads to exit
	for (uint8_t i = 0; i < numThreads; ++i) {
		pthread_join(threads[i], NULL);
	}
	
	// tear down the window
	delwin(win);
	endwin();
	refresh();
	
	// get out of here
	return EXIT_SUCCESS;
}
