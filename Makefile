# Automated Makefile



CC = g++

CFLAGS = -Wall -O2

LIBS = -lGL -lGLU -lglut

COMPILE = $(CC) $(CFLAGS) -c $(LIBS)

TCOMPILE = $(COMPILE) 

OBJFILES := $(patsubst %.c,%.o,$(wildcard *.c))

TFILES := $(patsubst %.cc,%.o,$(wildcard t/*.cc))


all: myprog



myprog: $(OBJFILES)

	$(CC) -o SceneGraph main.cc $(OBJFILES) $(LIBS)



%.o: %.c

	$(COMPILE) -o $@ $<

%.o: %.cc
	$(TCOMPILE) -o $@ $<

test: $(TFILES) $(OBJFILES)
	$(CC) -o ObjTest $(TFILES) $(OBJFILES) $(LIBS)

clean:
	rm $(TFILES) $(OBJFILES) SceneGraph ObjTest

