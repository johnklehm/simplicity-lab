/* ballctrl.c		1.2		20101028
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
 *
 * This file manages tthe motion of the ball.  This includes collisions, edge 
 * detections, paddle detection, etc.
 */
#define BALLCTRL_C

#include <stdlib.h>
#include <unistd.h>
#include "ballctrl.h"
#include "pong.h"

typedef enum scorer {PLAYER, COMPUTER} Scorer;

/**
 * Invoked when a ball collision is detected. It will fork a new child
 * process and play a beep sound. 
 */
static void collision() {
	// fork and play beep (cmd line program)
	pid_t child = fork();
	if (child == 0) {
		// the child - play beep
		execlp("/usr/bin/beep", "beep", "-f", "700", "-l", "20", NULL);
		exit(EXIT_SUCCESS);
	}
}

/**
 * Called when a goal is detected.
 *
 * @param p Whoe the score should get attributed to
 */
static void score(Scorer p) {
    switch (p) {
    case COMPUTER:

    break;
    case PLAYER:

    break;
    default:
    break;
    }
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
void *moveball(void* vp) {
	// these should be floating point to get slopes other than
	// +/- 45 degrees
	float yadder = 1.0f;
	float xadder = 1.0f;
	float xactual = ballx;
	float yactual = bally;

    while (!quit) {
		while (isPaused) { usleep(gameDelay); }

		drawChar(bally,ballx,' ' | A_NORMAL);		
		yactual+=yadder;
		xactual+=xadder;
		
		// truncate
		bally = (int)(yactual);
		ballx = (int)(xactual);

		// bottom boundary
		if (bally >= playFieldMaxY) {
			yadder = -yadder;
			collision();
		}
		// top boundry
		if (bally <= playFieldMinY) {
			yadder = -yadder;
			collision();
		}
		// right boundary
		if (ballx >= playFieldMaxX) {
			xadder = -xadder;
                        score(PLAYER);
		}
		// left boundary
		if (ballx <= playFieldMinX) {
			xadder = -xadder;
                        score(COMPUTER);
		}

		drawChar(bally,ballx,' ' | A_REVERSE );

		// Do not want ball to move too fast...		
		usleep(gameDelay);
	}

    return NULL;
}
