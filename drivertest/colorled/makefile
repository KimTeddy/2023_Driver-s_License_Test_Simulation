all: colorledtest.c libMyPeri.a
	arm-linux-gnueabi-gcc -o colorledtest colorledtest.c -l MyPeri -L.

libMyPeri.a : colorled.o
	arm-linux-gnueabi-ar rc libMyPeri.a colorled.o

led.o: colorled.h colorled.c
	arm-linux-gnueabi-gcc -c colorledled.c -o colorled.o

clear : 
	rm *.o
	rm libMyPeri.a
