#ifndef _OBJECT_H
#define _OBJECT_H


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "common.h"

object* obj_create ( );
void obj_destroy ( object* obj ) ;
void obj_operate( object* root, enum OBJ_OPERATION operation, GLfloat x, GLfloat y, GLfloat z);
void obj_load( object* obj, int MODE, void* data, int count );

#endif
