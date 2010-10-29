/************************************************************************************
* This file was developed as part of CS3841 Design of Operating Systems at the 
* Milwaukee School of Engineering.  This file is copyright 2008-2009 by MSOE.
* 
* $Author: wws $
* $Revision: 1.1 $
* $Name:  $
* This file manages tthe motion of the ball.  This includes collisions, edge 
* detections, paddle detection, etc.
*
************************************************************************************/
#define BALLCTRL_C


/************************************************************************************
 * External Includes
 ************************************************************************************/
#include <stdlib.h>
#include <unistd.h>
#include "ballctrl.h"
#include "pong.h"

/************************************************************************************
 * Private structure / type definitions
 ************************************************************************************/
typedef enum scorer {PLAYER, COMPUTER} Scorer;

/************************************************************************************
 * Private function / method prototypes
 ************************************************************************************/
static void collision();
static void score(Scorer p);

/************************************************************************************
 * Constant declarations / table declarations
 ***********************************************************************************/



/************************************************************************************
 * Method header:
 * Function name: mainmoveball
 * Function purpose: This function is responsible for moving the ball within the game of pong.
 *                   It is spawned as a thread and ewill exit if and when quit is no longer true.
 * Function parameters: 
 *                   void *vp - This is a pointer to the parameters passed into the 
 *                              thread.  At the present time, this parameter is not used.
 * Function return value: void* This is the return value when the thread exits.  
 *                              Currently, it is always NULL, as no data is directly 
 *                              returned by the thread.
 ************************************************************************************/
// This thread is responsible for moving the ball
void *moveball(void* vp) {
	// these should be floating point to get slopes other than
	// +/- 45 degrees
	float yadder = 1.0f;
	float xadder = 1.0f;
	float xactual = (float)ballx;
	float yactual = (float)bally;

    while(!quit)
	{
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

/************************************************************************************
 * Method header:
 * Function name: collision
 * Function purpose: This method will be invoked when a ball collision is detected. 
 *                   It will fork a new child process and play a beep sound.
 * Function parameters: 
 *                   None
 * Function return value: None
 ************************************************************************************/
// collision sound effects
static void collision()
{
	// fork and play beep (cmd line program)
	pid_t child = fork();
	if (child == 0)
	{	// the child - play beep
		execlp("/usr/bin/beep", "beep", "-f", "700", "-l", "20", NULL);
		exit(EXIT_SUCCESS);
	}
	return;
}

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
