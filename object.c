#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>

#include "object.h"

void (*op_func_ptr)(object* obj, GLfloat x, GLfloat y, GLfloat z) = NULL;     


object* obj_create()
{
	object* obj = (object*) malloc( sizeof(object) );
	obj->children_c = 0;
	obj->scale.x = 1; obj->scale.y = 1; obj->scale.z = 1;
	obj->location.x = 0, obj->location.y = 0; obj->location.z = 0;
	obj->rotation.x = 0; obj->rotation.y = 0; obj->rotation.z = 0;
	return obj;
}



void obj_translate( object* obj, GLfloat x, GLfloat y, GLfloat z)
{

	fprintf( stderr, "Translate: %p from (%f,%f,%f) \n", obj , x,y,z );
	obj->location.x = obj->location.x + x;
	obj->location.y = obj->location.y + y;
	obj->location.z = obj->location.z + z;
}

void obj_rotate( object* obj, GLfloat x, GLfloat y, GLfloat z)
{
	fprintf( stderr, "Rotate: %p from (%f,%f,%f) \n", obj , x,y,z );
	obj->rotation.x = obj->rotation.x + x;
	obj->rotation.y = obj->rotation.y + y;
	obj->rotation.z = obj->rotation.z + z;

}

void obj_scale( object* obj, GLfloat x, GLfloat y, GLfloat z) 
{

	fprintf( stderr, "Scale: %p from (%f,%f,%f) \n", obj , x,y,z );
	obj->scale.x = obj->scale.x + x;
	obj->scale.y = obj->scale.y + y;
	obj->scale.z = obj->scale.z + z;

}

void obj_render( object* obj, GLfloat x, GLfloat y, GLfloat z )
{
	fprintf( stderr, "Rendered: %p from (%f,%f,%f) \n", obj , x,y,z );

	if( obj->polygon_count > 0 )
	{
		int i;

		glScalef( obj->scale.x, obj->scale.y, obj->scale.z );	
		glTranslatef( obj->location.x, obj->location.y, obj->location.z );
		glRotatef( obj->rotation.x, obj->rotation.y, obj->rotation.z, 0 );

		fprintf(stderr, "Polygon Location (%f,%f,%f) \n", obj->location.x, obj->location.y, obj->location.z );
		fprintf(stderr, "Polygon Rotate (%f,%f,%f) \n", obj->rotation.x, obj->rotation.y, obj->rotation.z );
		fprintf(stderr, "Polygon Scale (%f,%f,%f) \n", obj->scale.x, obj->scale.y, obj->scale.z );

		glColor3f( obj->polygon_color.x, obj->polygon_color.y, obj->polygon_color.z);
		glBegin( obj->render_mode );	


		for( i = 0; i < obj->polygon_count; i++ )
		{
			vertex p = (obj->polygon_data)[i];
			glVertex3f( p.x, p.y, p.z);


		} 

		glEnd();
	}
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
			op_func_ptr = &obj_render;
			break;

	}
}
void obj_load( object* obj, int mode,  void* data, int count)
{
	obj->render_mode = mode;
	obj->polygon_data = (vertex*)data;

	obj->polygon_count = count;
}

void obj_closest( object* root, GLfloat x, GLfloat y, GLfloat z)
{


}

void obj_destroy( object* obj)
{
	if( obj->polygon_count > 0)
		free( obj->polygon_data );
	free( obj );
}


void obj_operate( object* parent, OBJ_OPERATION operation, GLfloat x, GLfloat y, GLfloat z)
{
	unsigned int child;
	obj_switch_operation( operation );

	for( child = 0; child < parent->children_c; child++)
	{
		object* o =  ((object**)(parent->children))[child];

		fprintf( stderr, "Operating on %p, child %d \n", o, child);
		obj_operate( o, operation, x, y, z);

	}
	(*op_func_ptr) ( parent, x,y,z );


}


