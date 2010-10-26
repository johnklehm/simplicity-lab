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
#ifndef BALLCTRL_H
#define BALLCTRL_H

#ifdef BALLCTRL_C
#define EXTERN_PFX
#else
#define EXTERN_PFX extern
#endif

/************************************************************************************
 * External Includes
 ************************************************************************************/
// None as of right now.
/************************************************************************************
 * Public structure / type definitions
 ************************************************************************************/
// None as of right now.

/************************************************************************************
 * Public function / method prototypes
 ************************************************************************************/
// This thread is responsible for moving the ball
EXTERN_PFX void *moveball(void* vp);
#undef EXTERN_PFX
#endif
