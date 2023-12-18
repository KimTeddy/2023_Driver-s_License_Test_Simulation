all: bmptest.o libMyPeri.a
	arm-linux-gnueabi-gcc -o bmptesting bmptest.c -l MyPeri -L. -lpthread

bmptest.o: bmptest.c
	arm-linux-gnueabi-gcc -c bmptest.c -o bmptest.o


clear : 
	rm *.o