//Makefile
all: textlcdtest.c libMyPeri.a
	arm-linux-gnueabi-gcc -o textlcdtest textlcdtest.c -l MyPeri -L.
	scp ./btntest ecube@192.168.97.99:~/

libMyPeri.a : lcdtext.o
	arm-linux-gnueabi-ar rc libMyPeri.a lcdtext.o

lcdtext.o: lcdtext.h lcdtext.c
	arm-linux-gnueabi-gcc -c lcdtext.c -o lcdtext.o

clear : 
	rm *.o
	rm libMyPeri.a
