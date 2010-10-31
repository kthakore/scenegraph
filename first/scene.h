#ifndef _SCENE_H
#define _SCENE_H

scene_manager* sc_init(int objects);

void set_scene(scene_manager* scene, int );

object* sc_get_object( scene_manager* scene, int object_id );

linked_object* sc_get_rm_object( scene_manager* sm, int id );

int sc_obj_in_frustum( scene_manager* Scene, object* obj );

void sc_update_frustum( scene_manager* scene );

void sc_render(scene_manager* sm); 

void sc_destroy(scene_manager* sm);

#endif 
