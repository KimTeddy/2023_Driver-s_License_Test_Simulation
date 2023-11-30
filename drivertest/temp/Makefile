all : temp.c libMyPeri.a
	arm-linux-gnueabi-gcc -o temptest temptest.c -l MyPeri -L.
	scp ./temptest ecube@192.168.97.99:~/

libMyPeri.a : temp.o
	arm-linux-gnueabi-ar rc libMyPeri.a temp.o

temp.o : temp.h temp.c
	arm-linux-gnueabi-gcc -c temp.c -o temp.o	

clear :
	rm *.o
	rm libMyPeri.a	