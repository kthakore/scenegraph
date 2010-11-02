# Automated Makefile



CC = g++

LINKER = ld

CFLAGS = -Wall -g

LIBS = -lGL -lGLU -lglut -lm

COMPILE = $(CC) $(CFLAGS) -c 

OBJFILES := $(patsubst %.c,%.o,$(wildcard *.c))

all: scenegraph

scenegraph: $(OBJFILES)

	$(CC) -o SceneGraph main.cc $(OBJFILES) $(LIBS)

lib: $(OBJFILES)
	
	$(LINKER) -G $(OBJFILES) -o libscenegraph.so


%.o: %.c

	$(COMPILE)  -o $@ $<

clean:
	rm $(OBJFILES) SceneGraph

