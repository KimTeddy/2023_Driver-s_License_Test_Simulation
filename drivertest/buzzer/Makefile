all: libMyPeri.a
libMyPeri.a: buzzer.o
	arm-linux-gnueabi-ar rc libMyPeri.a buzzer.o
buzzer.o: buzzer.h buzzer.c
	arm-linux-gnueabi-gcc -c buzzer.c -o buzzer.o