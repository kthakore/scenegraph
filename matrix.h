#ifndef _MATRIX_
#define _MATRIX_

/* Functions to operate on Matrices */

GLdouble* mat_translate( vector g);
GLdouble* mat_rotate( vector g, vector l, GLdouble angle);
GLdouble* mat_scale(  vector g );
GLdouble* mat_combine( GLdouble* t, GLdouble* r, GLdouble* s);
void mat_transform_vector( vector* out, GLdouble* m, vector in);
bool mat_inv(const GLdouble m[16], GLdouble invOut[16]);

void convert16_4( GLdouble in[16], GLdouble out[4][4]);

void mat_mul (GLdouble* src1, GLdouble* src2, GLdouble* dest);
GLdouble* mat_mul (GLdouble* src1, GLdouble* src2);


GLdouble*  get_clipping_space_transform( );



#endif
