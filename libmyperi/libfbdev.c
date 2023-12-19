#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>     // for open/close
#include <fcntl.h>      // for O_RDWR
#include <sys/ioctl.h>  // for ioctl
#include <sys/mman.h>
#include <linux/fb.h>   // for fb_var_screeninfo, FBIOGET_VSCREENINFO
#include "libfbdev.h"


//You have to do:
//
//  fbset -fb /dev/fb1 -xres 1024 -yres 600 -depth 32 -vyres 600 -t 31250 40 40 29 13 48 3
//
//You must.

#define FBDEV_FILE "/dev/fb0"
#define FBDEV_FILE2 "/dev/fb1"

static int fbfd;
static int fbfd2;
static int fbHeight=0;	//현재 하드웨어의 사이즈
static int fbWidth=0;	//현재 하드웨어의 사이즈
static unsigned long   *pfbmap;	//프레임 버퍼
static unsigned long 	*pfbmap2;
static struct fb_var_screeninfo fbInfo;	//To use to do double buffering.
static struct fb_fix_screeninfo fbFixInfo;	//To use to do double buffering.

struct mxcfb_color_key { int enable;__u32 color_key;};
#define MXCFB_SET_CLR_KEY _IOW('F',0x22,struct mxcfb_color_key)


#define PFBSIZE 			((fbHeight)*fbWidth*sizeof(unsigned long))	
static int currentEmptyBufferPos = 0;
//1 Pixel 4Byte Framebuffer.


int fb_init(int * screen_width, int * screen_height, int * bits_per_pixel, int * line_length)
{
    struct  fb_fix_screeninfo fbfix;

	if( (fbfd = open(FBDEV_FILE, O_RDWR)) < 0)
    {
        printf("%s: open error\n", FBDEV_FILE);
        return -1;
    }

    if( ioctl(fbfd, FBIOGET_VSCREENINFO, &fbInfo) )
    {
        printf("%s: ioctl error - FBIOGET_VSCREENINFO \n", FBDEV_FILE);
		close(fbfd);
        return -1;
    }
   	if( ioctl(fbfd, FBIOGET_FSCREENINFO, &fbFixInfo) )
    {
        printf("%s: ioctl error - FBIOGET_FSCREENINFO \n", FBDEV_FILE);
        close(fbfd);
        return -1;
    }
	//printf ("FBInfo.YOffset:%d\r\n",fbInfo.yoffset);
	fbInfo.yoffset = 0;
	ioctl(fbfd, FBIOPUT_VSCREENINFO, &fbInfo);	//슉!
    if (fbInfo.bits_per_pixel != 32)
    {
        printf("bpp is not 32\n");
		close(fbfd);
        return -1;
    }	

    fbWidth = *screen_width    =   fbInfo.xres;
    fbHeight = *screen_height   =   fbInfo.yres;
    *bits_per_pixel  =   fbInfo.bits_per_pixel;
    *line_length     =   fbFixInfo.line_length;

	pfbmap  =   (unsigned long *)
        mmap(0, PFBSIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fbfd, 0);
	
	if ((unsigned)pfbmap == (unsigned)-1)
    {
        printf("fbdev mmap failed\n");
        close(fbfd);
		return -1;
    }
	#ifdef ENABLED_DOUBLE_BUFFERING
		currentEmptyBufferPos = DOUBLE_BUFF_START;	//더블버퍼링 임시 주소로 할당
	#else
		currentEmptyBufferPos = 0;
	#endif
	//printf ("CurrentEmptyBuffPos:%d\r\n",currentEmptyBufferPos);
//printf ("\r\n");
	return 1;
}

int fb_init2(void)	//as overlay.
{
	printf ("Second FB1 is init...\r\n");
        if( (fbfd2 = open(FBDEV_FILE2, O_RDWR)) < 0)
    {
        printf("%s: open error\n", FBDEV_FILE2);
        return -1;
    }

    struct mxcfb_color_key key;
    key.color_key=0x0; //fb1 black = transparent
    key.enable = 1;
    if(ioctl(fbfd2, MXCFB_SET_CLR_KEY, &key)<0) {printf("Color key Failed!\r\n");}

	printf ("PFB Size:%d\r\n",PFBSIZE);
        pfbmap2  =   (unsigned long *) mmap(0, PFBSIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fbfd2, 0);

        if ((unsigned)pfbmap2 == (unsigned)-1)
    {
        printf("fbdev2 mmap failed\n");
        close(fbfd2);
                return -1;
    }
       return 1;
}

void fb_clear(void)
{
	int coor_y = 0;
	int coor_x = 0;
	// fb clear - black
    for(coor_y = 0; coor_y < fbHeight; coor_y++) 
	{
        unsigned long *ptr =   pfbmap + currentEmptyBufferPos + (fbWidth * coor_y);
        for(coor_x = 0; coor_x < fbWidth; coor_x++)
        {
            *ptr++  =   0x000000;
        }
    }
}

void fb_clear2(int xpos, int ypos, int width, int height)
{
	
        int coor_y = 0;
        int coor_x = 0;
        // fb clear - black
	//if (height+ypos > fbHeight)
	//sheight
	if (ypos+height > fbHeight) height = fbHeight-ypos;
    for(coor_y = ypos; coor_y < ypos+height; coor_y++)
        {
//        unsigned long *ptr =   pfbmap2 + (fbWidth * coor_y)+(fbWidth-xpos-1);
        for(coor_x = 0; coor_x < width; coor_x++)
        {
            //*ptr++  =   0x000000;
	    pfbmap2[ (coor_y)*fbWidth + ( (fbWidth-xpos)-coor_x-1) ] = 0x0;
        }
    }
}

void fb_close(void)
{
	printf ("Memory UnMapped!\r\n");
    munmap( pfbmap, PFBSIZE);
	printf ("CloseFB\r\n");
    close( fbfd);
}
void fb_close2(void)
{
        printf ("Memory UnMapped!\r\n");
    munmap( pfbmap2, PFBSIZE);
        printf ("CloseFB\r\n");
    close( fbfd2);
}

void fb_write(char* picData, int picWidth, int picHeight)
{
	int coor_y=0;
	int coor_x=0;
	int targetHeight = (fbHeight<picHeight)?fbHeight:picHeight;	//if Screen과 파일 사이즈가 안맞으면
	int targetWidth = (fbWidth<picWidth)?fbWidth:picWidth;		//if Screen과 파일 사이즈가 안맞으면
	
	printf ("TargetHeight:%d, TargetWidth:%d\r\n",targetHeight, targetWidth);
	for(coor_y = 0; coor_y < targetHeight; coor_y++) 
	{
		int bmpYOffset = coor_y*picWidth*3; ///Every 1Pixel requires 3Bytes.
		int bmpXOffset = 0;
		for (coor_x=0; coor_x < targetWidth; coor_x++)
		{
			//BMP: B-G-R로 인코딩 됨, FB: 0-R-G-B로 인코딩 됨.
			pfbmap[coor_y*fbWidth+ (fbWidth-coor_x-1)] = 
				((unsigned long)(picData[bmpYOffset+bmpXOffset+2])<<16) 	+
				((unsigned long)(picData[bmpYOffset+bmpXOffset+1])<<8) 		+
				((unsigned long)(picData[bmpYOffset+bmpXOffset+0]));
			bmpXOffset+=3;	//Three Byte.
		}
    }	
	printf ("Job DOne\r\n");
}


void fb_write2(char* picData, int picWidth, int picHeight, int frameX, int frameY)
{
        int coor_y=0;
        int coor_x=0;
        int targetHeight = ((fbHeight-frameY)<picHeight)?(fbHeight-frameY):picHeight;     //if Screen과 파일 사이즈가 안맞으면
        int targetWidth = ((fbWidth-frameX)<picWidth)?(fbWidth-frameX):picWidth;          //if Screen과 파일 사이즈가 안맞으면

        for(coor_y = 0; coor_y < targetHeight; coor_y++)	//Image Y 사이즈...
        {
                int bmpYOffset = coor_y*picWidth*3; ///Every 1Pixel requires 3Bytes.
                int bmpXOffset = 0;
                for (coor_x=0; coor_x < targetWidth; coor_x++)	//Image X 사이즈
                {
                        //BMP: B-G-R로 인코딩 됨, FB: 0-R-G-B로 인코딩 됨.
                        pfbmap2[ ( coor_y + frameY ) *fbWidth + ( (fbWidth-frameX)-coor_x-1) ] =
                                ((unsigned long)(picData[bmpYOffset+bmpXOffset+2])<<16)         +
                                ((unsigned long)(picData[bmpYOffset+bmpXOffset+1])<<8)          +
                                ((unsigned long)(picData[bmpYOffset+bmpXOffset+0]));
                        bmpXOffset+=3;  //Three Byte.
                }
    }
}
