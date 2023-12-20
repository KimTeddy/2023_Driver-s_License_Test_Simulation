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
static char *pDib2;
//Read BMP from filename, to data, pDib2, with cols, rows.
int read_bmp2(char *filename, char **data, int *cols, int *rows)
{
    BITMAPFILEHEADER    bmpHeader;
    BITMAPINFOHEADER    *bmpInfoHeader;
    unsigned int    size;
    unsigned char   magicNum[2];
    int     nread;
    FILE    *fp2;

    fp2  =  fopen(filename, "rb");
    if(fp2 == NULL) {
        printf("ERROR\n");
        return -1;
    }

    // identify bmp file
    magicNum[0]   =   fgetc(fp2);
    magicNum[1]   =   fgetc(fp2);
    //printf("magicNum : %c%c\n", magicNum[0], magicNum[1]);

    if(magicNum[0] != 'B' && magicNum[1] != 'M') {
        printf("It's not a bmp file!\n");
        fclose(fp2);
        return -1;
    }

    nread   =   fread(&bmpHeader.bfSize, 1, sizeof(BITMAPFILEHEADER), fp2);
    size    =   bmpHeader.bfSize - sizeof(BITMAPFILEHEADER);
    printf ("Malloc required:%d\r\n",size);
    pDib2   =   (unsigned char *)malloc(size);      // DIB Header(Image Header)
    fread(pDib2, 1, size, fp2);
    bmpInfoHeader   =   (BITMAPINFOHEADER *)pDib2;

    //printf("nread : %d\n", nread);
    //printf("size : %d\n", size);

    // check 24bit
    if(BIT_VALUE_24BIT != (bmpInfoHeader->biBitCount))     // bit value
    {
        printf("It supports only 24bit bmp!\n");
        fclose(fp2);
        return -1;
    }

    *cols   =   bmpInfoHeader->biWidth;
    *rows   =   bmpInfoHeader->biHeight;
    *data   =   (char *) ((char *)(pDib2 + bmpHeader.bfOffBits - sizeof(bmpHeader) - 2));
    fclose(fp2);

	return 1;
}

int close_bmp2(void)     // DIB(Device Independent Bitmap)
{
    free(pDib2);
	return 1;
}
