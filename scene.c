#include "scenegraph.h"
#include <math.h>

scene_manager* sc_init(int objects) {

	int i;
	scene_manager* Scene = (scene_manager*)malloc( sizeof(scene_manager) );

	Scene->objects = objects;
	Scene->registered = 0;
	// Malloc our object registry
	Scene->object_registry = (object*)malloc(sizeof(object) * objects ); 

	// Malloc the render marshall too
	Scene->rm_all = (linked_object*)malloc(sizeof(linked_object) * objects );

	// Prepare them with their object* 
	for( i = 0; i < objects; i++ )
	{
		Scene->rm_all[i].next = NULL;
		Scene->rm_all[i].previous = NULL;
		Scene->rm_all[i].object_ptr = sc_get_object( Scene, i);
	}

	Scene->root_object_id = 0; //Assuming this for now
	sc_update_frustum(Scene); 

	return Scene;
}

void  sc_set_root( scene_manager* scene, object* root)
{
	scene->root_object_id = root->id;
	root->is_root = true;	

	copy_vertex( &(root->r_location) , &(root->location) ); 	
}

object* sc_get_object( scene_manager* sm, int id )
{
	if( id < 0 || id > sm->objects )
	{
		fprintf(stderr, "Invalid object id: %d .", id );
		return NULL;
	}
	return &( (sm->object_registry)[id] );
}

linked_object* sc_get_rm_object( scene_manager* sm, int id )
{
	if( id < 0 || id > sm->objects )
	{
		fprintf(stderr, "Invalid object id: %d .", id );
		return NULL;
	}
	return &( (sm->rm_all)[id] );

}


void sc_render( scene_manager* sm)
{

//	sc_update_frustum( sm );
	object* root = sc_get_object( sm, sm->root_object_id );
	
	obj_operate( sm, root, RENDER, sm->camera.x, sm->camera.y, sm->camera.z );

}


void sc_update_frustum( scene_manager* Scene )
{

	Scene->polygon_rendered = 0;

	GLdouble model_matrix[16];
	GLdouble projection_matrix[16];
	GLdouble clip_matrix[16];

	GLint viewport[4];
	GLdouble t;

	/* Get the current VIEWPORT plane */
	glGetIntegerv(GL_VIEWPORT, viewport);
	
	/* Get the current PROJECTION matrix from OpenGL */
	glGetDoublev( GL_PROJECTION_MATRIX, projection_matrix );

	/* Get the current MODELVIEW matrix from OpenGL */
	glGetDoublev( GL_MODELVIEW_MATRIX, model_matrix );



	gluUnProject( 
	  (viewport[2]-viewport[0])/2 , (viewport[3]-viewport[1])/2, 
	  0.0,  
	  model_matrix, projection_matrix, viewport,  
	  &(Scene->camera.x) ,&(Scene->camera.y) ,&(Scene->camera.z) 
	);

	if( DEBUG )
	fprintf(stderr, "Camera at %f %f %f", Scene->camera.x, Scene->camera.y, Scene->camera.z );

	/* Combine the two matrices (multiply projection_matrixection by modelview)    */
	clip_matrix[ 0] = model_matrix[ 0] * projection_matrix[ 0] + model_matrix[ 1] * projection_matrix[ 4] + model_matrix[ 2] * projection_matrix[ 8] +    model_matrix[ 3] * projection_matrix[12];
	clip_matrix[ 1] = model_matrix[ 0] * projection_matrix[ 1] + model_matrix[ 1] * projection_matrix[ 5] + model_matrix[ 2] * projection_matrix[ 9] +    model_matrix[ 3] * projection_matrix[13];
	clip_matrix[ 2] = model_matrix[ 0] * projection_matrix[ 2] + model_matrix[ 1] * projection_matrix[ 6] + model_matrix[ 2] * projection_matrix[10] +    model_matrix[ 3] * projection_matrix[14];
	clip_matrix[ 3] = model_matrix[ 0] * projection_matrix[ 3] + model_matrix[ 1] * projection_matrix[ 7] + model_matrix[ 2] * projection_matrix[11] +    model_matrix[ 3] * projection_matrix[15];

	clip_matrix[ 4] = model_matrix[ 4] * projection_matrix[ 0] + model_matrix[ 5] * projection_matrix[ 4]    + model_matrix[ 6] * projection_matrix[ 8] + model_matrix[ 7] * projection_matrix[12];
	clip_matrix[ 5] = model_matrix[ 4] * projection_matrix[ 1] + model_matrix[ 5] * projection_matrix[ 5] + model_matrix[ 6] * projection_matrix[ 9] +    model_matrix[ 7] * projection_matrix[13];
	clip_matrix[ 6] = model_matrix[ 4] * projection_matrix[ 2] + model_matrix[ 5] * projection_matrix[ 6] + model_matrix[ 6] * projection_matrix[10] +    model_matrix[ 7] * projection_matrix[14];
	clip_matrix[ 7] = model_matrix[ 4] * projection_matrix[ 3] + model_matrix[ 5] * projection_matrix[ 7] + model_matrix[ 6] * projection_matrix[11] +    model_matrix[ 7] * projection_matrix[15];

	clip_matrix[ 8] = model_matrix[ 8] * projection_matrix[ 0] + model_matrix[ 9] * projection_matrix[ 4]    + model_matrix[10] * projection_matrix[ 8] + model_matrix[11] * projection_matrix[12];
	clip_matrix[ 9] = model_matrix[ 8] * projection_matrix[ 1] + model_matrix[ 9] * projection_matrix[ 5] + model_matrix[10] * projection_matrix[ 9] +    model_matrix[11] * projection_matrix[13];
	clip_matrix[10] = model_matrix[ 8] * projection_matrix[ 2] + model_matrix[ 9] * projection_matrix[ 6] + model_matrix[10] * projection_matrix[10] +    model_matrix[11] * projection_matrix[14];
	clip_matrix[11] = model_matrix[ 8] * projection_matrix[ 3] + model_matrix[ 9] * projection_matrix[ 7] + model_matrix[10] * projection_matrix[11] +    model_matrix[11] * projection_matrix[15];

	clip_matrix[12] = model_matrix[12] * projection_matrix[ 0] + model_matrix[13] * projection_matrix[ 4]    + model_matrix[14] * projection_matrix[ 8] + model_matrix[15] * projection_matrix[12];
	clip_matrix[13] = model_matrix[12] * projection_matrix[ 1] + model_matrix[13] * projection_matrix[ 5] + model_matrix[14] * projection_matrix[ 9] +    model_matrix[15] * projection_matrix[13];
	clip_matrix[14] = model_matrix[12] * projection_matrix[ 2] + model_matrix[13] * projection_matrix[ 6] + model_matrix[14] * projection_matrix[10] +    model_matrix[15] * projection_matrix[14];
	clip_matrix[15] = model_matrix[12] * projection_matrix[ 3] + model_matrix[13] * projection_matrix[ 7] + model_matrix[14] * projection_matrix[11] +    model_matrix[15] * projection_matrix[15];

	/* Extract the numbers for the RIGHT plane */
	Scene->frustum[0][0] = clip_matrix[ 3] - clip_matrix[ 0];
	Scene->frustum[0][1] = clip_matrix[ 7] - clip_matrix[ 4];
	Scene->frustum[0][2] = clip_matrix[11] - clip_matrix[ 8];
	Scene->frustum[0][3] = clip_matrix[15] - clip_matrix[12];

	/* Normalize the result */
	t = sqrt( Scene->frustum[0][0] * Scene->frustum[0][0] + Scene->frustum[0][1] * Scene->frustum[0][1] + Scene->frustum[0][2]    * Scene->frustum[0][2] );
	Scene->frustum[0][0] /= t;
	Scene->frustum[0][1] /= t;
	Scene->frustum[0][2] /= t;
	Scene->frustum[0][3] /= t;

	/* Extract the numbers for the LEFT plane */
	Scene->frustum[1][0] = clip_matrix[ 3] + clip_matrix[ 0];
	Scene->frustum[1][1] = clip_matrix[ 7] + clip_matrix[ 4];
	Scene->frustum[1][2] = clip_matrix[11] + clip_matrix[ 8];
	Scene->frustum[1][3] = clip_matrix[15] + clip_matrix[12];

	/* Normalize the result */
	t = sqrt( Scene->frustum[1][0] * Scene->frustum[1][0] + Scene->frustum[1][1] * Scene->frustum[1][1] + Scene->frustum[1][2]    * Scene->frustum[1][2] );
	Scene->frustum[1][0] /= t;
	Scene->frustum[1][1] /= t;
	Scene->frustum[1][2] /= t;
	Scene->frustum[1][3] /= t;

	/* Extract the BOTTOM plane */
	Scene->frustum[2][0] = clip_matrix[ 3] + clip_matrix[ 1];
	Scene->frustum[2][1] = clip_matrix[ 7] + clip_matrix[ 5];
	Scene->frustum[2][2] = clip_matrix[11] + clip_matrix[ 9];
	Scene->frustum[2][3] = clip_matrix[15] + clip_matrix[13];

	/* Normalize the result */
	t = sqrt( Scene->frustum[2][0] * Scene->frustum[2][0] + Scene->frustum[2][1] * Scene->frustum[2][1] + Scene->frustum[2][2]    * Scene->frustum[2][2] );
	Scene->frustum[2][0] /= t;
	Scene->frustum[2][1] /= t;
	Scene->frustum[2][2] /= t;
	Scene->frustum[2][3] /= t;

	/* Extract the TOP plane */
	Scene->frustum[3][0] = clip_matrix[ 3] - clip_matrix[ 1];
	Scene->frustum[3][1] = clip_matrix[ 7] - clip_matrix[ 5];
	Scene->frustum[3][2] = clip_matrix[11] - clip_matrix[ 9];
	Scene->frustum[3][3] = clip_matrix[15] - clip_matrix[13];

	/* Normalize the result */
	t = sqrt( Scene->frustum[3][0] * Scene->frustum[3][0] + Scene->frustum[3][1] * Scene->frustum[3][1] + Scene->frustum[3][2]    * Scene->frustum[3][2] );
	Scene->frustum[3][0] /= t;
	Scene->frustum[3][1] /= t;
	Scene->frustum[3][2] /= t;
	Scene->frustum[3][3] /= t;

	/* Extract the FAR plane */
	Scene->frustum[4][0] = clip_matrix[ 3] - clip_matrix[ 2];
	Scene->frustum[4][1] = clip_matrix[ 7] - clip_matrix[ 6];
	Scene->frustum[4][2] = clip_matrix[11] - clip_matrix[10];
	Scene->frustum[4][3] = clip_matrix[15] - clip_matrix[14];

	/* Normalize the result */
	t = sqrt( Scene->frustum[4][0] * Scene->frustum[4][0] + Scene->frustum[4][1] * Scene->frustum[4][1] + Scene->frustum[4][2]    * Scene->frustum[4][2] );
	Scene->frustum[4][0] /= t;
	Scene->frustum[4][1] /= t;
	Scene->frustum[4][2] /= t;
	Scene->frustum[4][3] /= t;

	/* Extract the NEAR plane */
	Scene->frustum[5][0] = clip_matrix[ 3] + clip_matrix[ 2];
	Scene->frustum[5][1] = clip_matrix[ 7] + clip_matrix[ 6];
	Scene->frustum[5][2] = clip_matrix[11] + clip_matrix[10];
	Scene->frustum[5][3] = clip_matrix[15] + clip_matrix[14];

	/* Normalize the result */
	t = sqrt( Scene->frustum[5][0] * Scene->frustum[5][0] + Scene->frustum[5][1] * Scene->frustum[5][1] + Scene->frustum[5][2]    * Scene->frustum[5][2] );
	Scene->frustum[5][0] /= t;
	Scene->frustum[5][1] /= t;
	Scene->frustum[5][2] /= t;
	Scene->frustum[5][3] /= t;
}


int sc_obj_in_frustum( scene_manager* Scene, object* obj )
{
	int p;
	int c = 0;
	GLfloat d;

	obj_update_bounding_sphere( obj );

	vertex relative_bs;
	
	
	add_vertex( &relative_bs, obj->r_location, obj->bound_sphere_loc );
	multiply_vertex( &relative_bs, obj->scale, relative_bs );	

	GLfloat x = relative_bs.x;
	GLfloat y = relative_bs.y;
	GLfloat z = relative_bs.z;
	GLfloat radius = obj->bound_sphere_rad;

//	fprintf( stderr, "Rad %f, %f %f %f", radius, x, y, z );

	for( p = 0; p < 6; p++ )
	{
		d = Scene->frustum[p][0] * x + Scene->frustum[p][1] * y + Scene->frustum[p][2] * z + Scene->frustum[p][3];
		if( d <= -radius )
			return 0;
		if( d > radius )
			c++;
	}
	return (c == 6) ? 2 : 1;
} 


void sc_destroy( scene_manager* sm )
{
	free( sm->rm_all );
	free( sm->object_registry );
	free( sm );
}
