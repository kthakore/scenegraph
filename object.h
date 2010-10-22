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

  vertex   bounding_box [4];
  vertex    location; 
  vertex    rotation;
  vertex    scale;

  GLfloat* polygon_data;

  struct OBJ* parent; 
  struct OBJ** children; 
 
  unsigned int children_c;  
 
} object;

object* obj_create ( );
void obj_destroy ( object* obj ) ;
void obj_operate( object* root, OBJ_OPERATION operation, GLfloat x, GLfloat y, GLfloat z);
void (*op_func_ptr)(object* obj, GLfloat x, GLfloat y, GLfloat z) = NULL;     
	

