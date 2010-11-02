#ifndef _VERTEX_H
#define _VERTEX_H

void add_vertex(vertex* sum, vertex a, vertex b );
void sub_vertex(vertex* sum, vertex a, vertex b );
void squared_vertex( vertex* a );
void divide_vertex( vertex* a, GLfloat b);

void copy_vertex(vertex* a, vertex* b );

void multiply_vertex(vertex* c, vertex a, vertex b);

void debug_vertex_p( vertex* a, const char* );
void  debug_vertex( vertex b, const char* );

void glTranslate_vertex( vertex a );
void glRotate_vertex( vertex a, vertex b,  int d);

GLfloat vertex_dist( vertex a, vertex b);

void zero_vertex( vertex* z);
void flood_vertex( vertex* z, GLfloat v);

void extract_vertex( vertex v, GLfloat* a, GLfloat* b, GLfloat* c);
void draw_vertex_axis( vertex* bb, GLfloat rad, vertex c);

GLdouble modelview_multiply( vertex* s, GLdouble** inv, vertex t ) ;

GLdouble* modelview_inv_get( ) ;

#endif 
