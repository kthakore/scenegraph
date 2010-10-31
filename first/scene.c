#include "scenegraph.h"

scene_manager* sc_init(int objects) {

   int i;
   scene_manager* Scene = (scene_manager*)malloc( sizeof(scene_manager) );

   Scene->objects = objects;

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
   
   return Scene;
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

void sc_destroy( scene_manager* sm )
{
   free( sm->object_registry );
   free( sm );
}
