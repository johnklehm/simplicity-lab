/* ballctrl.h		1.2		20101028
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
 * This file servers as the interface header definition for the ball controller logic of the 
 * pong game.
 */
#ifndef BALLCTRL_H
#define BALLCTRL_H

#ifdef BALLCTRL_C
#define EXTERN_PFX
#else
#define EXTERN_PFX extern
#endif

typedef enum direction {X, Y} Direction;
EXTERN_PFX void collision(Direction d);
EXTERN_PFX void* moveball(void* vp);

#undef EXTERN_PFX
#endif
