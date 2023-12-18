#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>     // for open/close
#include <fcntl.h>      // for O_RDWR
#include <sys/ioctl.h>  // for ioctl
#include <sys/mman.h>
#include <linux/fb.h>   // for fb_var_screeninfo, FBIOGET_VSCREENINFO


#include "libbmp.h"
#include "bitmapFileHeader.h"
static char *pDib;
//Read BMP from filename, to data, pDib, with cols, rows.
int read_bmp(char *filename, char **data, int *cols, int *rows)
{
    BITMAPFILEHEADER    bmpHeader;
    BITMAPINFOHEADER    *bmpInfoHeader;
    unsigned int    size;
    unsigned char   magicNum[2];
    int     nread;
    FILE    *fp;

    fp  =  fopen(filename, "rb");
    if(fp == NULL) {
        printf("ERROR\n");
        return -1;
    }

    // identify bmp file
    magicNum[0]   =   fgetc(fp);
    magicNum[1]   =   fgetc(fp);
    //printf("magicNum : %c%c\n", magicNum[0], magicNum[1]);

    if(magicNum[0] != 'B' && magicNum[1] != 'M') {
        printf("It's not a bmp file!\n");
        fclose(fp);
        return -1;
    }

    nread   =   fread(&bmpHeader.bfSize, 1, sizeof(BITMAPFILEHEADER), fp);
    size    =   bmpHeader.bfSize - sizeof(BITMAPFILEHEADER);
    pDib   =   (unsigned char *)malloc(size);      // DIB Header(Image Header)
    fread(pDib, 1, size, fp);
    bmpInfoHeader   =   (BITMAPINFOHEADER *)pDib;

    //printf("nread : %d\n", nread);
    //printf("size : %d\n", size);

    // check 24bit
    if(BIT_VALUE_24BIT != (bmpInfoHeader->biBitCount))     // bit value
    {
        printf("It supports only 24bit bmp!\n");
        fclose(fp);
        return -1;
    }

    *cols   =   bmpInfoHeader->biWidth;
    *rows   =   bmpInfoHeader->biHeight;
    *data   =   (char *) ((char *)(pDib + bmpHeader.bfOffBits - sizeof(bmpHeader) - 2));
    fclose(fp);

	return 1;
}

int close_bmp(void)     // DIB(Device Independent Bitmap)
{
    free(pDib);
	return 1;
}
