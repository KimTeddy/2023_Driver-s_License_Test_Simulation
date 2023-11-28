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
void buzzerTone(int scale, unsigned int milliseconds);
void delay_ms(unsigned int milliseconds);
#endif
