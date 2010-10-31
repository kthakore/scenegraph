#ifndef _SCENE_H
#define _SCENE_H

scene_manager* sc_init(int objects);
void set_scene(scene_manager* scene, int );
object* get_scene_object( int object_id );

#endif 
