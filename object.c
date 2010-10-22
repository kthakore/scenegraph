#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>

#include "object.h"


object* obj_create()
{
	object* obj = (object*) malloc( sizeof(object) );
	obj->children_c = 0;
	return obj;
}



void obj_translate( object* obj, GLfloat x, GLfloat y, GLfloat z)
{

	fprintf( stderr, "translate: %p from (%f,%f,%f) ", obj , x,y,z );
}

void obj_rotate( object* obj, GLfloat x, GLfloat y, GLfloat z)
{
	fprintf( stderr, "Rotate: %p from (%f,%f,%f) ", obj , x,y,z );
}

void obj_scale( object* obj, GLfloat x, GLfloat y, GLfloat z) 
{

	fprintf( stderr, "Scale: %p from (%f,%f,%f) ", obj , x,y,z );

}

void obj_render( object* obj, GLfloat x, GLfloat y, GLfloat z )
{
	fprintf( stderr, "Rendered: %p from (%f,%f,%f) ", obj , x,y,z );
}

void obj_switch_operation( OBJ_OPERATION op)
{


	switch( op )
	{
		case TRANSLATE:
			op_func_ptr = &obj_translate;
			break;
		case ROTATE:
			op_func_ptr = &obj_rotate;
			break;
		case SCALE:
			op_func_ptr = &obj_scale;
			break;
		case RENDER:
			op_func_ptr = &obj_render;
			break;
		default:
			break;

	}
}
void obj_load( object* obj, void* data)
{
	obj->polygon_data = (GLfloat*)data;
}

void obj_closest( object* root, GLfloat x, GLfloat y, GLfloat z)
{


}

void obj_destroy( object* obj )
{

	free( obj );
}


void obj_operate( object* parent, OBJ_OPERATION operation, GLfloat x, GLfloat y, GLfloat z)
{

	obj_switch_operation( operation );

	(*op_func_ptr) ( parent, x,y,z);

	//Apply rotate to our selves

	//For all our children
	//rotate on all of them
	//return if parent = null;

}


