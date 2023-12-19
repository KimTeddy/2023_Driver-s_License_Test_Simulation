#include <iostream>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include "bitmapFileHeader.h"
#include "libfbdev.h"
#include "libbmp.h"

#define WIDTH 800
#define HEIGHT 600

void ScreenCapture(const char* strFilePath)
{
   //비트맵 파일 처리를 위한 헤더 구조체
   BITMAPFILEHEADER BMFH;
   BITMAPINFOHEADER BMIH;

   int nWidth = WIDTH;
   int nHeight = HEIGHT;
   unsigned long dwQuadrupleWidth = (nWidth % 4) ? ((nWidth)+(4 - (nWidth % 4))) : (nWidth);

   //비트맵 파일 헤더 처리
   BMFH.bfType = 0x4D42;
   BMFH.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (dwQuadrupleWidth * 3 * nHeight);
   BMFH.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

   //비트맵 인포 헤더 처리
   BMIH.biSize = sizeof(BITMAPINFOHEADER);
   BMIH.biWidth = nWidth;
   BMIH.biHeight = nHeight;
   BMIH.biPlanes = 1;
   BMIH.biBitCount = 24;
   BMIH.biCompression = 0;
   BMIH.biSizeImage = dwQuadrupleWidth * 3 * nHeight;
   BMIH.biXPelsPerMeter = 0;
   BMIH.biYPelsPerMeter = 0;
   BMIH.biClrUsed = 0;
   BMIH.biClrImportant = 0;

   GLbyte* pPixelData = new GLbyte[dwQuadrupleWidth * 3 * nHeight];

   glReadPixels(
       0, 0,
       nWidth, nHeight,
       GL_RGB,
       GL_UNSIGNED_BYTE,
       pPixelData
   );

   FILE* outFile = fopen(strFilePath, "wb");
   if (outFile == NULL)
   {
       printf("에러");
       return;
   }

   fwrite(&BMFH, sizeof(char), sizeof(BITMAPFILEHEADER), outFile);
   fwrite(&BMIH, sizeof(char), sizeof(BITMAPINFOHEADER), outFile);
   fwrite(pPixelData, sizeof(unsigned char), BMIH.biSizeImage, outFile);

   fclose(outFile);
   delete[] pPixelData;
}

int main() {
    // Initialize EGL
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY) {
        fprintf(stderr, "Error: Unable to get EGL display\n");
        return 1;
    }

    if (!eglInitialize(display, NULL, NULL)) {
        fprintf(stderr, "Error: Unable to initialize EGL\n");
        return 1;
    }

    // Configure EGL
    EGLint configAttributes[] = {
        EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_NONE
    };

    EGLConfig config;
    EGLint numConfigs;
    if (!eglChooseConfig(display, configAttributes, &config, 1, &numConfigs)) {
        fprintf(stderr, "Error: Unable to choose EGL config\n");
        return 1;
    }

    // Create PBuffer Surface
    EGLint pbufferAttributes[] = {
        EGL_WIDTH, WIDTH,
        EGL_HEIGHT, HEIGHT,
        EGL_NONE
    };

    EGLSurface pbuffer = eglCreatePbufferSurface(display, config, pbufferAttributes);
    if (pbuffer == EGL_NO_SURFACE) {
        fprintf(stderr, "Error: Unable to create PBuffer surface\n");
        return 1;
    }

    // Create EGL Context
    EGLint contextAttributes[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    EGLContext context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttributes);
    if (context == EGL_NO_CONTEXT) {
        fprintf(stderr, "Error: Unable to create EGL context\n");
        return 1;
    }

    // Make current
    if (!eglMakeCurrent(display, pbuffer, pbuffer, context)) {
        fprintf(stderr, "Error: Unable to make EGL context current\n");
        return 1;
    }

    // Set up OpenGL data (draw a simple triangle)
    GLfloat vertices[] = {
        0.0f,  0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Save OpenGL rendering to raw image
     char *imageData = ( char *)malloc(WIDTH * HEIGHT * 3);
    glReadPixels(0, 0, WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, imageData);

    // Save raw image
    //saveRawImage("triangle_image.raw", imageData, WIDTH, HEIGHT);
    //ScreenCapture("triangle_image.bmp");
//----------------------------------------------------------------
    int screen_width;
    int screen_height;
    int bits_per_pixel;
    int line_length;
    int cols = 0, rows = 0;
	char *data;


    printf("=================================\n");
    printf("Frame buffer Application - Bitmap\n");
    printf("=================================\n\n");



	//FrameBuffer init
    if ( fb_init(&screen_width, &screen_height, &bits_per_pixel, &line_length) < 0 )
	{
		printf ("FrameBuffer Init Failed\r\n");
		return 0;
	}

	//Clear FB.
	fb_clear();

	//FileRead
    // if (read_bmp(imageData, &data, &cols, &rows) < 0)
	// {
	// 	printf ("File open failed\r\n");
	// 	return 0;
	// }
    // printf("\tBitmapFile: %dx%d pixels\n", cols, rows);
    // printf("\tFB Screen: %dx%d\n", screen_width, screen_height);
    // printf("\tFB bits_per_pixel: %d, FB line_length: %d\n", bits_per_pixel, line_length);
	
	//FileWrite
	fb_write(imageData, cols,rows);
    
	close_bmp();
	fb_close();

//-----------------------------------

    // Cleanup
    free(imageData);
    glDeleteBuffers(1, &vertexBuffer);
    eglDestroyContext(display, context);
    eglDestroySurface(display, pbuffer);
    eglTerminate(display);

    return 0;
}
