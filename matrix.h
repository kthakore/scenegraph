#ifndef _SCENEGRAPH_
#define _SCENEGRAPH_

GLdouble* mat_transform( vertex g);
GLdouble* mat_rotate( vertex g, GLdouble angle);
GLdouble* mat_scale(  vertex g );
GLdouble* mat_combine( GLdouble* t, GLdouble* r, GLdouble* s);
bool mat_inv(const GLdouble m[16], GLdouble invOut[16]);

void convert16_4( GLdouble in[16], GLdouble out[4][4]);

void mat_mul (GLdouble* src1, GLdouble* src2, GLdouble* dest);

GLdouble*  get_clipping_space_transform( );



#endif
