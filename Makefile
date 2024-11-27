LIBS     = -lGL -lGLU -lglut -lm
CFLAGS   = -Wall -Wextra
TARGET   = main
COMPILER = gcc

main: main.c color.h rng.h cube.h vec3.h rect.h pig.h bomb.h texture.h
	$(COMPILER) $(CFLAGS) -o $(TARGET) main.c $(LIBS)
