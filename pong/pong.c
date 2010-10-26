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
#include <pthread.h>
#include <curses.h>
#include <sys/types.h>
#include <unistd.h>

#include "pong.h"
#include "paddlectrl.h"
#include "ballctrl.h"
#include "opponent.h"

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
	
	pthread_t thread1, thread2, thread3;

	// Initialize all of the variables.
	// Global data - for inter-thread communication
	ballx = 1;
	bally = 1;
	quit = false;
	isPaused = false;
	
	// init window - see curses documentation for guidance
	win = initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(win,TRUE);
	nodelay(win,TRUE);
	refresh();

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
	
	// Wait for the threads to exit
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	
	// tear down the window
	delwin(win);
	endwin();
	refresh();
	
	// get out of here
	return 0;
}
