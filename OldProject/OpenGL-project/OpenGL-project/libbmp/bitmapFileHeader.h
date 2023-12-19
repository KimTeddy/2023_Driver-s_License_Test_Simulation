#ifndef _BITMAP_FILE_HEADER_
#define _BITMAP_FILE_HEADER_

//Bitmap Header.
// File Header
typedef struct 
{
    unsigned short  bfType;
    unsigned int    bfSize;         // 4 byte
    unsigned short  bfReserved1;    // 2 byte
    unsigned short  bfReserved2;    // 2 byte
    unsigned int    bfOffBits;      // 4 byte
} BITMAPFILEHEADER;

// Image Header
typedef struct 
{
    unsigned long    biSize;             // 4 byte
    long             biWidth;            // 4 byte
    long             biHeight;           // 4 byte
    unsigned short   biPlanes;           // 2 byte
    unsigned short   biBitCount;         // 2 byte
    unsigned long    biCompression;      // 4 byte
    unsigned long    biSizeImage;        // 4 byte
    long             biXPelsPerMeter;    // 4 byte
    long             biYPelsPerMeter;    // 4 byte
    unsigned long    biClrUsed;          // 4 byte
    unsigned long    biClrImportant;     // 4 byte
} BITMAPINFOHEADER;

// Color Table
typedef struct 
{
    unsigned char   rgbBlue;        // 1 byte
    unsigned char   rgbGreen;       // 1 byte
    unsigned char   rgbRed;         // 1 byte
    unsigned char   rgbReserved;    // 1 byte
} RGBQUAD;

// Pixel Data
typedef struct 
{
    BITMAPINFOHEADER    bmiHeader;
    RGBQUAD             bmiColors[1];
} BITMAPINFO;

#define BIT_VALUE_24BIT   24

#endif
