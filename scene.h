#ifndef _SCENE_H
#define _SCENE_H

//Intialize the scenegraph with the number of objects.
scene_manager* sc_init(int objects);

//Set the root in the scene
void sc_set_root( scene_manager* scene, object* root);

//Get our object from the registry
object* sc_get_object( scene_manager* scene, int object_id );

//Get our linked object from the linked list registry
linked_object* sc_get_rm_object( scene_manager* sm, int id );

//Check if the object is in the frustum
int sc_obj_in_frustum( scene_manager* Scene, object* obj );

//Update our current frustum
void sc_update_frustum( scene_manager* scene );

//Render the whole scenegraph
void sc_render(scene_manager* sm); 

//Tell the scenegraph we want to render this obj
void sc_set_object_to_render(scene_manager* Scene, object* obj ); 

//Go through the render marshall (linked list) and draw the stuff
void sc_traverse_rm( scene_manager* sm );

//Deallocate the scenegraph
void sc_destroy(scene_manager* sm);

#endif 
