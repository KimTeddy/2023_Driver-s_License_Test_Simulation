all: testing
	scp ./testing ecube@172.20.10.3:~/testfolder/
	echo "		5) send complete"

testing: test.o libMyPeri.a libtouch.a
	arm-linux-gnueabi-gcc -Xlinker --start-group -lpthread test.o -ltouch -lMyPeri -lm -Xlinker --end-group  -L. -o testing
	echo "		4) testing OUTPUT"

test.o: test.c
	arm-linux-gnueabi-gcc -c test.c -o test.o
	echo "		3) test.o"

clear : 
	rm *.o
	echo "		2) remove .o"
	make
	echo "		1) make START"