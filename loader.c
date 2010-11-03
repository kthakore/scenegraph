#include "scenegraph.h"

vector* read_poly_file( const char* file, int* v_count, int* polygons )
{

	char line[255];
	FILE* in = NULL;
	int i;
	int p = 0; 
	in = fopen(file, "r");


	int data_lines;
	//Get the number of data lines
	fgets( line, 255, in );
	data_lines = atoi( line );

	int vector_count;
	//Get the number of data lines
	fgets( line, 255, in );
	vector_count = atoi( line );

	int poly_count;
	fgets( line, 255, in );
	poly_count = atoi( line );

	vector* data; 

	data = (vector*)( malloc( sizeof(vector) * (vector_count+2) ) );

	if( in )
	{
		for(i = 0; i < poly_count; i++)
		{
			if(feof(in))
				break;

			fgets( line, 255, in);

			int k;
			for(k = 0; k < 3; k++)
			{
				fgets( line, 255, in);
				char sx[10];
				char sy[10];
				char sz[10];

				int j;
				for( j = 0; j < 10; j++)
					sx[j] = line[j];
				for( j = 14; j < 24; j++)
					sy[j-14] = line[j];
				for( j = 28; j < 37; j++)
					sz[j-28] = line[j];

				data[p].x = atof( sx );
				data[p].y = atof( sy );
				data[p].z = atof( sz );
				p++;
			}


		}
		
	}  
	fclose( in );

	*v_count = vector_count;
	*polygons = poly_count;
	return data;
} 
