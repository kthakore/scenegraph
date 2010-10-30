#ifndef _COMMON_H
#define _COMMON_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

enum OBJ_OPERATION{ TRANSLATE = 0, ROTATE = 1, SCALE = 2, RENDER = 3, DESTROY = 4 };

typedef struct vertex
{
   GLfloat x, y, z;
} vertex;

typedef struct OBJ
{

  vertex    bounding_box [6];
  vertex    location; 
  vertex    rotation;
  vertex    scale;

  vertex* polygon_data;
  vertex  polygon_color;

  int polygon_count;

  int render_mode;

  struct OBJ* parent; 
  struct OBJ** children; 
 
  unsigned int children_c;  
 
} object;


typedef struct linked_obj
{

  struct linked_obj* next;
  object* object;


} linked_obj;

typedef struct scene_manager
{

  GLfloat frustum[6][4]; // The 6 planes of the frustum 
  int root;
  object* obj_registry;
  linked_obj* start;
  linked_obj* end;

} scene_manager;


#endif
