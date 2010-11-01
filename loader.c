#include "scenegraph.h"

int read_poly_file( const char* file, vertex* data, int* polygons )
{

   char line[255];
   FILE* in = NULL;
   int i;
   int p = 0; 
   in = fopen("data/object3", "r");
  fprintf( stderr, "%p WTF D \n", data );
//   data = (vertex*)( malloc( sizeof(vertex) * 448 ) );
   
   if( in )
   {
	for(i = 0; i < 4896; i++)
	{
	  if(feof(in))
	     break;
	  fgets( line, 255, in);

		char sx[10];
		char sy[10];
		char sz[10];
  
	  if( i % 4 )
	  {
		int j;

	 
		for( j = 0; j < 10; j++)
		  sx[j] = line[j];
		for( j = 14; j < 24; j++)
		  sy[j-14] = line[j];
		for( j = 28; j < 37; j++)
		  sz[j-28] = line[j];
		//printf("Line: %s", line);
		//printf(" %s %s %s \n", sx, sy, sz);
	  }
	  else
	  {
		++p;
	
	  }
	  
	  if( (i % 4) == 3 )
	  {
		data[p-1].x = atof( sx );
		data[p-1].y = atof( sy );
		data[p-1].z = atof( sz );
		//printf(" %f %f %f \n",  data[p].x,  data[p].y,  data[p].z);
//		debug_vertex( data[p-1], "ASDSAD" );
	  }

	}
	fclose( in );

   }  

 *polygons = p;
  return i;
} 
