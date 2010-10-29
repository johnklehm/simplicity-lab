/* opponent.h		1.2		20101028
 *
 * @author wws klehmc krewalk
 * @version 1.2
 * @date 20101028
 * @course cs3841-002
 *
 * This file was developed as part of CS3841 Design of Operating Systems at the 
 * Milwaukee School of Engineering.  This file is copyright 2008-2009 by MSOE.
 * 
 * Copyright 2010 klehmc krewalk
 */
#ifndef PADDLECTRL_H
#define PADDLECTRL_H

#ifdef PADDLECTRL_C
#define EXTERN_PFX 
#else
#define EXTERN_PFX extern
#endif

EXTERN_PFX void *moveme(void* vp);

#undef EXTERN_PFX
#endif