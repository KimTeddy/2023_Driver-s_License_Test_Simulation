all: ledtest.c libMyPeri.a
	arm-linux-gnueabi-gcc -o ledtest ledtest.c -l MyPeri -L.

libMyPeri.a : led.o
	arm-linux-gnueabi-ar rc libMyPeri.a led.o

led.o: led.h led.c
	arm-linux-gnueabi-gcc -c led.c -o led.o

clear : 
	rm *.o
	rm libMyPeri.a
