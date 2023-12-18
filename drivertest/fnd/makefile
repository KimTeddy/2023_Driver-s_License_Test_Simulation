all: fndtest.elf
	echo "		6) all complete"

fndtest.elf: libMyPeri.a fndtest.o
	arm-linux-gnueabi-gcc fndtest.o -l MyPeri -L. -o fndtest.elf
	echo "		5) fndtest.elf"

fndtest.o: fndtest.c fnd.h
	arm-linux-gnueabi-gcc -c -o fndtest.o fndtest.c
	echo "		4) fndtest.o"

libMyPeri.a: fnd.o
	arm-linux-gnueabi-ar rc libMyPeri.a fnd.o
	echo "		3) libMyPeri.a"

fnd.o: fnd.c fnd.h
	arm-linux-gnueabi-gcc --static -c -o fnd.o fnd.c
	echo "		2) fnd.o"

clear : 
	rm *.o
	rm libMyPeri.a
	echo "		1) make start"
	make