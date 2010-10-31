#ifndef _OBJECT_H
#define _OBJECT_H

object* obj_create ( scene_manager* sm);
void obj_load( object* obj, int mode, void* data, int count);
void obj_update_bounding_sphere( object* obj);
void obj_add( object* parent, object* child);
void obj_calculate_bounding_sphere( object* obj );
void obj_operate( scene_manager* sm,  object* parent, enum OBJ_OPERATION operation, GLfloat x, GLfloat y, GLfloat z);


#endif
