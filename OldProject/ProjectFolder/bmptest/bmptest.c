#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <linux/spi/spidev.h>
#include <stdint.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <linux/input.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <stdio.h>
#include <stdlib.h>     // for exit


int main (void)
{
    int screen_width;
    int screen_height;
    int bits_per_pixel;
    int line_length;
    int cols = 0, rows = 0;
	char *data;
    char bmpfile[200];
    int nums=0;
    int testingnow=1;
	//FrameBuffer init
    if ( fb_init(&screen_width, &screen_height, &bits_per_pixel, &line_length) < 0 )
	{
		printf ("FrameBuffer Init Failed\r\n");
		return 0;
	}
    while(testingnow==1) {
        usleep(500000);
        strcpy(bmpfile, "");
	//Clear FB.
	//fb_clear();
    snprintf(bmpfile, sizeof(bmpfile), "%d", nums);
    strcat(bmpfile, ".bmp");

	//FileRead
    if (read_bmp(bmpfile, &data, &cols, &rows) < 0)
	{
		printf ("File open failed\r\n");
		return 0;
	}
	//FileWrite
	fb_write(data, cols,rows);
    
	close_bmp();
	//fb_close();
    nums++;
    }
}
