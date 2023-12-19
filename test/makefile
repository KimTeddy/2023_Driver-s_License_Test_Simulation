all: testing
	scp ./testing ecube@172.20.10.3:~/testfolder
	echo "		5) send complete"

testing: test.c libMyPeri.a
	arm-linux-gnueabi-gcc -o testing test.c -l MyPeri -L. -lpthread -lm
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