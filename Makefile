# Automated Makefile



CC = g++

CFLAGS = -Wall -O2

LIBS = -lGL -lGLU -lglut

COMPILE = $(CC) $(CFLAGS) -c $(LIBS)

OBJFILES := $(patsubst %.c,%.o,$(wildcard *.c))



all: myprog



myprog: $(OBJFILES)

	$(CC) -o SceneGraph $(OBJFILES)



%.o: %.c

	$(COMPILE) -o $@ $<

clean:
	rm $(OBJFILES) SceneGraph

