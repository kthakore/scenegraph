#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "object.h"


object* obj_create()
{
	object* obj = (object*) malloc( sizeof(object) );
	obj->vertices_c = 0;
	obj->children_c = 0;
	return obj;
}


void obj_rotate( object* obj, GLfloat rad)
{

}

void obj_translate( object* obj, GLfloat x, GLfloat y, GLfloat z)
{

}

void obj_destroy( object* obj )
{
	
	free(obj);
}

void obj_render( object* obj )
{

}

void obj_load( object* obj, void* data)
{

}

void obj_closest( object* root, GLfloat x, GLfloat y, GLfloat z)
{


}



