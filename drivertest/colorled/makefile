all: colorledtest

colorledtest: colorledtest.c libMyPeri.a
	arm-linux-gnueabi-gcc -o colorledtest colorledtest.c -l MyPeri -L.

libMyPeri.a: colorled.o
	arm-linux-gnueabi-ar rc libMyPeri.a colorled.o
	arm-linux-gnueabi-ranlib libMyPeri.a

colorled.o: colorled.h colorled.c
	arm-linux-gnueabi-gcc -c colorled.c -o colorled.o

clear:
	rm -f *.o libMyPeri.a colorledtest

