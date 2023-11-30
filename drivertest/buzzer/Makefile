all: buzzertest.elf
	scp ./buzzertest.elf ecube@192.168.97.19:~/teddy/test/
	echo "		6) send complete"

buzzertest.elf: libMyPeri.a buzzertest.o
	arm-linux-gnueabi-gcc buzzertest.o -l MyPeri -L. -o buzzertest.elf
	echo "		5) buzzertest.elf"

buzzertest.o: buzzertest.c buzzer_pitch.h
	arm-linux-gnueabi-gcc -c -o buzzertest.o buzzertest.c
	echo "		4) buzzertest.o"

libMyPeri.a: buzzer.o
	arm-linux-gnueabi-ar rc libMyPeri.a buzzer.o
	echo "		3) libMyPeri.a"

buzzer.o: buzzer.c buzzer.h
	arm-linux-gnueabi-gcc --static -c -o buzzer.o buzzer.c
	echo "		2) buzzer.o"

clear : 
	rm *.o
	rm libMyPeri.a
	echo "		1) make start"
	make