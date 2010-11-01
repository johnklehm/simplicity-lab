/* autoplay.h		1.2		20101101
 *
 * @author klehmc krewalk
 * @version 1.2
 * @date 20101101
 * @course cs3841-002
 *
 * Copyright 2010 klehmc krewalk
 */
#ifndef AUTOPLAY_H
#define AUTOPLAY_H

#ifdef AUTOPLAY_C
#define EXTERN_PFX 
#else
#define EXTERN_PFX extern
#endif

EXTERN_PFX void* moveplayer(void* vp);

#undef EXTERN_PFX
#endif
