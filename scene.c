#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#include "scene.h"
#include "object.h"


void set_scene( scene_manager* Scene )
{

   GLfloat model_matrix[16];
   GLfloat projection_matrix[16];
   GLfloat clip_matrix[16];
   GLfloat t;

 /* Get the current PROJECTION matrix from OpenGL */
   glGetFloatv( GL_PROJECTION_MATRIX, projection_matrix );

 /* Get the current MODELVIEW matrix from OpenGL */
   glGetFloatv( GL_MODELVIEW_MATRIX, model_matrix );

 /* Combine the two matrices (multiply projection_matrixection by modelview)    */
   clip_matrix[ 0] = model_matrix[ 0] * projection_matrix[ 0] + model_matrix[ 1] * projection_matrix[ 4] + model_matrix[ 2] * projection_matrix[ 8] +    model_matrix[ 3] * projection_matrix[12];
   clip_matrix[ 1] = model_matrix[ 0] * projection_matrix[ 1] + model_matrix[ 1] * projection_matrix[ 5] + model_matrix[ 2] * projection_matrix[ 9] +    model_matrix[ 3] * projection_matrix[13];
   clip_matrix[ 2] = model_matrix[ 0] * projection_matrix[ 2] + model_matrix[ 1] * projection_matrix[ 6] + model_matrix[ 2] * projection_matrix[10] +    model_matrix[ 3] * projection_matrix[14];
   clip_matrix[ 3] = model_matrix[ 0] * projection_matrix[ 3] + model_matrix[ 1] * projection_matrix[ 7] + model_matrix[ 2] * projection_matrix[11] +    model_matrix[ 3] * projection_matrix[15];

   clip_matrix[ 4] = model_matrix[ 4] * projection_matrix[ 0] + model_matrix[ 5] * projection_matrix[ 4]    + model_matrix[ 6] * projection_matrix[ 8] + model_matrix[ 7] * projection_matrix[12];
   clip_matrix[ 5] = model_matrix[ 4] * projection_matrix[ 1] + model_matrix[ 5] * projection_matrix[ 5] + model_matrix[ 6] * projection_matrix[ 9] +    model_matrix[ 7] * projection_matrix[13];
   clip_matrix[ 6] = model_matrix[ 4] * projection_matrix[ 2] + model_matrix[ 5] * projection_matrix[ 6] + model_matrix[ 6] * projection_matrix[10] +    model_matrix[ 7] * projection_matrix[14];
   clip_matrix[ 7] = model_matrix[ 4] * projection_matrix[ 3] + model_matrix[ 5] * projection_matrix[ 7] + model_matrix[ 6] * projection_matrix[11] +    model_matrix[ 7] * projection_matrix[15];

   clip_matrix[ 8] = model_matrix[ 8] * projection_matrix[ 0] + model_matrix[ 9] * projection_matrix[ 4]    + model_matrix[10] * projection_matrix[ 8] + model_matrix[11] * projection_matrix[12];
   clip_matrix[ 9] = model_matrix[ 8] * projection_matrix[ 1] + model_matrix[ 9] * projection_matrix[ 5] + model_matrix[10] * projection_matrix[ 9] +    model_matrix[11] * projection_matrix[13];
   clip_matrix[10] = model_matrix[ 8] * projection_matrix[ 2] + model_matrix[ 9] * projection_matrix[ 6] + model_matrix[10] * projection_matrix[10] +    model_matrix[11] * projection_matrix[14];
   clip_matrix[11] = model_matrix[ 8] * projection_matrix[ 3] + model_matrix[ 9] * projection_matrix[ 7] + model_matrix[10] * projection_matrix[11] +    model_matrix[11] * projection_matrix[15];

   clip_matrix[12] = model_matrix[12] * projection_matrix[ 0] + model_matrix[13] * projection_matrix[ 4]    + model_matrix[14] * projection_matrix[ 8] + model_matrix[15] * projection_matrix[12];
   clip_matrix[13] = model_matrix[12] * projection_matrix[ 1] + model_matrix[13] * projection_matrix[ 5] + model_matrix[14] * projection_matrix[ 9] +    model_matrix[15] * projection_matrix[13];
   clip_matrix[14] = model_matrix[12] * projection_matrix[ 2] + model_matrix[13] * projection_matrix[ 6] + model_matrix[14] * projection_matrix[10] +    model_matrix[15] * projection_matrix[14];
   clip_matrix[15] = model_matrix[12] * projection_matrix[ 3] + model_matrix[13] * projection_matrix[ 7] + model_matrix[14] * projection_matrix[11] +    model_matrix[15] * projection_matrix[15];

 /* Extract the numbers for the RIGHT plane */
   Scene->frustum[0][0] = clip_matrix[ 3] - clip_matrix[ 0];
   Scene->frustum[0][1] = clip_matrix[ 7] - clip_matrix[ 4];
   Scene->frustum[0][2] = clip_matrix[11] - clip_matrix[ 8];
   Scene->frustum[0][3] = clip_matrix[15] - clip_matrix[12];

 /* Normalize the result */
   t = sqrt( Scene->frustum[0][0] * Scene->frustum[0][0] + Scene->frustum[0][1] * Scene->frustum[0][1] + Scene->frustum[0][2]    * Scene->frustum[0][2] );
   Scene->frustum[0][0] /= t;
   Scene->frustum[0][1] /= t;
   Scene->frustum[0][2] /= t;
   Scene->frustum[0][3] /= t;

 /* Extract the numbers for the LEFT plane */
   Scene->frustum[1][0] = clip_matrix[ 3] + clip_matrix[ 0];
   Scene->frustum[1][1] = clip_matrix[ 7] + clip_matrix[ 4];
   Scene->frustum[1][2] = clip_matrix[11] + clip_matrix[ 8];
   Scene->frustum[1][3] = clip_matrix[15] + clip_matrix[12];

 /* Normalize the result */
   t = sqrt( Scene->frustum[1][0] * Scene->frustum[1][0] + Scene->frustum[1][1] * Scene->frustum[1][1] + Scene->frustum[1][2]    * Scene->frustum[1][2] );
   Scene->frustum[1][0] /= t;
   Scene->frustum[1][1] /= t;
   Scene->frustum[1][2] /= t;
   Scene->frustum[1][3] /= t;

 /* Extract the BOTTOM plane */
   Scene->frustum[2][0] = clip_matrix[ 3] + clip_matrix[ 1];
   Scene->frustum[2][1] = clip_matrix[ 7] + clip_matrix[ 5];
   Scene->frustum[2][2] = clip_matrix[11] + clip_matrix[ 9];
   Scene->frustum[2][3] = clip_matrix[15] + clip_matrix[13];

 /* Normalize the result */
   t = sqrt( Scene->frustum[2][0] * Scene->frustum[2][0] + Scene->frustum[2][1] * Scene->frustum[2][1] + Scene->frustum[2][2]    * Scene->frustum[2][2] );
   Scene->frustum[2][0] /= t;
   Scene->frustum[2][1] /= t;
   Scene->frustum[2][2] /= t;
   Scene->frustum[2][3] /= t;

 /* Extract the TOP plane */
   Scene->frustum[3][0] = clip_matrix[ 3] - clip_matrix[ 1];
   Scene->frustum[3][1] = clip_matrix[ 7] - clip_matrix[ 5];
   Scene->frustum[3][2] = clip_matrix[11] - clip_matrix[ 9];
   Scene->frustum[3][3] = clip_matrix[15] - clip_matrix[13];

 /* Normalize the result */
   t = sqrt( Scene->frustum[3][0] * Scene->frustum[3][0] + Scene->frustum[3][1] * Scene->frustum[3][1] + Scene->frustum[3][2]    * Scene->frustum[3][2] );
   Scene->frustum[3][0] /= t;
   Scene->frustum[3][1] /= t;
   Scene->frustum[3][2] /= t;
   Scene->frustum[3][3] /= t;

 /* Extract the FAR plane */
   Scene->frustum[4][0] = clip_matrix[ 3] - clip_matrix[ 2];
   Scene->frustum[4][1] = clip_matrix[ 7] - clip_matrix[ 6];
   Scene->frustum[4][2] = clip_matrix[11] - clip_matrix[10];
   Scene->frustum[4][3] = clip_matrix[15] - clip_matrix[14];

 /* Normalize the result */
   t = sqrt( Scene->frustum[4][0] * Scene->frustum[4][0] + Scene->frustum[4][1] * Scene->frustum[4][1] + Scene->frustum[4][2]    * Scene->frustum[4][2] );
   Scene->frustum[4][0] /= t;
   Scene->frustum[4][1] /= t;
   Scene->frustum[4][2] /= t;
   Scene->frustum[4][3] /= t;

 /* Extract the NEAR plane */
   Scene->frustum[5][0] = clip_matrix[ 3] + clip_matrix[ 2];
   Scene->frustum[5][1] = clip_matrix[ 7] + clip_matrix[ 6];
   Scene->frustum[5][2] = clip_matrix[11] + clip_matrix[10];
   Scene->frustum[5][3] = clip_matrix[15] + clip_matrix[14];

 /* Normalize the result */
   t = sqrt( Scene->frustum[5][0] * Scene->frustum[5][0] + Scene->frustum[5][1] * Scene->frustum[5][1] + Scene->frustum[5][2]    * Scene->frustum[5][2] );
   Scene->frustum[5][0] /= t;
   Scene->frustum[5][1] /= t;
   Scene->frustum[5][2] /= t;
   Scene->frustum[5][3] /= t;

    
}

scene_manager* init_scene()
{

   scene_manager* Scene = (scene_manager*)malloc( sizeof(scene_manager) );

   set_scene( Scene );

   return Scene;

}

int CubeInFrustum( scene_manager* Scene, float x, float y, float z, float size )
{
  int p;
  int c;
  int c2 = 0;

  for( p = 0; p < 6; p++ )
  {
    c = 0;
    if( Scene->frustum[p][0] * (x - size) + Scene->frustum[p][1] * (y - size) + Scene->frustum[p][2]    * (z - size) + Scene->frustum[p][3] > 0 )
      c++;
    if( Scene->frustum[p][0] * (x + size) + Scene->frustum[p][1] * (y - size) + Scene->frustum[p][2]    * (z - size) + Scene->frustum[p][3] > 0 )
      c++;
    if( Scene->frustum[p][0] * (x - size) + Scene->frustum[p][1] * (y + size) + Scene->frustum[p][2]    * (z - size) + Scene->frustum[p][3] > 0 )
      c++;
    if( Scene->frustum[p][0] * (x + size) + Scene->frustum[p][1] * (y + size) + Scene->frustum[p][2]    * (z - size) + Scene->frustum[p][3] > 0 )
      c++;
    if( Scene->frustum[p][0] * (x - size) + Scene->frustum[p][1] * (y - size) + Scene->frustum[p][2]    * (z + size) + Scene->frustum[p][3] > 0 )
      c++;
    if( Scene->frustum[p][0] * (x + size) + Scene->frustum[p][1] * (y - size) + Scene->frustum[p][2]    * (z + size) + Scene->frustum[p][3] > 0 )
      c++;
    if( Scene->frustum[p][0] * (x - size) + Scene->frustum[p][1] * (y + size) + Scene->frustum[p][2]    * (z + size) + Scene->frustum[p][3] > 0 )
      c++;
    if( Scene->frustum[p][0] * (x + size) + Scene->frustum[p][1] * (y + size) + Scene->frustum[p][2]    * (z + size) + Scene->frustum[p][3] > 0 )
      c++;
    if( c == 0 )
      return 0;
    if( c == 8 )
      c2++;
  }
  return (c2 == 6) ? 2 : 1;
}
