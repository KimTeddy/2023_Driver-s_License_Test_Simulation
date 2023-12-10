
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef _LCDTEXT_H_
#define _LCDTEXT_H_
#define CMD_WRITE_STRING 0x20

void lcdtextwrite(const char *str1, const char *str2, int lineFlag);
void txtlcd_Init(void);
void txtlcd_Exit(void);

#endif //  __TEXTLCD_DRV_H__

