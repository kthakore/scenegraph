#include "scenegraph.h"



void (*op_func_ptr)(object* obj, GLfloat x, GLfloat y, GLfloat z) = NULL;     




object* obj_create( scene_manager* sm)
{

	object* obj = sc_get_object( sm, sm->registered  );

	obj->id = sm->registered++;
	// Store the bounding sphere 
	obj->bound_sphere_rad = 0;
	obj->bound_sphere_loc.x = 0;
	obj->bound_sphere_loc.y = 0;
	obj->bound_sphere_loc.z = 0; 
	obj->children = 0;
	obj->scale.x = 1; obj->scale.y = 1; obj->scale.z = 1;
	obj->location.x = 0, obj->location.y = 0; obj->location.z = 0;
	obj->rotation.x = 0; obj->rotation.y = 0; obj->rotation.z = 0;
	obj->polygon_count = 0;

	obj->is_root = false;
	return obj;
}

void obj_add( object* parent, object* child )
{
	if( parent->children == 7 )
		return;

	parent->children_id[ parent->children++ ] = child->id;
	child->parent = parent->id;
}


/* Load data (polygons), the mode to draw them with during render
 *
 * Additionally set the bounding box 
 */
void obj_load( object* obj, int mode, void* data, int count)
{
	//We alread have data loaded
	if( obj->polygon_count > 0 )
		//Lets throw it away :D
		free( obj->polygon_data );

	obj->render_mode = mode;
	obj->polygon_data = (vertex*)data;
	obj->polygon_count = count;
	obj_update_bounding_sphere( obj );
}

void obj_update_bounding_sphere( object* obj)
{	
	if( obj->polygon_count <= 0) 
		return;
	//Iterate through the polygons to find the min and max x,y,z
	vertex min;
	min.x = 0; min.y = 0; min.z = 0;
	vertex max; 
	max.x = 0; max.y = 0; max.z = 0;

	int i;
	for( i = 0; i < obj->polygon_count; i++ )
	{

		vertex p = (obj->polygon_data)[i];

		if( p.x <= min.x)
			min.x = p.x;
		if( p.y <= min.y)
			min.y = p.y;
		if( p.z <= min.z)
			min.z = p.z;


		if( p.x >= max.x)
			max.x = p.x;
		if( p.y >= max.y)
			max.y = p.y;
		if( p.z >= max.z)
			max.z = p.z;

	}

	// Calculate the middle point and place the bounding sphere there
	GLfloat diff_x = max.x - min.x;
	GLfloat diff_y = max.y - max.y;
	GLfloat diff_z = max.z - max.z;

	obj->bound_sphere_loc.x = diff_x/2.0;
	obj->bound_sphere_loc.y = diff_y/2.0;
	obj->bound_sphere_loc.z = diff_z/2.0;

	obj->bound_sphere_rad = diff_x/2.0;

	if( diff_y >= diff_x && diff_y >= diff_z )
		obj->bound_sphere_rad = diff_y/2.0;
	else if ( diff_z >= diff_y && diff_z >= diff_x )
		obj->bound_sphere_rad = diff_z/2.0;

}

/*Operation to set the translate values of the object*/
void obj_translate( object* obj, GLfloat x, GLfloat y, GLfloat z)
{

	fprintf( stderr, "Translate: %p from (%f,%f,%f) \n", obj , x,y,z );
	obj->location.x = x;
	obj->location.y = y;
	obj->location.z = z;
}

/*Operation to set the rotation values of the object*/
void obj_rotate( object* obj, GLfloat x, GLfloat y, GLfloat z)
{
	fprintf( stderr, "Rotate: %p from (%f,%f,%f) \n", obj , x,y,z );
	obj->rotation.x = x;
	obj->rotation.y = y;
	obj->rotation.z = z;

}

/*Operation to set the scale values of the object*/
void obj_scale( object* obj, GLfloat x, GLfloat y, GLfloat z) 
{

	fprintf( stderr, "Scale: %p from (%f,%f,%f) \n", obj , x,y,z );
	obj->scale.x = x;
	obj->scale.y = y;
	obj->scale.z = z;

}

/*Operation to render the objects */
void obj_render( object* obj, GLfloat x, GLfloat y, GLfloat z )
{
	fprintf( stderr, "Rendered: %p from (%f,%f,%f) \n", obj , x,y,z );

	if( obj->polygon_count > 0 )
	{
		int i;

		glPushMatrix();
		glScalef( obj->scale.x, obj->scale.y, obj->scale.z );	
		glTranslatef( obj->r_location.x, obj->r_location.y, obj->r_location.z );
		glRotatef( obj->rotation.x, obj->rotation.y, obj->rotation.z, 0 );

		fprintf(stderr, "\n Object Location %p (%f,%f,%f) \n", obj, obj->r_location.x, obj->r_location.y, obj->r_location.z );
		//fprintf(stderr, "Polygon Rotate (%f,%f,%f) \n", obj->rotation.x, obj->rotation.y, obj->rotation.z );
		//fprintf(stderr, "Polygon Scale (%f,%f,%f) \n", obj->scale.x, obj->scale.y, obj->scale.z );

		glColor3f( obj->polygon_color.x, obj->polygon_color.y, obj->polygon_color.z);
		glBegin( obj->render_mode );	
		
	
		for( i = 0; i < obj->polygon_count; i++ )
		{
			vertex p = (obj->polygon_data)[i];
			glVertex3f( p.x, p.y, p.z);


		} 

		glEnd();
		glPopMatrix();
	}
}


/*Convert the operation into a function pointer (Simple VTABLE implementation) */
void obj_switch_operation( enum OBJ_OPERATION op)
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

// Destroy the object and the polygon data
void obj_destroy( object* obj)
{
	if( obj->polygon_count > 0)
		free( obj->polygon_data );
	free( obj );
}

void increment_relative_mats( object* p, object* c )
{

 	add_vertex(&(c->r_location), p->r_location, c->location);

}

/* Perform the operation, recursively on all children */
void obj_operate( scene_manager* sm,  object* parent, enum OBJ_OPERATION operation, GLfloat x, GLfloat y, GLfloat z)
{
	unsigned int child;

	obj_switch_operation( operation );

	for( child = 0; child < parent->children; child++)
	{
		object* o =  sc_get_object(sm, parent->children_id[child]);
		increment_relative_mats( parent, o );
		fprintf( stderr, "\tOperating on %p, child %d\n", o, child);

		obj_operate( sm, o, operation, x, y, z);

	}
	(*op_func_ptr) ( parent, x,y,z );


}


