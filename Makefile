# Automated Makefile



CC = g++

CFLAGS = -Wall -O2

LIBS = -lGL -lGLU -lglut

COMPILE = $(CC) $(CFLAGS) -c $(LIBS)

OBJFILES := $(patsubst %.c,%.o,$(wildcard *.c))

TFILES := $(patsubst %.cc,%.o,$(wildcard t/*.cc))


all: myprog



myprog: $(OBJFILES)

	$(CC) -o SceneGraph $(OBJFILES) $(LIBS)



%.o: %.c

	$(COMPILE) -o $@ $<

%.o: %.cc
	$(COMPILE) -o $@ $<

test: $(TFILES)
	$(CC) -o ObjTest $(TFILES) $(LIBS)

clean:
	rm $(OBJFILES) SceneGraph

