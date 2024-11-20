LIBS     = -lGL -lGLU -lglut
CFLAGS   = -Wall -Wextra
TARGET   = main
COMPILER = gcc

main: main.c color.h rng.h
	$(COMPILER) $(CFLAGS) -o $(TARGET) main.c $(LIBS)
