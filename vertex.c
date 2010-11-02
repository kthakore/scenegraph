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

bool gluInvertMatrix(const GLdouble m[16], GLdouble invOut[16])
{
	GLdouble inv[16], det;
	int i;

	inv[0] =   m[5]*m[10]*m[15] - m[5]*m[11]*m[14] - m[9]*m[6]*m[15]
		+ m[9]*m[7]*m[14] + m[13]*m[6]*m[11] - m[13]*m[7]*m[10];
	inv[4] =  -m[4]*m[10]*m[15] + m[4]*m[11]*m[14] + m[8]*m[6]*m[15]
		- m[8]*m[7]*m[14] - m[12]*m[6]*m[11] + m[12]*m[7]*m[10];
	inv[8] =   m[4]*m[9]*m[15] - m[4]*m[11]*m[13] - m[8]*m[5]*m[15]
		+ m[8]*m[7]*m[13] + m[12]*m[5]*m[11] - m[12]*m[7]*m[9];
	inv[12] = -m[4]*m[9]*m[14] + m[4]*m[10]*m[13] + m[8]*m[5]*m[14]
		- m[8]*m[6]*m[13] - m[12]*m[5]*m[10] + m[12]*m[6]*m[9];
	inv[1] =  -m[1]*m[10]*m[15] + m[1]*m[11]*m[14] + m[9]*m[2]*m[15]
		- m[9]*m[3]*m[14] - m[13]*m[2]*m[11] + m[13]*m[3]*m[10];
	inv[5] =   m[0]*m[10]*m[15] - m[0]*m[11]*m[14] - m[8]*m[2]*m[15]
		+ m[8]*m[3]*m[14] + m[12]*m[2]*m[11] - m[12]*m[3]*m[10];
	inv[9] =  -m[0]*m[9]*m[15] + m[0]*m[11]*m[13] + m[8]*m[1]*m[15]
		- m[8]*m[3]*m[13] - m[12]*m[1]*m[11] + m[12]*m[3]*m[9];
	inv[13] =  m[0]*m[9]*m[14] - m[0]*m[10]*m[13] - m[8]*m[1]*m[14]
		+ m[8]*m[2]*m[13] + m[12]*m[1]*m[10] - m[12]*m[2]*m[9];
	inv[2] =   m[1]*m[6]*m[15] - m[1]*m[7]*m[14] - m[5]*m[2]*m[15]
		+ m[5]*m[3]*m[14] + m[13]*m[2]*m[7] - m[13]*m[3]*m[6];
	inv[6] =  -m[0]*m[6]*m[15] + m[0]*m[7]*m[14] + m[4]*m[2]*m[15]
		- m[4]*m[3]*m[14] - m[12]*m[2]*m[7] + m[12]*m[3]*m[6];
	inv[10] =  m[0]*m[5]*m[15] - m[0]*m[7]*m[13] - m[4]*m[1]*m[15]
		+ m[4]*m[3]*m[13] + m[12]*m[1]*m[7] - m[12]*m[3]*m[5];
	inv[14] = -m[0]*m[5]*m[14] + m[0]*m[6]*m[13] + m[4]*m[1]*m[14]
		- m[4]*m[2]*m[13] - m[12]*m[1]*m[6] + m[12]*m[2]*m[5];
	inv[3] =  -m[1]*m[6]*m[11] + m[1]*m[7]*m[10] + m[5]*m[2]*m[11]
		- m[5]*m[3]*m[10] - m[9]*m[2]*m[7] + m[9]*m[3]*m[6];
	inv[7] =   m[0]*m[6]*m[11] - m[0]*m[7]*m[10] - m[4]*m[2]*m[11]
		+ m[4]*m[3]*m[10] + m[8]*m[2]*m[7] - m[8]*m[3]*m[6];
	inv[11] = -m[0]*m[5]*m[11] + m[0]*m[7]*m[9] + m[4]*m[1]*m[11]
		- m[4]*m[3]*m[9] - m[8]*m[1]*m[7] + m[8]*m[3]*m[5];
	inv[15] =  m[0]*m[5]*m[10] - m[0]*m[6]*m[9] - m[4]*m[1]*m[10]
		+ m[4]*m[2]*m[9] + m[8]*m[1]*m[6] - m[8]*m[2]*m[5];

	det = m[0]*inv[0] + m[1]*inv[4] + m[2]*inv[8] + m[3]*inv[12];
	if (det == 0)
		return false;

	det = 1.0 / det;

	for (i = 0; i < 16; i++)
		invOut[i] = inv[i] * det;

	return true;
}



GLdouble* modelview_inv_get(  )
{

	GLdouble m[16];
	glGetDoublev( GL_MODELVIEW_MATRIX, m );

	///Take m and send to MatrixInversion

	float **in;
	in = new float*[16];
	int i;
	for(i=0;i<16;i++)
		in[i] = new float[16];

	in[0][1] = m[0]; in[0][1] = m[4]; in[0][2] = m[8]; in[0][4] = m[12];
	in[1][1] = m[1]; in[1][1] = m[5]; in[1][2] = m[9]; in[1][4] = m[13];
	in[2][1] = m[2]; in[2][1] = m[6]; in[2][2] = m[10]; in[2][4] = m[14];
	in[3][1] = m[3]; in[3][1] = m[7]; in[3][2] = m[11]; in[3][4] = m[15];

	float **Y;
	Y = new float*[16]; 
	for(i=0;i<16;i++)
		Y[i] = new float[16];

	MatrixInversion( (float **)in , 4, (float** )Y );


	GLdouble* out = (GLdouble*)malloc( sizeof( GLdouble) * 16 );

	out[0] = Y[0][1]; out[4] = Y[0][2]; out[8] = Y[0][3]; out[12] = Y[0][4];
	out[1] = Y[1][1]; out[5] = Y[1][2]; out[9] = Y[1][3]; out[13] = Y[1][4];
	out[2] = Y[2][1]; out[6] = Y[2][2]; out[10] = Y[2][3]; out[14] = Y[2][4];
	out[3] = Y[3][1]; out[7] = Y[3][2]; out[11] = Y[3][3]; out[15] = Y[3][4];

	fprintf(stderr, "ASDSD %f %f \n", Y[0][1], out[0]);

	return out;
}


static inline void Matrix4x4MultiplyBy4x4 (GLdouble src1[4][4], GLdouble src2[4][4], GLdouble dest[4][4])
{
	dest[0][0] = src1[0][0] * src2[0][0] + src1[0][1] * src2[1][0] + src1[0][2] * src2[2][0] + src1[0][3] * src2[3][0]; 
	dest[0][1] = src1[0][0] * src2[0][1] + src1[0][1] * src2[1][1] + src1[0][2] * src2[2][1] + src1[0][3] * src2[3][1]; 
	dest[0][2] = src1[0][0] * src2[0][2] + src1[0][1] * src2[1][2] + src1[0][2] * src2[2][2] + src1[0][3] * src2[3][2]; 
	dest[0][3] = src1[0][0] * src2[0][3] + src1[0][1] * src2[1][3] + src1[0][2] * src2[2][3] + src1[0][3] * src2[3][3]; 
	dest[1][0] = src1[1][0] * src2[0][0] + src1[1][1] * src2[1][0] + src1[1][2] * src2[2][0] + src1[1][3] * src2[3][0]; 
	dest[1][1] = src1[1][0] * src2[0][1] + src1[1][1] * src2[1][1] + src1[1][2] * src2[2][1] + src1[1][3] * src2[3][1]; 
	dest[1][2] = src1[1][0] * src2[0][2] + src1[1][1] * src2[1][2] + src1[1][2] * src2[2][2] + src1[1][3] * src2[3][2]; 
	dest[1][3] = src1[1][0] * src2[0][3] + src1[1][1] * src2[1][3] + src1[1][2] * src2[2][3] + src1[1][3] * src2[3][3]; 
	dest[2][0] = src1[2][0] * src2[0][0] + src1[2][1] * src2[1][0] + src1[2][2] * src2[2][0] + src1[2][3] * src2[3][0]; 
	dest[2][1] = src1[2][0] * src2[0][1] + src1[2][1] * src2[1][1] + src1[2][2] * src2[2][1] + src1[2][3] * src2[3][1]; 
	dest[2][2] = src1[2][0] * src2[0][2] + src1[2][1] * src2[1][2] + src1[2][2] * src2[2][2] + src1[2][3] * src2[3][2]; 
	dest[2][3] = src1[2][0] * src2[0][3] + src1[2][1] * src2[1][3] + src1[2][2] * src2[2][3] + src1[2][3] * src2[3][3]; 
	dest[3][0] = src1[3][0] * src2[0][0] + src1[3][1] * src2[1][0] + src1[3][2] * src2[2][0] + src1[3][3] * src2[3][0]; 
	dest[3][1] = src1[3][0] * src2[0][1] + src1[3][1] * src2[1][1] + src1[3][2] * src2[2][1] + src1[3][3] * src2[3][1]; 
	dest[3][2] = src1[3][0] * src2[0][2] + src1[3][1] * src2[1][2] + src1[3][2] * src2[2][2] + src1[3][3] * src2[3][2]; 
	dest[3][3] = src1[3][0] * src2[0][3] + src1[3][1] * src2[1][3] + src1[3][2] * src2[2][3] + src1[3][3] * src2[3][3]; 
};

static inline void convert16_4( GLdouble in[16], GLdouble out[4][4])
{

	out[0][0] = in[0]; out[0][1] = in[4]; out[0][2] = in[8]; out[0][3] = in[12];
	out[1][0] = in[1]; out[1][1] = in[5]; out[1][2] = in[9]; out[1][3] = in[13];
	out[2][0] = in[2]; out[2][1] = in[6]; out[2][2] = in[10]; out[2][3] = in[14];
	out[3][0] = in[3]; out[3][1] = in[7]; out[3][2] = in[11]; out[3][3] = in[15];
};


GLdouble modelview_multiply( vertex* s, GLdouble** inv, vertex t)
{



	GLdouble m[16];
	glGetDoublev( GL_MODELVIEW_MATRIX, m );
	GLdouble a = 0;
	GLdouble b,c,d;

	GLdouble m_[4][4];
	GLdouble inv_[4][4];
	convert16_4( m, m_ );


	GLdouble ins[4][4];

	convert16_4( *inv, inv_ );

	GLdouble out[4][4];

	Matrix4x4MultiplyBy4x4( m_, inv_, out);
	s->x    = out[0][0]*t.x + out[0][1]*t.y + out[0][2]*t.z + out[0][3]*a;
	s->y    = out[1][0]*t.x + out[1][1]*t.y + out[1][2]*t.z + out[1][3]*a;
	s->z    = out[2][0]*t.x + out[2][1]*t.y + out[2][2]*t.z + out[2][3]*a;
	//c    = out[0][0]*t.x + out[0][1]*t.y + out[0][2]*t.z + out[0][3]*a;
	return c;

	/*
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
	 */
}

