# Automated Makefile



CC = g++

LINKER = ld

CFLAGS = -Wall -O2

LIBS = -lGL -lGLU -lglut

COMPILE = $(CC) $(CFLAGS) -c 

TCOMPILE = $(COMPILE) 

COBJFILES := $(wildcard *.c)

OBJFILES := $(patsubst %.c,%.o,$(wildcard *.c))

TFILES := $(patsubst %.cc,%.o,$(wildcard t/*.cc))

TFILES := $(wildcard t/*.cc)

all: myprog



myprog: $(OBJFILES)

	$(CC) -o SceneGraph main.cc $(OBJFILES) $(LIBS)


lib: $(OBJFILES)
	
	$(LINKER) -G $(OBJFILES) -o libscenegraph.so


%.o: %.c

	$(COMPILE)  -o $@ $<

%.o: %.cc
	$(TCOMPILE) -o $@ $<

test: $(TFILES) $(OBJFILES) 
	$(CC) -o ObjTest $(TFILES) $(COBJFILES) $(LIBS)

clean:
	rm $(TFILES) $(OBJFILES) SceneGraph ObjTest

