libMyPeri.a : btn.o 
	arm-linux-gnueabi-ar rc libMyPeri.a btn.o
button.o : btn.h btn.c
	arm-linux-gnueabi-gcc -c btn.c -o btn.o

all: btntest.c libMyPeri.a
	arm-linux-gnueabi-gcc -o btntest btntest.c -l MyPeri -L.

libMyPeri.a : btn.o
	arm-linux-gnueabi-ar rc libMyPeri.a btn.o

btn.o: btn.h btn.c
	arm-linux-gnueabi-gcc -c btn.c -o btn.o

clear : 
	rm *.o
	rm libMyPeri.a
