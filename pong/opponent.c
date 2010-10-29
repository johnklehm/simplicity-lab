/* opponent.c		1.2		20101028
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
void *moveoponent(void* vp) {
	while (!quit) {
		while (isPaused) { usleep(gameDelay); }
	}

	return NULL;
}
