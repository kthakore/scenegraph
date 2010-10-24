#ifndef _SCENE_H
#define _SCENE_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "object.h"

typedef struct camera
{

  GLfloat fov;
  GLfloat ratio;
  GLfloat near_dist;
  GLfloat far_dist;

  vertex p;
  vertex l;
  vertex u;

} camera;

typedef struct scene
{
  camera Camera;
  object* root;

} scene;

scene* init_scene();
void   set_scene(scene* scene);


#endif 
