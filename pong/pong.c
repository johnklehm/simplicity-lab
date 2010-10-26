/************************************************************************************
* This file was developed as part of CS3841 Design of Operating Systems at the 
* Milwaukee School of Engineering.  This file is copyright 2008-2009 by MSOE.
* 
* $Author: wws $
* $Revision: 1.1 $
* $Name:  $
* This file manages serves as the main program for the pong game.
* It is responsible for spawning all other threads and managing the overall 
* behavior of the game.  All global variables are owned by this file.
*
************************************************************************************/
#define PONG_C

/************************************************************************************
 * External Includes
 ************************************************************************************/
#include <curses.h>
#include <sys/types.h>
#include <unistd.h>

#include "pong.h"
#include "paddlectrl.h"
#include "ballctrl.h"
#include "opponent.h"
#include "timer.h"

/************************************************************************************
 * Method header:
 * Function name: moveme
 * Function purpose: This function is responsible for moving the users paddle.
 *                   It is spawned as a thread and ewill exit if and when quit is no longer true.
 * Function parameters: 
 *                   int argc  - This is a count of the number of command line parameters 
 *                               passed by the operating system.
 *                   char *vp[] - This is the array of strings which is passed to program.
 * Function return value: int.  0 will be returned upon normal exiting of the program.  
 *                                A negative value will indicate an error.
 ************************************************************************************/
int main(int argc, char* argv[])
{
	int rc1;
	int rc2;
	int rc3;
	int rc4;

	pthread_t thread1, thread2, thread3, thread4;
	pthread_mutex_init(&screenLock, NULL);

	// init window - see curses documentation for guidance
	win = initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(win,TRUE);
	nodelay(win,TRUE);
	refresh();
	// get the extents of the screen
	getmaxyx(win,maxy,maxx);

	// Initialize all of the variables.
	// Global data - for inter-thread communication
	playFieldMinX = 0;
	playFieldMaxX = maxx;
	playFieldMinY = 2; // save space at the top for score and timer
	playFieldMaxY = maxy;

	// center the timer
	timerX = maxx / 2;
	timerY = 0;

	// center the ball
	ballx = playFieldMaxX / 2;
	bally = playFieldMaxY / 2;

	// settings
	quit = false;
	isPaused = false;
	
	
	gameDelay = 100000;

	// Start the threads
	if ((rc1=pthread_create(&thread1, NULL, &moveball, NULL)))
	{
	  fprintf(stderr, "Thread 1 creation failed");
	}
	if ((rc2=pthread_create(&thread2, NULL, &moveoponent, NULL)))
	{
	  fprintf(stderr, "Thread 2 creation failed");
	}
	if ((rc3=pthread_create(&thread3, NULL, &moveme, NULL)))
	{
	  fprintf(stderr, "Thread 3 creation failed");
	}
	if ((rc4=pthread_create(&thread4, NULL, &timer, NULL)))
	{
	  fprintf(stderr, "Thread 4 creation failed");
	}

	// Wait for the threads to exit
	pthread_join(thread1, NULL);
	//pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	//pthread_join(thread4, NULL);
	
	// tear down the window
	delwin(win);
	endwin();
	refresh();
	
	// get out of here
	return 0;
}

void drawChar(uint16_t y, uint16_t x, chtype c) {
	pthread_mutex_lock(&screenLock);
	mvaddch(y, x, c);
	pthread_mutex_unlock(&screenLock);
}