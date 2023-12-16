all: libMyPeri.a

libMyPeri.a: accelMagGyro.o button.o buzzer.o colorled.o fnd.o lcdtext.o led.o temp.o
	arm-linux-gnueabi-ar rc libMyPeri.a accelMagGyro.o button.o buzzer.o colorled.o fnd.o lcdtext.o led.o temp.o

accelMagGyro.o: accelMagGyro.c accelMagGyro.h
	arm-linux-gnueabi-gcc -o accelMagGyro.o -c accelMagGyro.c 

button.o: button.h button.c
	arm-linux-gnueabi-gcc -c button.c -o button.o

buzzer.o: buzzer.h buzzer.c
	arm-linux-gnueabi-gcc -c buzzer.c -o buzzer.o

colorled.o: colorled.h colorled.c
	arm-linux-gnueabi-gcc -c colorled.c -o colorled.o

fnd.o: fnd.h fnd.c
	arm-linux-gnueabi-gcc -c fnd.c -o fnd.o

lcdtext.o: lcdtext.h lcdtext.c
	arm-linux-gnueabi-gcc -c lcdtext.c -o lcdtext.o

led.o: led.h led.c
	arm-linux-gnueabi-gcc -c led.c -o led.o

temp.o: temp.h temp.c
	arm-linux-gnueabi-gcc -c temp.c -o temp.o

clean: 
	rm -f *.o *.a
