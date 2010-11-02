#ifndef _SCENEGRAPH_H_
#define _SCENEGRAPH_H_

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define FRUSTUM 0
#define DEBUG 1
#define MAX_POLYGONS 10000

struct SM;

enum OBJ_OPERATION{ TRANSLATE = 0, ROTATE = 1, SCALE = 2, RENDER = 3, DESTROY = 4 };

typedef struct VER
{
   GLdouble x, y, z;
} vertex;

typedef struct OBJ
{

  int id; /*This is the array value in SM.object_registry*/

  /* We are using a sphere, as we only have to recalculate on translate 
     and not rotate. Also it takes less memory to hold a bounding sphere.
     Additionally it takes less checks to do the frustum intersections. */
  vertex    bound_sphere_loc;
  GLfloat   bound_sphere_rad;  
  int	    bound_rad_from; /* Which axis is providing the radius, for scaling purposes */

  vertex    location; 
  vertex    rotation;
  vertex    scale;

  /* relative vertexes to hold state of scenegraph traversal so far */
  vertex    r_location; 
  vertex    r_rotation;
  vertex    r_bound_sphere_loc;

  vertex* polygon_data;
  vertex  polygon_color;

  int vertex_count;
  int polygon_count; /* Number of polygons */
  int render_mode; /* GL_TRIANGLE_STRIPS ... so on */

  int children_id[8]; /*Limit children of a node to 8, which allows easier implementation of octree later*/

  int is_root;
  int parent; 

  unsigned int children; /*Number of children*/  

  vertex model_proj_bb;

  int render_call_list;  

  struct SM* scene;
 
} object;


typedef struct LOBJ
{

  struct LOBJ* next;
  struct LOBJ* previous;
  object* object_ptr; /*This is the array value in SM.object_register */
  

} linked_object; 


typedef struct SM
{
 
  int objects;
  /*We keep an array of objects so we have locality on this data*/
  object* object_registry;
  int registered; //Value of objects registered so far 

  /*A linked list implementation for quick sorting of closest objects will help us with maintaining a ploygon limit*/
  linked_object* rm_all;
  linked_object* rm_first; 
  linked_object* rm_last;
  unsigned int to_render;

  /* Our root object */
  int root_object_id;

  GLfloat frustum[6][4];

  vertex camera;

  int polygon_rendered;


} scene_manager;


#include "scene.h"
#include "object.h"
#include "vertex.h"
#include "loader.h"

#endif
