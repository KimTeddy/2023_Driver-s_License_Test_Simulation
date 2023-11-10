all: linux.out

linux.out: linux.cpp
	gcc linux.cpp -o linux.out -lglut -lGL -lGLU
	scp linux.out ecube@192.168.0.170:~/teddy/
	scp linux.out ecube@192.168.46.19:~/teddy/