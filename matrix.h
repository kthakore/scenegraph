#ifndef _SCENEGRAPH_
#define _SCENEGRAPH_

GLdouble* mat_translate( vertex g);
GLdouble* mat_rotate( vertex g, vertex l, GLdouble angle);
GLdouble* mat_scale(  vertex g );
GLdouble* mat_combine( GLdouble* t, GLdouble* r, GLdouble* s);
void mat_transform_vertex( vertex* out, GLdouble* m, vertex in);
bool mat_inv(const GLdouble m[16], GLdouble invOut[16]);

void convert16_4( GLdouble in[16], GLdouble out[4][4]);

void mat_mul (GLdouble* src1, GLdouble* src2, GLdouble* dest);
GLdouble* mat_mul (GLdouble* src1, GLdouble* src2);


GLdouble*  get_clipping_space_transform( );



#endif
