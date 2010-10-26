#ifndef TIMER_H
#define TIMER_H

#ifdef TIMER_C
#define EXTERN_PFX 
#else
#define EXTERN_PFX extern
#endif

EXTERN_PFX void *timer(void* vp);
#undef EXTERN_PFX
#endif
