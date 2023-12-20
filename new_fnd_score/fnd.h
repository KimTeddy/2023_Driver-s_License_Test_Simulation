#ifndef _FND_H_
#define _FND_H_

#define MAX_FND_NUM			6
#define FND_DATA_BUFF_LEN	(MAX_FND_NUM + 2)
// #define MODE_STATIC_DIS 's'
// #define MODE_TIME_DIS 't'
// #define MODE_COUNT_DIS 'c'

int fnd(int num, char mode);
int fndDisp(int num , int dotflag);
int fndDisp_canoff(int num, int dotflag, int offdigit[]);
int fndDisp_ch(char ch[]);
#define FND_DRIVER_NAME "/dev/perifnd"

#endif
