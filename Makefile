# Automated Makefile



CC = clang

LINKER = ld

CFLAGS = -Wall -O2

LIBS = -lGL -lGLU -lglut

COMPILE = $(CC) $(CFLAGS) -c 

TCOMPILE = $(COMPILE) 

OBJFILES := $(patsubst %.c,%.o,$(wildcard *.c))

TFILES := $(patsubst %.cc,%.o,$(wildcard t/*.cc))


all: myprog



myprog: $(OBJFILES)

	$(CC) -o SceneGraph main.cc $(OBJFILES) $(LIBS)


lib: $(OBJFILES)
	
	$(LINKER) -G $(OBJFILES) -o libscenegraph.so


%.o: %.c

	$(COMPILE) -fPIC -o $@ $<

%.o: %.cc
	$(TCOMPILE) -o $@ $<

test: $(TFILES) lib
	$(CC) $(OBJFILES) $(LIBS) -o ObjTest $(TFILES) 
clean:
	rm $(TFILES) $(OBJFILES) SceneGraph ObjTest

