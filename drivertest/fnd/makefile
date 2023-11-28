all: fndtest.c libMyPeri.a
	arm-linux-gnueabi-gcc -o fndtest fndtest.c -l MyPeri -L.

libMyPeri.a : fnd.o
	arm-linux-gnueabi-ar rc libMyPeri.a fnd.o

fnd.o: fnd.h fnd.c
	arm-linux-gnueabi-gcc -c fnd.c -o fnd.o

clear : 
	rm *.o
	rm libMyPeri.a
