#ifndef _LED_H_
#define _LED_H_
int ledLibInit(void);
int ledOnOff(int ledNum, int onOff);
int ledStatus(void);
int ledLibExit(void);
int ledRead(const char* data);

#define LED_DRIVER_NAME "/dev/periled"

#endif _LED_H_