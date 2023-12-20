#ifndef _TOUCH_H_
#define _TOUCH_H_
#define MESSAGE_ID2 1133
typedef struct
{
	long int messageNum;
	int keyInput;
	int pressed;
	int x;
	int y;
} BUTTON_MSG_S;

int touchInit(void);
int touchExit(void);

#endif

