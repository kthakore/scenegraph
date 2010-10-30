#ifndef _SCENE_H
#define _SCENE_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "object.h"


typedef struct link_obj_list
{

  struct link_obj_list* next;
  object* object;


} link_obj_list;

typedef struct scene
{

  GLfloat frustum[6][4]; // The 6 planes of the frustum 
  int root;
  object** obj_registry;
  link_obj_list* start;
  link_obj_list* end;


} scene_manager;

scene_manager* init_scene();
void set_scene(scene_manager* scene, int );
object* get_scene_object( int object_id );
void register_scene_object( object* obj );


#endif 
