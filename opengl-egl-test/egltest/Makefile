all: egl

egl: triangle.cpp
	#gcc triangle.c -o egl -lglut -lGL -lGLU -lm -lEGL -lGLESv2 -ldrm -lgbm
	g++ triangle.cpp libfbdev.c -o egl -lglut -lGL -lGLU -lm -lEGL -lGLESv2 -ldrm -lgbm