#ifndef _LIB_FBDEV_H_
#define _LIB_FBDEV_H_

//#define ENABLED_DOUBLE_BUFFERING	1	//This makes fb slow...

int fb_init(int * screen_width, int * screen_height, int * bits_per_pixel, int * line_length);
void fb_close(void);
void fb_clear(void);
void fb_write(char *picData, int picWidth, int picHeight);
void fb_write_reverse(char *picData, int picWidth, int picHeight);
void fb_doubleBufSwap(void);
#endif