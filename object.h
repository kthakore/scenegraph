#ifndef _OBJECT_H
#define _OBJECT_H

object* obj_create ( scene_manager* sm);
void obj_load( object* obj, int mode, void* data, int vert_count, int poly_count);
void obj_update_bounding_sphere( object* obj);
void obj_add( object* parent, object* child);
void obj_calculate_bounding_sphere( object* obj );
void obj_operate( scene_manager* sm,  object* parent);
void obj_render( object* o );
void obj_displace_bb( object* obj);

void obj_color( object* obj, GLfloat x, GLfloat y, GLfloat z );
void obj_scale( object* obj, GLfloat x, GLfloat y, GLfloat z );
void obj_translate( object* obj, GLfloat x, GLfloat y, GLfloat z );
void obj_rotate( object* obj, GLfloat x, GLfloat y, GLfloat z );



#endif
