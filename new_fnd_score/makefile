all: fndscoretest
	scp ./fndscoretest ecube@172.20.10.3:~/testfolder
	echo "		6) send complete"

fndscoretest: fnd_score.o libMyPeri.a
	arm-linux-gnueabi-gcc -o fndscoretest fnd_score.o -l MyPeri -L. -lpthread -lm
	echo "		5) fndscoretest OUTPUT"

fnd_score.o: fnd_score.c fnd.o 
	arm-linux-gnueabi-gcc -c fnd_score.c fnd.o  -o fnd_score.o
	echo "		4) fnd_score.o"

fnd.o: fnd.c fnd.h
	arm-linux-gnueabi-gcc -c fnd.c -o fnd.o
	echo "		3) fnd.o"

clear : 
	rm *.o
	rm libMyPeri.a
	echo "		2) remove .o, .a"
	make
	echo "		1) make START"