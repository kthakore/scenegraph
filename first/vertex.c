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

GLfloat vertex_dist( vertex a, vertex b)
{
	
	vertex val;

	sub_vertex( &val, a, b );
	squared_vertex( &val );
	
	return sqrt( val.x + val.y + val.z  );

}
