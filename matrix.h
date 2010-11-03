#ifndef _SCENEGRAPH_
#define _SCENEGRAPH_

GLdouble* mat_transform( vertex g);
GLdouble* mat_rotate( vertex g, GLdouble angle);
GLdouble* mat_scale(  vertex g );
GLdouble* mat_combine( GLdouble* t, GLdouble* r, GLdouble* s);
bool mat_inv(const GLdouble m[16], GLdouble invOut[16]);

void convert16_4( GLdouble in[16], GLdouble out[4][4]);

void Matrix4x4MultiplyBy4x4 (GLdouble src1[4][4], GLdouble src2[4][4], GLdouble dest[4][4]);


#endif
