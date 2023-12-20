CC=arm-linux-gnueabi-gcc
AR=arm-linux-gnueabi-ar

all: libtouch.a touchtest

touchtest: libtouch.a main.o
	$(CC) -Xlinker --start-group -lpthread main.o -ltouch -Xlinker --end-group  -L. -o touchtest 

main.o: main.c touch.h
	$(CC) main.c -o main.o -c

libtouch.a: touch.o
	$(AR) rc libtouch.a touch.o

touch.o: touch.c touch.h
	$(CC) touch.c -c -o touch.o
