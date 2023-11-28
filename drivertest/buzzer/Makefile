all: libMyPeri.a
	arm-linux-gnueabi-gcc -o buzzertest.elf buzzertest.c -l MyPeri -L.
	scp ./buzzertest.elf ecube@192.168.97.99:~/teddy/

libMyPeri.a: buzzer.o
	arm-linux-gnueabi-ar rc libMyPeri.a buzzer.o

buzzer.o: buzzer.h buzzer.c
	arm-linux-gnueabi-gcc -c buzzer.c -o buzzer.o

clear : 
	rm *.o
	rm libMyPeri.a
	make