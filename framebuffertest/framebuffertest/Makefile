all: egl

egl: linux.cpp
	g++ linux.cpp libfbdev.c -o egl -lglut -lGL -lGLU -lm -lEGL -lGLESv2 -ldrm -lgbm