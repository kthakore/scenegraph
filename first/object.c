#include "scenegraph.h"

object* obj_create( scene_manager* sm)
{

	object* obj = sc_get_object( sm, sm->registered++  );

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
	return obj;
}



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

