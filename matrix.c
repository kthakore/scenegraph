#include "scenegraph.h"


void Matrix4x4MultiplyBy4x4 (GLdouble src1[4][4], GLdouble src2[4][4], GLdouble dest[4][4])
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
}

void convert16_4( GLdouble in[16], GLdouble out[4][4])
{

	out[0][0] = in[0]; out[0][1] = in[4]; out[0][2] = in[8]; out[0][3] = in[12];
	out[1][0] = in[1]; out[1][1] = in[5]; out[1][2] = in[9]; out[1][3] = in[13];
	out[2][0] = in[2]; out[2][1] = in[6]; out[2][2] = in[10]; out[2][3] = in[14];
	out[3][0] = in[3]; out[3][1] = in[7]; out[3][2] = in[11]; out[3][3] = in[15];
}


void mat_mul( GLdouble* src, GLdouble* src2, GLdouble* out)
{

	Matrix4x4MultiplyBy4x4( (GLdouble (*)[4])src, (GLdouble (*)[4])src2, (GLdouble (*)[4])out);

}

GLdouble* mat_mul( GLdouble* src, GLdouble* src2)
{

	GLdouble* out = (GLdouble* ) malloc( sizeof( GLdouble ) * 16 );

	Matrix4x4MultiplyBy4x4( (GLdouble (*)[4])src, (GLdouble (*)[4])src2, (GLdouble (*)[4])out);

	return out;
}

GLdouble* mat_translate( vector g)
{
	GLdouble* t = (GLdouble*)malloc( sizeof(GLdouble) * 16 );

	t[0] = 1; t[4] = 0; t[8] = 0; t[12] = g.x;
	t[1] = 0; t[5] = 1; t[9] = 0; t[13] = g.y;
	t[2] = 0; t[6] = 0; t[10] = 1; t[14] = g.z;
	t[3] = 0; t[7] = 0; t[11] = 0; t[15] = 1;

	return t;
}

GLdouble* mat_rotate( vector g, vector l, GLdouble angle)
{
	GLdouble c = cos( angle );
	GLdouble s = sin( angle );

	GLdouble c_ = 1-c;

	GLdouble* t = (GLdouble*)malloc( sizeof(GLdouble) * 16 );

	t[0] = g.x*g.x*c_ + c;     t[4] = g.x*g.y*c_ - g.z*s; t[8]  = g.x*g.z*c_+g.y*s; t[12] = 0;
	t[1] = g.y*g.x*c_ + g.z*s; t[5] = g.y*g.y*c_ + c;     t[9]  = g.y*g.z*c_-g.x*s; t[13] = 0;
	t[2] = g.x*g.z*c_ - g.y*s; t[6] = g.y*g.z*c_ + g.x*s; t[10] = g.z*g.z*c_ + c;   t[14] = 0;
	t[3] = 0;                  t[7] = 0;                  t[11] = 0;                t[15] = 1;
	/*		  ( xx(1-c)+c	xy(1-c)-zs  xz(1-c)+ys	 0  )
			  |					    |
			  | yx(1-c)+zs	yy(1-c)+c   yz(1-c)-xs	 0  |
			  | xz(1-c)-ys	yz(1-c)+xs  zz(1-c)+c	 0  |
			  |					    |
			  (	 0	     0		 0	 1  )
	 */

	return t;
}

GLdouble* mat_scale(  vector g )
{
	GLdouble* t = (GLdouble*)malloc( sizeof(GLdouble) * 16 );

	t[0] = g.x; t[4] = 0; t[8] = 0; t[12] = 0;
	t[1] = 0; t[5] = g.y; t[9] = 0; t[13] = 0;
	t[2] = 0; t[6] = 0; t[10] = g.z; t[14] = 0;
	t[3] = 0; t[7] = 0; t[11] = 0; t[15] = 1;

	return t;
}

GLdouble* mat_combine( GLdouble* tr, GLdouble* r, GLdouble* s)
{
	GLdouble* t = (GLdouble*)malloc( sizeof(GLdouble) * 16 );

	return t;
}


bool mat_inv(const GLdouble m[16], GLdouble invOut[16])
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


void mat_transform_vector( vector* out, GLdouble* m, vector in)
{

	GLdouble r_c[4]; 
	glGetDoublev( GL_CURRENT_RASTER_POSITION, r_c ); 

	GLdouble wc = r_c[3];

	out->x =  m[0]*in.x + m[4]*in.y + m[8]*in.z + m[12]*wc;
	out->y =  m[1]*in.x + m[5]*in.y + m[9]*in.z + m[13]*wc;
	out->z =  m[2]*in.x + m[6]*in.y + m[10]*in.z + m[14]*wc;

}
