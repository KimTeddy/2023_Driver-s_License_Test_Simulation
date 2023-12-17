#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "../libfbdev/libfbdev.h"
#include "../libbuzzer/libbuzzer.h"
#include "../libjpeg/jpeglib.h"

char musicNote1[2000]=
" ^E ^E ^E ^C ^E ^G G ^C G E A B Bb A G ^E ^G ^A ^F ^G ^E ^C ^D B ^C G E A B Bb A G ^E ^G ^A ^F ^G ^E ^C ^D B"
" ^G ^F# ^F ^D ^E G A ^C A ^C ^D ^G ^F# ^F ^D ^E *C *C *C ^G ^F# ^F ^D ^E G A ^C A ^C ^D ^D# ^D ^C"
" ^C ^C ^C ^C ^D ^E ^C A G ^C ^C ^C ^C ^D ^E ^C ^C ^C ^C ^D ^E ^C A G ^E ^E ^E ^C ^E ^G G ^C G E"
" A B Bb A G ^E ^G ^A ^F ^G ^E ^C ^D B ^C G E A B Bb A G ^E ^G ^A ^F ^G ^E ^C ^D B ^E-^C G G A ^F ^F A"
" B ^A ^A ^A ^G ^F ^E ^C A G ^E-^C G G A ^F ^F A B ^F ^F ^F ^E ^D ^C G E C ^C G E A B A G# Bb G# G-F#-G ";
//FROM https://noobnotes.net/super-mario-bros-theme-nintendo/?solfege=false&transpose=0
char musicNote3[2000]=
"C  E       G   B  ^C   B     A - G "
" ^D          ^C    ^C     B     ^C   B  A-G "
" F     A       ^C    ^D-^D#    ^D       ^C-A "
" F - G# - ^C        ^D        ^D# - ^D     Bb-G#"
" ^C    ^D     B    ^C    A     B   A-G#"
" ^E             ^D      ^C      B      A-B   A-G#"
" G           A      ^C      ^G     ^F"
" ^E   ^D     ^C     A       G# - ^D    ^E   ^D-^C ";
char musicNote2[2000]=
" C   A   G    Bb      C  F  E  F"
" C     A      G      Bb    C    F-E-F"
" A   Bb    ^C    ^D     ^C - G     G  A  Bb-^C  A"
" A      Bb     ^C      ^D     ^C - G    G-A  Bb  ^C   A"
" ^C   ^D-^E   ^F   ^E-Bb"
" Bb - ^C             ^D       ^E     ^D-^C-Bb    A   ^C"
" ^C   ^D-^E   ^F   ^E-Bb"
" Bb       ^C      ^D      ^E      ^D     ^C    Bb   A     ^C"
" C       A      G       Bb      C   F  E   F"
" C   A   G    Bb     C  F-E-F"
" C     A     G      Bb-G     C-F-G-A"
" A      Bb      ^C-^D-^C-G         G      A     Bb      ^C      A"
" A  -  Bb         ^C           ^D         ^C - G       G     A-Bb-^C   A"
" ^C   ^D-^E   ^F   ^E-Bb"
" Bb - ^C             ^D       ^E     ^D-^C-Bb    A   ^C"
" ^C   ^D-^E   ^F   ^E-Bb"
" Bb       ^C      ^D      ^E      ^D     ^C    Bb   A     ^C"
" C       A      G       Bb      C   F  E   F"
" C       A      G       Bb      C   F  E   F"
" C   F  E   F";


void *musicFunc(void* arg)
{
	libBuzzerInit();
	int i=0;
	int thisScale = 0;
	char *note = musicNote1;
	char prevChar = 0;
	while (1)
	{
		for (i=0;i<strlen(note);i++)
		{
			switch (note[i])
			{
				case ' ': case '-':	//Play scale and wait;
				//printf ("ThisScale:%d\r\n",thisScale);
				if ((prevChar!=' ') && (prevChar!= '-'))
				{
					setFrequency (thisScale);	
					buzzerEnable (1);
					usleep(250*1000);	//100ms;

					buzzerEnable (0);
					usleep(10*1000);	//100ms;
					thisScale = 0;
				}
				break;
				case '^': thisScale+=HC;	break;
				case '*': thisScale+=HHC;	break;
				case 'C': thisScale += C - C;	break;
				case 'D': thisScale += D - C;	break;
				case 'E': thisScale += E - C;	break;
				case 'F': thisScale += F - C;	break;
				case 'G': thisScale += G - C;	break;
					
				case 'A': thisScale += A - C;	break;
				case 'B': thisScale += B - C;	break;
					
				case '#': thisScale++;	break;
				case 'b': thisScale--;	break;
			}
			prevChar = note[i];
		}
		usleep(500*1000);
		if (note == musicNote1)
			note = musicNote2;
		else if (note == musicNote2)
			note = musicNote3;
		else note = musicNote1;
	}
}
int main (int argc, char **argv)
{
	pthread_t musicThreadT;
	pthread_create(&musicThreadT, NULL, musicFunc, NULL);
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
	while (1)
	for (i=99; i<=3285;i++)
	{
		char filename[200]={0,};
		snprintf(filename,200,"./superm/supermario_%05d.jpg",i);
		//FileRead
		int error=0;
		struct jpeg_decompress_struct cinfo;
		struct jpeg_error_mgr jerr;
	 	cinfo.err = jpeg_std_error(&jerr);
   		jpeg_create_decompress(&cinfo);
		FILE *fp = fopen(filename, "rb");
    	jpeg_stdio_src(&cinfo, fp);
		jpeg_read_header(&cinfo, TRUE); 
		//printf ("JPG %d by %d by %d, %d\n",
		//	cinfo.image_width,cinfo.image_height,cinfo.num_components, cinfo.output_scanline);
		cols = cinfo.image_width;
		rows = cinfo.image_height;

		data = malloc(cols*rows*3);
		int currPoint = 0;
		jpeg_start_decompress(&cinfo);
		while(cinfo.output_scanline < cinfo.output_height) 
		{
			//printf ("CInfoScanlines:%d\r\n",cinfo.output_scanline);
			char *tempPtr=&data[currPoint];
			jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&tempPtr, 1);
			currPoint+=cols*3;
		}
		jpeg_finish_decompress(&cinfo);
		jpeg_destroy_decompress(&cinfo);
		fclose(fp);

		fb_write_reverse(data, cols,rows);
		free(data);

	}
	fb_close();
    return 0;
}
