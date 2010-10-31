#ifndef _OBJECT_H
#define _OBJECT_H

object* obj_create ( scene_manager* sm);
void obj_load( object* obj, int mode, void* data, int count);
void obj_update_bounding_sphere( object* obj);

void obj_calculate_bounding_sphere( object* obj );

#endif
