all: jpegtest.c libMyPeri.a
	arm-linux-gnueabi-gcc -o jpegtesting jpegtest.c -l MyPeri -L. -lpthread

jpegtest.o: jpegtest.c
	arm-linux-gnueabi-gcc -c jpegtest.c -o jpegtest.o


clear : 
	rm *.o