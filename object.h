#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


typedef struct OBJ
{

  GLfloat* vertices;
  int count;

} object;

object* obj_create ( ) { return (object*)malloc( sizeof (object) ); }
void obj_rotate( object* obj, GLfloat rad ) { }
void obj_translate( object* obj, GLfloat x, GLfloat y, GLfloat z) { }
void obj_destroy ( object* obj, bool free_ver) { if(free_ver) free( obj->vertices );  free( obj ); }

