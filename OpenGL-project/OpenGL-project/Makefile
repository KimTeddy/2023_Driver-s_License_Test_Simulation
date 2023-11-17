all: linux.out

linux.out: linux.cpp
	gcc linux.cpp -o linux.out -lglut -lGL -lGLU
	./linux.out
	#ssh ecube@192.168.0.170 ~/teddy/linux.out
	#ssh ecube@192.168.218.19 ~/teddy/linux.out
clear:
	scp kimteddy@192.168.218.19:/home/kimteddy/EmbeddedSystem/OpenGL-project/OpenGL-project/Makefile ~/teddy
	scp kimteddy@192.168.218.19:/home/kimteddy/EmbeddedSystem/OpenGL-project/OpenGL-project/linux.cpp ~/teddy
	make