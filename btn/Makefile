all : libMyPeri
libMyPeri.a : button.o led.o
	arm-linux-gnueabi-ar rc libMyPeri.a led.o button.o
button.o : button.h button.c
	arm-linux-gnueabi-gcc -c button.c -o button.o
led.o : led.h led.c
	arm-linux-gnueabi-gcc - led.c -o led.o