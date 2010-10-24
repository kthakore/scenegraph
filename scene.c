#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "scene.h"
#include "object.h"


void set_scene( scene* Scene )
{

  gluPerspective( Scene->Camera.fov, Scene->Camera.ratio, Scene->Camera.near_dist, Scene->Camera.far_dist);
  gluLookAt( Scene->Camera.p.x, Scene->Camera.p.y, Scene->Camera.p.z,
	     Scene->Camera.l.x, Scene->Camera.p.y, Scene->Camera.p.z,
	     Scene->Camera.u.x, Scene->Camera.u.y, Scene->Camera.u.z
	   );
	    
	     
}

scene* init_scene()
{

   scene* Scene = (scene*)malloc( sizeof(scene) );

   Scene->Camera.p.x = 10;
   Scene->Camera.p.y = 10;
   Scene->Camera.p.z = 10;

   Scene->Camera.l.x = 10;
   Scene->Camera.l.y = 10;
   Scene->Camera.l.z = 10;

   Scene->Camera.u.x = 10;
   Scene->Camera.u.y = 10;
   Scene->Camera.u.z = 10;

   Scene->Camera.fov = 1.0;
   Scene->Camera.ratio = 2;
   Scene->Camera.near_dist = 10;
   Scene->Camera.far_dist = 100;

   set_scene( Scene );

   return Scene;

}
