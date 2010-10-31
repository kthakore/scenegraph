#ifndef _SCENE_H
#define _SCENE_H

scene_manager* init_scene();
void set_scene(scene_manager* scene, int );
object* get_scene_object( int object_id );

#endif 
