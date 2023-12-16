all: accelMagGyrotest.elf
	scp ./accelMagGyrotest.elf ecube@192.168.254.19:~/teddy/test/
	echo "		6) send complete"

accelMagGyrotest.elf: libMyPeri.a accelMagGyrotest.o
	arm-linux-gnueabi-gcc accelMagGyrotest.o -l MyPeri -L. -o accelMagGyrotest.elf -lm
	echo "		5) accelMagGyrotest.elf"

accelMagGyrotest.o: accelMagGyrotest.c
	arm-linux-gnueabi-gcc -c -o accelMagGyrotest.o accelMagGyrotest.c -lm
	echo "		4) accelMagGyrotest.o"

libMyPeri.a: accelMagGyro.o
	arm-linux-gnueabi-ar rc libMyPeri.a accelMagGyro.o
	echo "		3) libMyPeri.a"

accelMagGyro.o: accelMagGyro.c accelMagGyro.h
	arm-linux-gnueabi-gcc --static -c -o accelMagGyro.o accelMagGyro.c
	echo "		2) accelMagGyro.o"

clear : 
	rm *.o
	rm libMyPeri.a
	echo "		1) make start"
	make