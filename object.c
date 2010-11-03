#include "scenegraph.h"


object* obj_create( scene_manager* sm)
{

	object* obj = sc_get_object( sm, sm->registered  );
	obj->scene = sm;
	obj->id = sm->registered++;
	// Store the bounding sphere 
	obj->bound_sphere_rad = 0;
	obj->children = 0;

	zero_vector( & obj->bound_sphere_loc );
	zero_vector( & obj->r_bound_sphere_loc );
	zero_vector( & obj->location );
	zero_vector( & obj->rotation );
	flood_vector( & obj->scale, 1 );
	obj->polygon_count = 0;
	obj->vector_count = 0;
	obj->is_root = 0;
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
void obj_load( object* obj, int mode, void* data, int vector_count, int poly_count)
{
	//We alread have data loaded
	if( obj->polygon_count > 0 )
		//Lets throw it away :D
		free( obj->polygon_data );

	obj->render_mode = mode;
	obj->polygon_data = (vector*)data;
	obj->polygon_count = poly_count;
	obj->vector_count = vector_count;
	obj_update_bounding_sphere( obj );
}

void obj_update_bounding_sphere( object* obj)
{	
	if( obj->polygon_count <= 0) 
		return;
	//Iterate through the polygons to find the min and max x,y,z
	vector min;
	min.x = 0; min.y = 0; min.z = 0;
	vector max; 
	max.x = 0; max.y = 0; max.z = 0;

	int i;
	for( i = 0; i < obj->vector_count; i++ )
	{

		vector p = (obj->polygon_data)[i];
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
	vector diff;
	sub_vector(&diff, max, min );
	obj->bound_sphere_loc.x = diff.x/2.0;
	obj->bound_sphere_loc.y = diff.y/2.0;
	obj->bound_sphere_loc.z = diff.z/2.0;
	obj->bound_sphere_rad = diff.x/2.0;
	obj->bound_rad_from = 0;

	if( diff.y >= diff.x && diff.y >= diff.z )
	{
		obj->bound_sphere_rad = diff.y/2.0;
		obj->bound_rad_from = 1;
	}
	else if ( diff.z >= diff.y && diff.z >= diff.x )
	{
		obj->bound_sphere_rad = diff.z/2.0;
		obj->bound_rad_from = 2;
	}


}

/*Operation to set the translate values of the object*/
void obj_translate( object* obj, GLfloat x, GLfloat y, GLfloat z)
{
	obj->location.x = x;
	obj->location.y = y;
	obj->location.z = z;
}

/*Operation to set the rotation values of the object*/
void obj_rotate( object* obj, GLfloat x, GLfloat y, GLfloat z)
{
	obj->rotation.x = x;
	obj->rotation.y = y;
	obj->rotation.z = z;

}

void obj_color( object* obj, GLfloat x, GLfloat y, GLfloat z)
{
	obj->polygon_color.x = x;
	obj->polygon_color.y = y;
	obj->polygon_color.z = z;

}

/*Operation to set the scale values of the object*/
void obj_scale( object* obj, GLfloat x, GLfloat y, GLfloat z) 
{
	obj->scale.x = x;
	obj->scale.y = y;
	obj->scale.z = z;

}



object* obj_get_parent( object* obj )
{
	if( obj->is_root )
		return NULL;

	return sc_get_object( obj->scene, obj->parent );

}


void obj_displace_bb( object* obj)
{
	vector displace;
	add_vector( &displace, obj->r_location, obj->bound_sphere_loc );

	GLdouble* out_r = modelview_inv_get(   );

	glPushMatrix();

	add_vector( &displace, obj->r_location, obj->bound_sphere_loc );
	glTranslate_vector( obj->r_location);
	glRotate_vector( obj->r_location, obj->r_rotation, 0);	
	glScalef( obj->scale.x, obj->scale.y, obj->scale.z );	

	glPopMatrix();
	modelview_multiply( &obj->model_proj_bb, &out_r, displace);


}

/*Operation to render the objects */
void obj_render( object* obj)
{
	if( obj->polygon_count > 0 )
	{
		int i;

		glPushMatrix();
		glTranslate_vector( obj->r_location);
		glRotate_vector( obj->r_location, obj->r_rotation, 0);	
		glScalef( obj->scale.x, obj->scale.y, obj->scale.z );	
		glColor3f( obj->polygon_color.x, obj->polygon_color.y, obj->polygon_color.z);
		glBegin( obj->render_mode );	

		for( i = 0; i < obj->vector_count; i++ )
		{
			vector p = (obj->polygon_data)[i];
			glVertex3f( p.x, p.y, p.z);


		} 

		glEnd();
		glPopMatrix();
		

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


	add_vector(&(c->r_location), p->r_location, c->location);

	add_vector(&(c->r_rotation), p->r_rotation, c->rotation);
	//	add_vector(&(c->r_bound_sphere_loc), p->r_bound_sphere_loc, c->bound_sphere_loc);
	//	add_vector(&(c->r_bound_sphere_loc), p->r_location, c->bound_sphere_loc);
}


/* Perform the operation, recursively on all children */
void obj_operate( scene_manager* sm,  object* parent)
{

	unsigned int child;

	if( parent->is_root )
	{
		copy_vector( & parent->r_location, & parent->location);		
		copy_vector( & parent->r_bound_sphere_loc, & parent->bound_sphere_loc);
		copy_vector( & parent->r_rotation, & parent->rotation);
	}

	sc_set_object_to_render( sm, parent );


	//fprintf( stderr, "Parent %d, %d \n", parent->id, parent->children);
	for( child = 0; child < parent->children; child++)
	{


		object* o =  sc_get_object(sm, parent->children_id[child]);
		//	fprintf( stderr, "Parent %d, Child %d \n", parent->id, o->id );
		increment_relative_mats( parent, o );

		obj_operate( sm, o);

	}

}


