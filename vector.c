#include "scenegraph.h"

void add_vector(vector* sum, vector a, vector b )
{
	sum->x = a.x + b.x;
	sum->y = a.y + b.y;
	sum->z = a.z + b.z;
}


void sub_vector(vector* sum, vector a, vector b )
{
	sum->x = a.x - b.x;
	sum->y = a.y - b.y;
	sum->z = a.z - b.z;
}

void squared_vector( vector* sum )
{
	sum->x *= sum->x;
	sum->y *= sum->y;
	sum->z *= sum->z;
}

void copy_vector(vector* a, vector* b )
{
	a->x = b->x;
	a->y = b->y;
	a->z = b->z;
}

void divide_vector(vector* diff, GLfloat div)
{

	diff->x /= div;
	diff->y /= div;
	diff->z /= div;

}

GLfloat vector_dist( vector a, vector b)
{

	vector val;

	sub_vector( &val, a, b );
	squared_vector( &val );

	return sqrt( val.x + val.y + val.z  );

}

void multiply_vector(vector* c, vector a, vector b)
{

	c->x = a.x * b.x;
	c->y = a.y * b.y;
	c->z = a.z * b.z;
}

void debug_vector_p( vector* a, const char* c )
{
	fprintf( stderr, "%s (%f,%f,%f) \n", c, a->x, a->y, a->z );
}

void  debug_vector( vector b, const char* c )
{
	debug_vector_p( &b, c);	
}

void glTranslate_vector( vector a )
{
	glTranslated( a.x, a.y, a.z );

}


void glRotate_vector( vector r_loc, vector r_rot)
{

	   divide_vector( &r_loc, -1 );
	   glTranslate_vector( r_loc );	

	glRotated( r_rot.x, 1, 0, 0 );
	glRotated( r_rot.y, 0, 1, 0 );
	glRotated( r_rot.z, 0, 0, 1 ); 

	   divide_vector( &r_loc, -1 );
	   glTranslate_vector( r_loc );	
}


void zero_vector( vector* z)
{
	flood_vector(z , 0 );
}

void flood_vector(  vector* z, GLfloat v )
{
	z->x = v;
	z->y = v;
	z->z = v;

}


void extract_vector( vector a, GLfloat* x, GLfloat* y, GLfloat* z)
{

	*x = (GLfloat)a.x;
	*y = (GLfloat)a.y;
	*z = (GLfloat)a.z;

}

void draw_vector_axis( vector* bb, GLfloat rad, vector c )
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





GLdouble* modelview_inv_get(  )
{

	//Get the clipping matrix that we will invert
	GLdouble* m = get_clipping_space_transform();
	GLdouble* out = (GLdouble*)malloc( sizeof( GLdouble) * 16 );
        if( mat_inv( m, out) )
	{
		free(m);
		return out;
	}
	return out;
}


//Transform the matrix using the inv
GLdouble modelview_multiply( vector* s, GLdouble** inv, vector t)
{

	GLdouble r_c[4];
	glGetDoublev( GL_CURRENT_RASTER_POSITION, r_c );
	GLdouble* m = get_clipping_space_transform();

	GLdouble a = r_c[3];
	GLdouble out[16];
//	GLdouble c;
	mat_mul( *inv, m,  out);
	s->x    = out[0]*t.x + out[4]*t.y + out[8]*t.z + out[12]*a;
	s->y    = out[1]*t.x + out[5]*t.y + out[9]*t.z + out[11]*a;
	s->z    = out[2]*t.x + out[6]*t.y + out[10]*t.z + out[12]*a;
//	c    = out[0][0]*t.x + out[0][1]*t.y + out[0][2]*t.z + out[0][3]*a;

//	divide_vector( s, c);
	free(m);
	free(*inv);
	return 0.0;
}

