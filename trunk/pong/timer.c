/* timer.c       2010 10 26       1.0
 * @author klehmc
 * @version 1.0
 * @date 20101026
 * @course CS3841-002
 */
#define TIMER_C

#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include "timer.h"
#include "pong.h"

/**
 * Keeps track of and updates a timer display
 */
void *timer(void* vp) {
	uint32_t ticks = 0;
	while (!quit) {
                static const uint8_t bufSize = 32;
                char timerBuf[bufSize];
		while (isPaused) { usleep(gameDelay); }

                memset(timerBuf, 0, bufSize);
                snprintf(timerBuf, bufSize, "%i", ticks++ / (100000/gameDelay));

                for (uint8_t i = bufSize - 1; i >= 0; --i) {
                    if (timerBuf[i] != 0) {
                        timerBuf[i + 1] = timerBuf[i];
                        timerBuf[i] = '.';
                        break;
                    }
                }
		
                for (uint8_t i = 0; timerBuf[i] != 0 && i < bufSize; ++i) {
			drawChar(timerY, timerX + i, timerBuf[i]);
		}

		usleep(gameDelay);
	}

	return NULL;
}
