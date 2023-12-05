all: colorledtest.elf
	scp ./colorledtest.elf ecube@192.168.254.99:~/
	echo "		6) send complete"

colorledtest.elf: libMyPeri.a colorled.o
	arm-linux-gnueabi-gcc colorled.o -l MyPeri -L. -o colorledtest.elf
	echo "		5) colorledtest.elf"

buzzertest.o: colorledtest.c colorled.h
	arm-linux-gnueabi-gcc -c -o colorled.o colorledtest.c
	echo "		4) colorled.o"

libMyPeri.a: colorled.o
	arm-linux-gnueabi-ar rc libMyPeri.a colorled.o
	echo "		3) libMyPeri.a"

buzzer.o: colorled.c colorled.h
	arm-linux-gnueabi-gcc --static -c -o colorled.o colorled.c
	echo "		2) colorled.o"

clear : 
	rm *.o
	rm libMyPeri.a
	echo "		1) make start"
	make