all: linux.out

linux.out: linux.cpp
	gcc linux.cpp -o linux.out -lglut -lGL -lGLU
	./linux.out
	ssh ecube@192.168.0.170 ~/teddy/linux.out