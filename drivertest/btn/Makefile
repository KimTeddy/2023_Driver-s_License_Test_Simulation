all: btntest.elf
	scp ./btntest.elf ecube@192.168.254.99:~/
	echo "		6) send complete"

btntest.elf: libMyPeri.a btntest.o
	arm-linux-gnueabi-gcc btntest.o -l MyPeri -L. -o btntest.elf
	echo "		5) btntest.elf"

btntest.o: btntest.c btn.h
	arm-linux-gnueabi-gcc -c -o btntest.o btntest.c
	echo "		4) btntest.o"

libMyPeri.a: btn.o
	arm-linux-gnueabi-ar rc libMyPeri.a btn.o
	echo "		3) libMyPeri.a"

btn.o: btn.c btn.h
	arm-linux-gnueabi-gcc --static -c -o btn.o btn.c
	echo "		2) btn.o"

clear : 
	rm *.o
	rm libMyPeri.a
	echo "		1) make start"
	make