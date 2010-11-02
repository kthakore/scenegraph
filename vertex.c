#include "scenegraph.h"

void add_vertex(vertex* sum, vertex a, vertex b )
{
	sum->x = a.x + b.x;
	sum->y = a.y + b.y;
	sum->z = a.z + b.z;
}


void sub_vertex(vertex* sum, vertex a, vertex b )
{
	sum->x = a.x - b.x;
	sum->y = a.y - b.y;
	sum->z = a.z - b.z;
}

void squared_vertex( vertex* sum )
{
	sum->x *= sum->x;
	sum->y *= sum->y;
	sum->z *= sum->z;
}

void copy_vertex(vertex* a, vertex* b )
{
	a->x = b->x;
	a->y = b->y;
	a->z = b->z;
}

void divide_vertex(vertex* diff, GLfloat div)
{

	diff->x /= div;
	diff->y /= div;
	diff->z /= div;

}

GLfloat vertex_dist( vertex a, vertex b)
{

	vertex val;

	sub_vertex( &val, a, b );
	squared_vertex( &val );

	return sqrt( val.x + val.y + val.z  );

}

void multiply_vertex(vertex* c, vertex a, vertex b)
{

	c->x = a.x * b.x;
	c->y = a.y * b.y;
	c->z = a.z * b.z;
}

void debug_vertex_p( vertex* a, const char* c )
{
	fprintf( stderr, "%s (%f,%f,%f) \n", c, a->x, a->y, a->z );
}

void  debug_vertex( vertex b, const char* c )
{
	debug_vertex_p( &b, c);	
}

void glTranslate_vertex( vertex a )
{
	glTranslatef( a.x, a.y, a.z );
}


void glRotate_vertex( vertex r_loc, vertex r_rot, int root)
{
	
/*
	if( root == 0 )	
	{
		divide_vertex( &r_loc, -1 );
		glTranslate_vertex( r_loc );	
	}
*/
	glRotated( r_rot.x, 1, 0, 0 );
	glRotated( r_rot.y, 0, 1, 0 );
	glRotated( r_rot.z, 0, 0, 1 ); 
/*
	if( root == 0 )	
	{
		divide_vertex( &r_loc, -1 );
		glTranslate_vertex( r_loc );	
	}


*/
//	if(root == 0 )
	//glTranslate_vertex( p_loc );


}


void zero_vertex( vertex* z)
{
	flood_vertex(z , 0 );
}

void flood_vertex(  vertex* z, GLfloat v )
{
   z->x = v;
   z->y = v;
   z->z = v;

}


void extract_vertex( vertex a, GLfloat* x, GLfloat* y, GLfloat* z)
{

   *x = (GLfloat)a.x;
   *y = (GLfloat)a.y;
   *z = (GLfloat)a.z;

}

void draw_vertex_axis( vertex* bb, GLfloat rad, vertex c )
{
	glColor3f ( c.x,c.y,c.z);
	glBegin( GL_LINES );

	glVertex3f( bb->x, bb->y, bb->z);		
	glVertex3f( bb->x, bb->y, bb->z + rad);

	glEnd();
	glBegin( GL_LINES );

	glVertex3f( bb->x, bb->y, bb->z);		
	glVertex3f( bb->x + rad, bb->y, bb->z );

	glEnd();
	glBegin( GL_LINES );

	glVertex3f( bb->x, bb->y, bb->z);		
	glVertex3f( bb->x , bb->y + rad, bb->z );

	glEnd();
}


GLdouble modelview_multiply( vertex* s, vertex t)
{
/*
GLdouble m[16];
glGetDoublev( GL_MODELVIEW_MATRIX, m );

GLdouble a = 1;
GLdouble a,b,c,d;

a = 

c    = m[0]*t.x + m[1]*t.y + m[2]*t.z + m[3]*a;
s->x = m[4]*t.x + m[5]*t.y + m[6]*t.z + m[7]*a;
s->y = m[8]*t.x + m[9]*t.y + m[10]*t.z + m[11]*a;
s->z = m[12]*t.x + m[13]*t.y + m[14]*t.z + m[15]*a;

return c;
*/


GLdouble x,y,z,zdepth;
GLdouble projection[16];
GLdouble modelview[16];
GLint viewport[4];

glGetDoublev(GL_PROJECTION_MATRIX , projection);
glGetDoublev (GL_MODELVIEW_MATRIX , modelview);
glGetIntegerv (GL_VIEWPORT ,viewport);

//gluProject(GLdouble, GLdouble, GLdouble, const GLdouble*, const GLdouble*, const GLint*, GLdouble*, GLdouble*, GLdouble*)
gluUnProject( t.x, t.y, t.z ,modelview,projection,viewport , &x, &y , &z);
s->x = x;
s->y = y;
s->z = z;
debug_vertex( t, "IN:" );
debug_vertex_p( s, "OUT:");
return 1.0;
}

