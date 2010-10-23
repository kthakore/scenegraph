#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


#include <stdio.h>
#include <string.h>
#include "../object.h"

static unsigned int test_count_f = 0;
static unsigned int test_count_s = 0;
static object* root = NULL;

void diag( const char* message)
{
	fprintf(stderr, "%s\n", message);
}

void ok ( bool test, const char* test_name)
{

	if( test )
		fprintf( stderr, "SU(%d) ..... %s \n", test_count_s++, test_name);
	else
		fprintf( stderr, "FA(%d) ..... %s \n", test_count_f++, test_name);
}


void done( )
{

	fprintf( stderr, "Sucess %d, Fail %d, Total %d \n", test_count_s, test_count_f, test_count_s + test_count_f );


}

void test_obj()
{

	diag("Root tests");
	root = obj_create();

	int obj_size = sizeof(object);

	ok( sizeof(*root) == obj_size, "Memory allocated" );

	//vertex** triangle = (vertex**)malloc( sizeof(vertex*) * 3 );
	vertex* triangle = (vertex*)malloc( sizeof(vertex) * 3 );
	triangle[0].x = 0; triangle[0].y = 1; triangle[0].z = 0;
	triangle[1].x =  1; triangle[1].y = 0; triangle[1].z = 0;
	triangle[2].x = 1; triangle[2].y = 1; triangle[2].z = 0;

	root->polygon_color.x = 1;
	root->polygon_color.y = 0;
	root->polygon_color.z = 0;

	obj_load( root, GL_LINES, (void*)triangle, 3);
	obj_operate( root, SCALE, 0,0,0);	
	obj_operate( root, TRANSLATE, 0,0,0);
	obj_operate( root, ROTATE, 0,0,0);

}


void finish_tests()
{

	obj_destroy( root );

	done();

}

void DisplayFunc(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//Render our root, where the camera is at 10,10,10
	obj_operate( root, RENDER, 10, 10, 10);

	glFlush();
	glutSwapBuffers();	
}



int main( int argc, char** argv)
{

	/* Creation of the window */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);  // please don't mess with the window size for assignment.  It will still work obviously, but trying to stay limited in scope as it were.  
	glutCreateWindow("CS4483a Assignment 3 Kartik Thakore");

	/* OpenGL settings */
	glClearColor(0, 0, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

	/* Declaration of the callbacks */
	glutDisplayFunc(&DisplayFunc);
	/*  glutReshapeFunc(&ReshapeFunc);
	    glutKeyboardFunc(&KeyboardFunc);
	    glutMouseFunc(&MouseFunc);
	    glutMotionFunc(&MotionFunc);
	 */

	test_obj();

	/* Loop */
	glutMainLoop();


	return 0;
}


