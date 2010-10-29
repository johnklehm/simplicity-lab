/* timer.h		1.2		20101028
 *
 * @author klehmc krewalk
 * @version 1.2
 * @date 20101028
 * @course cs3841-002
 *
 * Copyright 2010 klehmc krewalk
 */
#ifndef TIMER_H
#define TIMER_H

#ifdef TIMER_C
#define EXTERN_PFX 
#else
#define EXTERN_PFX extern
#endif

EXTERN_PFX void* timer(void* vp);

#undef EXTERN_PFX
#endif
