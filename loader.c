#include <stdio.h> 
#include "object.h"
 


int load_file_to_memory(const char *filename, char **result) 
{ 
	unsigned int size = 0;
	FILE *f = fopen(filename, "rb");

	if (f == NULL) 
	{ 
		*result = NULL;
		return -1; // -1 means file opening fail 
	} 
	fseek(f, 0, SEEK_END);
	size = ftell(f);

	fseek(f, 0, SEEK_SET);
	*result = (char *)malloc(size+1);

	if (size != fread(*result, sizeof(char), size, f)) 
	{ 
		free(*result);
		return -2; // -2 means file reading fail 
	} 
	fclose(f);
	(*result)[size] = 0;

	return size;
}

object* load_object( const char* path )
{

   char* file;
   int lines = load_file_to_memory( path, &file );

   fprintf( stderr, "Loaded Lines %d, from %s \n" , lines, path );

    if( lines > 0 )
    {
   //Make an object with it 
        int i;
	for( i = 0; i < lines; i++ )
	{
		fprintf( stderr, "Data %s \n", file + i );
	} 

	   free(file);
    }

   return NULL;
}
