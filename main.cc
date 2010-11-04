/* ============================================================================
 ** MAIN.CC based on 
 ** Demonstration of display lists
 ** Copyright (C) 2005  Julien Guertault 
 ** Modifications (very minor) by Brian Srivastava 2010 for University of Western Ontario
 ** CS4482a/9511 as Assignment 3.
 **
 ** This program is free software; you can redistribute it and/or
 ** modify it under the terms of the GNU General Public License
 ** as published by the Free Software Foundation; either version 2
 ** of the License, or (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program; if not, write to the Free Software
 ** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 **

 ** ========================================================================= */


/*
 * Attempt at scenegraph by Kartik Thakore 2010 
 *
 */ 

#include "scenegraph.h"


static int	rotate_list_id = 0;
static int	rotate_teapot_list_id = 0;
static int	teapot_list_id = 0;
static int	left_click = GLUT_UP;
static int	right_click = GLUT_UP;
static int	xold;
static int	yold;
static float	rotate_x = -30;
static float	rotate_y = 15;

/*
   SCENEGRAPH
 */

static scene_manager* Scene;

/*Function to load our object pointer data*/
void make_obj_data( object* obj )
{
 
        int vertices;
	int polygons;
	vector* vector_data = read_poly_file( "data/test_objects.txt", &vertices, &polygons );
	//Default color is read for the object.
	obj->polygon_color.x = 1;
	obj->polygon_color.y = 0;
	obj->polygon_color.z = 0;
	
	//All our objects are being drawn with GL_LINE_LOOP
	obj_load( obj, GL_LINE_LOOP, (void*)vector_data, vertices, polygons);

}

/* Fill up the scene with test data */
void make_obj(int argc, char **argv)
{

	//Make and setup the root node.
	object* first = obj_create( Scene );	

	make_obj_data( first );

	obj_color( first, 1, 0, 0 );
	obj_translate( first, 0, 0, 0 );
	sc_set_root( Scene, first );

	int i;

	//Add about 100 objects in various direction for rendering
	object* head = first;

	for( i =0; i < 100; i++)
	{


		object* a = obj_create( Scene );
		make_obj_data( a );
		obj_color( a, 0, 0, 1 );
		obj_translate( a,  0, 0, -0.1);
		
		obj_add( head, a );
		//Add each subsequent object to itself, to make a huge tree for the scene to use.
		head = a;

	}

	head = first;
	for( i =0; i < 100; i++)
	{
		object* a = obj_create( Scene );
		make_obj_data( a );
		obj_color( a, 0, 0, 1 );
		obj_translate( a,  0, 0, 0.1);
		
		obj_add( head, a );

		head = a;

	}



	 head = first;


	for( i =0; i < 100; i++)
	{
		object* a = obj_create( Scene );
		make_obj_data( a );
		obj_color( a, 1, 0, 0 );
		obj_translate( a,  -0.1, 0, 0);
		obj_add( head, a );

		head = a;

	}

	head = first;
	for( i =0; i < 100; i++)
	{
		object* a = obj_create( Scene );
		make_obj_data( a );
		obj_color( a, 0, 1, 0 );
		obj_translate( a,  0.1, 0, 0);
		obj_add( head, a );

		head = a;

	}


	 head = first;


	for( i =0; i < 100; i++)
	{
		object* a = obj_create( Scene );
		make_obj_data( a );
		obj_color( a, 1, 0, 0 );
		obj_translate( a,  0, 0.1, 0.0);
		
		obj_add( head, a );

		head = a;

	}

	head = first;
	for( i =0; i < 100; i++)
	{
		object* a = obj_create( Scene );
		make_obj_data( a );
		obj_color( a, 0, 1, 0 );
		obj_translate( a,  0, -0.1, 0);
		
		obj_add( head, a );

		head = a;

	}

	//Just to show functionality
	obj_remove( head);

}



/*
 ** The instructions to rotate each teapot, according to the mouse
 */
void		compile_rotate_list(void)
{
	glNewList(rotate_list_id, GL_COMPILE);
	glRotatef(rotate_y, 1, 0, 0);
	glRotatef(rotate_x, 0, 1, 0);
	glEndList();
}


/*
 ** Function called to update rendering
 */
void		DisplayFunc(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0, 0, -10.);

	glCallList(rotate_list_id);
	if( DEBUG )
		fprintf( stderr, "\nDoing ROOT\n" );

	// Get our frustum 
	sc_update_frustum( Scene );

	//Render the whole scene
	sc_render( Scene );
	/* End */
	glFlush();
	glutSwapBuffers();
}

/*
 ** Function called when the window is created or resized
 */
void		ReshapeFunc(int width, int height)
{
	glMatrixMode(GL_PROJECTION);  //GL_MODELVIEW

	glLoadIdentity();
	gluPerspective(20, width / (float) height, 5, 15);
	glViewport(0, 0, width, height);

	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

/*
 ** Function called when a key is hit
 */
void		KeyboardFunc(unsigned char key, int x, int y)
{
	xold = x; /* Has no effect: just to avoid a warning */
	yold = y;
	if ('q' == key || 'Q' == key || 27 == key)
	{
		glDeleteLists(rotate_list_id, 1);
		exit(0);
	}

	//Use the keys to play with the root location and rotation a bit
	else if( 'w' == key || 'W' == key )
	{
		
		object* root = sc_get_object (Scene, Scene->root_object_id);
		root->location.z += 0.01;
		glutPostRedisplay();	
	}
	else if( 's' == key || 'S' == key )
	{
		object* root = sc_get_object (Scene, Scene->root_object_id);
		root->location.z -= 0.01;
		glutPostRedisplay();	


	}
	else if( 'a' == key || 'A' == key )
	{
		
		object* root = sc_get_object (Scene, Scene->root_object_id);
		root->rotation.y += 1;
		glutPostRedisplay();	
	}
	else if( 'd' == key || 'D' == key )
	{
		object* root = sc_get_object (Scene, Scene->root_object_id);
		root->rotation.y -= 1;
		glutPostRedisplay();	


	}
}

/*
 ** Function called when a mouse button is hit
 */
void		MouseFunc(int button, int state, int x, int y)
{
	if (GLUT_LEFT_BUTTON == button)
		left_click = state;
	if (GLUT_RIGHT_BUTTON == button)
		right_click = state;
	xold = x;
	yold = y;
}

/*
 ** Function called when the mouse is moved
 */
void		MotionFunc(int x, int y)
{

	if (GLUT_DOWN == left_click)
	{
		rotate_y = rotate_y + (y - yold) / 5.f;
		rotate_x = rotate_x + (x - xold) / 5.f;
		if (rotate_y > 90)
			rotate_y = 90;
		if (rotate_y < -90)
			rotate_y = -90;

		/* Update the rotations */
		compile_rotate_list();

		glutPostRedisplay();
	}
	xold = x;
	yold = y;


}


int		main(int argc, char **argv)
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

	/* Compilation of the instructions lists */
	rotate_list_id = glGenLists(1);
	compile_rotate_list();

	/* Initialize the Scenegraph */

	Scene = sc_init( 601 ); 

	make_obj(argc, argv);

	/* Declaration of the callbacks */
	glutDisplayFunc(&DisplayFunc);
	glutReshapeFunc(&ReshapeFunc);
	glutKeyboardFunc(&KeyboardFunc);
	glutMouseFunc(&MouseFunc);
	glutMotionFunc(&MotionFunc);

	
	glutPostRedisplay();
	/* Loop */
	glutMainLoop();

	/* Never reached */
	return 0;
}
