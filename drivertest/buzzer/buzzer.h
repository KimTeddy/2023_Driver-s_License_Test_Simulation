#ifndef _BUZZER_H_
#define _BUZZER_H_
#include "buzzer_pitch.h"

int findBuzzerSysPath();
void buzzerEnable(int bEnable);
void setFrequency(int frequency);

int buzzerInit(void);
int buzzerPlaySong(int scale);
int buzzerStopSong(void);
int buzzerExit(void);

#endif
