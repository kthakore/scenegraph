#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "object.h"

int main (int argc, char ** argv)
{

	object* obj = obj_create();

	obj_destroy ( obj, false);
	return 0;
}
