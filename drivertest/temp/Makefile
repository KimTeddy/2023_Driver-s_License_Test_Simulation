all: temptest.elf
	scp ./temptest.elf ecube@192.168.254.99:~/
	echo "		6) send complete"

temptest.elf: libMyPeri.a temptest.o
	arm-linux-gnueabi-gcc temptest.o -l MyPeri -L. -o temptest.elf
	echo "		5) temptest.elf"

temptest.o: temptest.c temp.h
	arm-linux-gnueabi-gcc -c -o temptest.o temptest.c
	echo "		4) temptest.o"

libMyPeri.a: temp.o
	arm-linux-gnueabi-ar rc libMyPeri.a temp.o
	echo "		3) libMyPeri.a"

temp.o: temp.c temp.h
	arm-linux-gnueabi-gcc --static -c -o temp.o temp.c
	echo "		2) temp.o"

clear : 
	rm *.o
	rm libMyPeri.a
	echo "		1) make start"
	make