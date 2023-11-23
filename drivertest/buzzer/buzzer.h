#ifndef _BUZZER_H_
#define _BUZZER_H_
#include "buzzer_pitch.h"
#define MAX_SCALE_STEP 8

const int musicScale[MAX_SCALE_STEP];

int buzzerInit(void);
int buzzerPlaySong(int scale);
int buzzerStopSong(void);
int buzzerExit(void);

#endif
