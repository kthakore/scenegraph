#ifndef _VERTEX_H
#define _VERTEX_H

void add_vector(vector* sum, vector a, vector b );
void sub_vector(vector* sum, vector a, vector b );
void squared_vector( vector* a );
void divide_vector( vector* a, GLfloat b);

void copy_vector(vector* a, vector* b );

void multiply_vector(vector* c, vector a, vector b);

void debug_vector_p( vector* a, const char* );
void  debug_vector( vector b, const char* );

void glTranslate_vector( vector a );
void glRotate_vector( vector a, vector b);

GLfloat vector_dist( vector a, vector b);

void zero_vector( vector* z);
void flood_vector( vector* z, GLfloat v);

void extract_vector( vector v, GLfloat* a, GLfloat* b, GLfloat* c);
void draw_vector_axis( vector* bb, GLfloat rad, vector c);

GLdouble modelview_multiply( vector* s, GLdouble** inv, vector t ) ;

GLdouble* modelview_inv_get( ) ;

#endif 
