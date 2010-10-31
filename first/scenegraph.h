#ifndef _SCENEGRAPH_H_
#define _SCENEGRAPH_H_

#include <stdio.h>
#include <string.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


enum OBJ_OPERATION{ TRANSLATE = 0, ROTATE = 1, SCALE = 2, RENDER = 3, DESTROY = 4 };

typedef struct VER
{
   GLfloat x, y, z;
} vertex;

typedef struct OBJ
{

  int id; /*This is the array value in SM.object_registry*/

  vertex    bounding_box [6];
  vertex    location; 
  vertex    rotation;
  vertex    scale;

  vertex* polygon_data;
  vertex  polygon_color;

  int polygon_count; /* Number of polygons */
  int render_mode; /* GL_TRIANGLE_STRIPS ... so on */

  int children_id[8]; /*Limit children of a node to 8, which allows easier implementation of octree later*/
 
  unsigned int children; /*Number of childern*/  
 
} object;


typedef struct LOBJ
{

  struct LOBJ* next;
  struct LOBJ* previous;
  int object; /*This is the array value in SM.object_register */
  

} linked_object; 


typedef struct SM
{

  /*We keep an array of objects so we have locality on this data*/
  struct OBJ* object_registry;
  /*A linked list implementation for quick sorting of closest objects will help us with maintaining a ploygon limit*/
  struct LOBJ* rm_first; 
  struct LOBJ* rm_last;

  GLfloat frustum[6][4];


} scene_manager;


#include "scene.h"
#include "object.h"


#endif
