#ifndef _SCENEGRAPH_H_
#define _SCENEGRAPH_H_

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define FRUSTUM 1
#define DEBUG 0
#define MAX_POLYGONS 400

//Defining the scenemanager struct early for useage before the declaration
struct SM;

// We will be using vector to hold positional and any 3 dim data
typedef struct VER
{
   GLdouble x, y, z;
} vector;

// An object defines a set of polygons, bounding box and spatial coord
typedef struct OBJ
{

  int id; /*This is the array value in SM.object_registry*/

  /* We are using a sphere, as we only have to recalculate on translate 
     and not rotate. Also it takes less memory to hold a bounding sphere.
     Additionally it takes less checks to do the frustum intersections. */
  vector    bound_sphere_loc;
  GLfloat   bound_sphere_rad;  
  int	    bound_rad_from; /* Which axis is providing the radius, for scaling purposes */

  vector    location; 
  vector    rotation;
  vector    scale;

  /* relative vectores to hold state of scenegraph traversal so far */
  vector    r_location; 
  vector    r_rotation;
  vector    r_bound_sphere_loc;

  vector* polygon_data;
  vector  polygon_color;

  int vector_count;
  int polygon_count; /* Number of polygons */
  int render_mode; /* GL_TRIANGLE_STRIPS ... so on */

  int children_id[8]; /*Limit children of a node to 8, which allows easier implementation of octree later*/

  int is_root;
  int parent; 

  unsigned int children; /*Number of children*/  

  vector model_proj_bb;

  struct SM* scene;
 
} object;


//A simple node for our linked list for the render marshall
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

  vector camera;

  int polygon_rendered;


} scene_manager;


#include "scene.h"
#include "object.h"
#include "vector.h"
#include "loader.h"
#include "matrix.h"
#endif
