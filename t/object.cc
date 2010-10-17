#include <stdio.h>
#include "../object.h"

int main( int argc, char** argv)
{

	printf("Root tests\n");
	object* test_root = obj_create();

	obj_destroy( test_root );
	printf("Can Destroy Object\n");


	return 0;
}
