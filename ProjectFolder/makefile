all: test.c libMyPeri.a
	arm-linux-gnueabi-gcc -o testing test.c -l MyPeri -L. -lpthread

test.o: test.c
	arm-linux-gnueabi-gcc -c test.c -o test.o

clear : 
	rm *.o
	rm libMyPeri.a