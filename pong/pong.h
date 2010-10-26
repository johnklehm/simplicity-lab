/************************************************************************************
* This file was developed as part of CS3841 Design of Operating Systems at the 
* Milwaukee School of Engineering.  This file is copyright 2008-2009 by MSOE.
* 
* $Author: wws $
* $Revision: 1.1 $
* $Name:  $
* This file servers as the interface header definition for the ball controller logic of the 
* pong game.
*
************************************************************************************/
#ifndef PONG_H
#define PONG_H

#ifdef PONG_C
#define EXTERN_PFX 
#else
#define EXTERN_PFX extern
#endif

/************************************************************************************
 * External Includes
 ************************************************************************************/
#include <curses.h>
#include <pthread.h>
#include <stdint.h>

/************************************************************************************
 * Public structure / type definitions
 ************************************************************************************/
// None as of right now.

/************************************************************************************
 * Public / global variable definitions
 ************************************************************************************/
// Global data - for inter-thread communication
EXTERN_PFX uint16_t ballx;
EXTERN_PFX uint16_t bally;
EXTERN_PFX WINDOW *win;	// the curses window
EXTERN_PFX bool quit;  // a flag to stop all threads
EXTERN_PFX bool isPaused; // true is pause, false if not
EXTERN_PFX uint16_t maxx;
EXTERN_PFX uint16_t maxy;
EXTERN_PFX uint16_t playFieldMaxX;
EXTERN_PFX uint16_t playFieldMaxY;
EXTERN_PFX uint16_t playFieldMinX;
EXTERN_PFX uint16_t playFieldMinY;
EXTERN_PFX uint16_t timerX;
EXTERN_PFX uint16_t timerY;
EXTERN_PFX uint32_t gameDelay;
EXTERN_PFX pthread_mutex_t screenLock;

/************************************************************************************
 * Public function / method prototypes
 ************************************************************************************/
EXTERN_PFX int main(int argc, char* argv[]);
EXTERN_PFX void drawChar(uint16_t y, uint16_t x, chtype c);
#undef EXTERN_PFX
#endif
