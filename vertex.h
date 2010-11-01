#ifndef _VERTEX_H
#define _VERTEX_H

void add_vertex(vertex* sum, vertex a, vertex b );
void sub_vertex(vertex* sum, vertex a, vertex b );
void squared_vertex( vertex* a );
void divide_vertex( vertex* a, GLfloat b);
void copy_vertex(vertex* a, vertex* b );

void debug_vertex_p( vertex* a, const char* );
void  debug_vertex( vertex b, const char* );

void glTranslate_vertex( vertex a );

GLfloat vertex_dist( vertex a, vertex b);


#endif 
