/************************************************************************************
* This file was developed as part of CS3841 Design of Operating Systems at the 
* Milwaukee School of Engineering.  This file is copyright 2008-2009 by MSOE.
* 
* $Author: wws $
* $Revision: 1.1 $
* $Name:  $
* This file manages the motion of the users paddle.  It is responsible for 
* reading commands from the keyboard and processing them appropriately.
*
************************************************************************************/
#define PADDLECTRL_C

/************************************************************************************
 * External Includes
 ************************************************************************************/
#include <unistd.h>
#include <curses.h>
#include "pong.h"


/************************************************************************************
 * Private structure / type definitions
 ************************************************************************************/
#define PADDLE_SIZE (5)

/************************************************************************************
 * Private function / method prototypes
 ************************************************************************************/


/************************************************************************************
 * Constant declarations / table declarations
 ***********************************************************************************/

/************************************************************************************
 * Method header:
 * Function name: moveme
 * Function purpose: This function is responsible for moving the users paddle.
 *                   It is spawned as a thread and ewill exit if and when quit is no longer true.
 * Function parameters: 
 *                   void *vp - This is a pointer to the parameters passed into the 
 *                              thread.  At the present time, this parameter is not used.
 * Function return value: void* This is the return value when the thread exits.  
 *                              Currently, it is always NULL, as no data is directly 
 *                              returned by the thread.
 ************************************************************************************/
// Run the user's paddle
void *moveme(void* vp)
{
	int ch;
	uint16_t vpos = playFieldMinY;

	// draw the default paddle
	for (uint8_t i = 0; i < PADDLE_SIZE; ++i) {
		drawChar(playFieldMinY + i, playFieldMinX, ' ' | A_REVERSE);
	}

	while(!quit)
	{
		ch = getch();
		switch (ch) {
		case KEY_UP:
			vpos--;

			if (vpos < playFieldMinY) {
	            vpos = playFieldMinY;
            }

			drawChar(vpos, 0, ' ' | A_REVERSE);
			drawChar(vpos + PADDLE_SIZE, 0, ' ' | A_NORMAL);

			break;
		case KEY_DOWN:
			vpos++;

 			if (vpos > (playFieldMaxY - PADDLE_SIZE)) {
				vpos = (playFieldMaxY - PADDLE_SIZE);
			}

			drawChar(vpos - 1, 0, ' ' | A_NORMAL);
			drawChar(vpos + PADDLE_SIZE - 1, 0, ' ' | A_REVERSE);

			break;
		case 'p':
			isPaused = true;
			while (isPaused) {
				usleep(gameDelay);

				if (getch() == 'p') {
					isPaused = false;
				}
			}

			break;
		case 'q':
			quit=true;
			break;
		default:
			break;
		}
	}
	return NULL;	
}

