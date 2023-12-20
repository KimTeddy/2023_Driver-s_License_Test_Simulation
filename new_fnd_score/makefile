all: fnd_score.elf
	#scp ./fnd_score.elf ecube@172.20.10.3:~/testfolder
	scp ./fnd_score.elf ecube@192.168.207.19:~/teddy/
	echo "		6) all complete"

fnd_score.elf: libMyPeri.a fnd_score.o
	arm-linux-gnueabi-gcc fnd_score.o -l MyPeri -L. -o fnd_score.elf
	echo "		5) fnd_score.elf"

fnd_score.o: fnd_score.c fnd.h
	arm-linux-gnueabi-gcc -c -o fnd_score.o fnd_score.c
	echo "		4) fnd_score.o"

libMyPeri.a: fnd.o
	arm-linux-gnueabi-ar rc libMyPeri.a fnd.o
	echo "		3) libMyPeri.a"

fnd.o: fnd.c fnd.h
	arm-linux-gnueabi-gcc --static -c -o fnd.o fnd.c
	echo "		2) fnd.o"

clear : 
	rm *.o
	rm libMyPeri.a
	echo "		1) make start"
	make