all: testing
	scp ./testing ecube@192.168.207.19:~/teddy/
	echo "		5) send complete"

testing: test.c libMyPeri.a
	arm-linux-gnueabi-gcc -o testing test.c -l MyPeri -L. -lpthread
	echo "		4) testing OUTPUT"

test.o: test.c
	arm-linux-gnueabi-gcc -c test.c -o test.o
	echo "		3) test.o"

clear : 
	rm *.o
	rm libMyPeri.a
	echo "		2) remove .o, .a"
	make
	echo "		1) make START"