all : colorledtest.c libMyPeri.a
	arm-linux-gnueabi-gcc -o colorledtest colorledtest.c -l MyPeri -L.
	scp ./btntest ecube@192.168.97.99:~/

libMyPeri.a : colorled.o
	arm-linux-gnueabi-ar rc libMyPeri.a colorled.o

colorled.o : colorled.h colorled.c
	arm-linux-gnueabi-gcc -c colorled.c -o colorled.o	

clear :
	rm *.o
	rm libMyPeri.a	