#include <stdio.h>
#include <stdlib.h>
#include "../libfbdev/libfbdev.h"
#include "../libbmp/libbmp.h"

int main (int argc, char **argv)
{
    int screen_width;
    int screen_height;
    int bits_per_pixel;
    int line_length;
    int cols = 0, rows = 0;
	char *data;
	//FrameBuffer init
    if ( fb_init(&screen_width, &screen_height, &bits_per_pixel, &line_length) < 0 )
	{
		printf ("FrameBuffer Init Failed\r\n");
		return 0;
	}
	//Clear FB.
	fb_clear();
	
	int i=0;
	for (i=99; i<=3285;i++)
	{
		char filename[200]={0,};
		snprintf(filename,200,"./superm/supermario_%05d.bmp",i);
		//FileRead
	    if (read_bmp(filename, &data, &cols, &rows) < 0)
		{
			printf ("File open failed\r\n");
			return 0;
		}	
		//FileWrite
		fb_write(data, cols,rows);
    
		close_bmp();
	}
	fb_close();
    return 0;
}
