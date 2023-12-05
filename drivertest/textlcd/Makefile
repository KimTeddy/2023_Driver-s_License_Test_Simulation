all: textlcdtest.elf
	scp ./textlcdtest.elf ecube@192.168.254.19:~/joo/
	echo "		6) send complete"

textlcdtest.elf: libMyPeri.a textlcdtest.o
	arm-linux-gnueabi-gcc textlcdtest.o -l MyPeri -L. -o textlcdtest.elf
	echo "		5) textlcdtest.elf"

textlcdtest.o: textlcdtest.c
	arm-linux-gnueabi-gcc -c -o textlcdtest.o textlcdtest.c
	echo "		4) textlcdtest.o"

libMyPeri.a: lcdtext.o
	arm-linux-gnueabi-ar rc libMyPeri.a lcdtext.o
	echo "		3) libMyPeri.a"

lcdtext.o: lcdtext.c lcdtext.h
	arm-linux-gnueabi-gcc --static -c -o lcdtext.o lcdtext.c
	echo "		2) lcdtext.o"

clear : 
	rm *.o
	rm libMyPeri.a
	echo "		1) make start"
	make