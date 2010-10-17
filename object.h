#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


typedef struct OBJ
{

  GLfloat** vertices;
  unsigned int vertices_c;

  GLfloat p[3];
 
  struct OBJ* parent;
  struct OBJ** children;
  unsigned int children_c;
   
} object;

object* obj_create ( );
void obj_rotate( object* obj, GLfloat rad );
void obj_translate( object* obj, GLfloat x, GLfloat y, GLfloat z);
void obj_destroy ( object* obj, bool free_ver) ;
void obj_render ( object* obj );

