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
	int vpos = 0;	// start at top row

	// get the extents of the screen
	int maxx; 
        int maxy;
	getmaxyx(win,maxy,maxx);

	// draw the default paddle
	int i;
	for (i=0;i<PADDLE_SIZE;i++)
	{
		mvaddch(i,0,' ' | A_REVERSE);
	}

	while(!quit)
	{
		ch = getch();
		switch (ch)
		{
		case KEY_UP:
			vpos--;
			if (vpos < 0) 
                        {
                          vpos = 0;
                        }
			mvaddch(vpos,0,' ' | A_REVERSE);
			mvaddch(vpos+PADDLE_SIZE,0,' ' | A_NORMAL);
			break;
		case KEY_DOWN:
			vpos++;
			if (vpos > (maxy-PADDLE_SIZE)) 
                        {
                          vpos = (maxy-PADDLE_SIZE);
                        }
			mvaddch(vpos-1,0,' ' | A_NORMAL);
			mvaddch(vpos+PADDLE_SIZE-1,0,' ' | A_REVERSE);
			break;
		case 'p':
			isPaused = true;
			while (isPaused) {
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

