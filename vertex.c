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
	glTranslated( a.x, a.y, a.z );
}


void glRotate_vertex( vertex r_loc, vertex r_rot, int root)
{

	
	   if( root == 0 )	
	   {
	   divide_vertex( &r_loc, -1 );
	   glTranslate_vertex( r_loc );	
	   }
	 
	glRotated( r_rot.x, 1, 0, 0 );
	glRotated( r_rot.y, 0, 1, 0 );
	glRotated( r_rot.z, 0, 0, 1 ); 

	   if( root == 0 )	
	   {
	   divide_vertex( &r_loc, -1 );
	   glTranslate_vertex( r_loc );	
	   }

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





GLdouble* get_clipping_space_transform( )
{

   GLdouble* m = (GLdouble*)malloc( sizeof( GLdouble ) * 16 );
   glGetDoublev( GL_MODELVIEW_MATRIX, m );

    GLdouble* p = (GLdouble*)malloc( sizeof( GLdouble ) * 16 );
   glGetDoublev( GL_PROJECTION_MATRIX, p);

    GLdouble* d = (GLdouble*)malloc( sizeof( GLdouble ) * 16 );
   Matrix4x4MultiplyBy4x4( (GLdouble (*)[4])m, (GLdouble (*)[4])p, (GLdouble (*)[4])d );

    free(m); free(p);
    
  return d;


}

GLdouble* modelview_inv_get(  )
{

	GLdouble* m = get_clipping_space_transform();

	///Take m and send to MatrixInversion
	GLdouble* out = (GLdouble*)malloc( sizeof( GLdouble) * 16 );
        if( mat_inv( m, out) )
	{
		fprintf(stderr, "bah m %f, %f \n", m[5],out[5]);
		free(m);
		return out;
	}
	return out;
}



GLdouble modelview_multiply( vertex* s, GLdouble** inv, vertex t)
{



	GLdouble r_c[4];
	glGetDoublev( GL_CURRENT_RASTER_POSITION, r_c );
	GLdouble* m = get_clipping_space_transform();

	GLdouble a = r_c[3];
	GLdouble m_[4][4];
	GLdouble inv_[4][4];
	convert16_4( m, m_ );
	convert16_4( *inv, inv_ );

	GLdouble out[4][4];
//	GLdouble c;
	Matrix4x4MultiplyBy4x4( m_, inv_, out);
	s->x    = out[0][0]*t.x + out[0][1]*t.y + out[0][2]*t.z + out[0][3]*a;
	s->y    = out[1][0]*t.x + out[1][1]*t.y + out[1][2]*t.z + out[1][3]*a;
	s->z    = out[2][0]*t.x + out[2][1]*t.y + out[2][2]*t.z + out[2][3]*a;
//	c    = out[0][0]*t.x + out[0][1]*t.y + out[0][2]*t.z + out[0][3]*a;

//	divide_vertex( s, c);
	free(m);
	free(*inv);
	return 0.0;
}

