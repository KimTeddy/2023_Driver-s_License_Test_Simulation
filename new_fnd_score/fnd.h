#ifndef _FND_H_
#define _FND_H_

#define MAX_FND_NUM			6
#define FND_DATA_BUFF_LEN	(MAX_FND_NUM + 2)
// #define MODE_STATIC_DIS 's'
// #define MODE_TIME_DIS 't'
// #define MODE_COUNT_DIS 'c'

int fnd(int num, char mode);
int fndDisp(int num , int dotflag);
char fndDisp_ch(char c[Max_FND_NUM+1]);
#define FND_DRIVER_NAME "/dev/perifnd"

#endif
