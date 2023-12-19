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


    int screen_width2;
    int screen_height2;
    int bits_per_pixel2;
    int line_length2;
    int cols2 = 0, rows2 = 0;
	char *data2;
    char bmpfile2[200];

       






	//FrameBuffer init
    if ( fb_init(&screen_width, &screen_height, &bits_per_pixel, &line_length) < 0 )
	{
		printf ("FrameBuffer Init Failed\r\n");
		return 0;
	}

	 //FrameBuffer init
    if ( fb_init2(&screen_width2, &screen_height2, &bits_per_pixel2, &line_length2) < 0 )
	{
		printf ("FrameBuffer0 Init Failed\r\n");
		return 0;
	}
    
		fb_clear2(0,0,1024,600);
        strcpy(bmpfile2, "testword");
	//Clear FB.
	//fb_clear();
    strcat(bmpfile2, ".bmp");

	
	
    while(testingnow==1) {
        usleep(33500);
        strcpy(bmpfile, "");
	//Clear FB.
	//fb_clear();
    snprintf(bmpfile, sizeof(bmpfile), "%05d", nums);
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

	//FileRead
    if (read_bmp(bmpfile2, &data2, &cols2, &rows2) < 0)
	{
		printf ("File open failed\r\n");
		return 0;
	}
	//FileWrite
	fb_write2(data2, cols2,rows2,0,0);
    
	close_bmp();
    }
}
