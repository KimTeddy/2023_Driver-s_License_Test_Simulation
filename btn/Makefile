libMyPeri.a : btn.o led.o 
	arm-linux-gnueabi-ar rc libMyPeri.a led.o btn.o
button.o : btn.h btn.c
	arm-linux-gnueabi-gcc -c btn.c -o btn.o
led.o : led.h led.c
	arm-linux-gnueabi-gcc - led.c -o led.o