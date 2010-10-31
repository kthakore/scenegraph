#include "scenegraph.h"

scene_manager* sc_init(int objects) {

   scene_manager* Scene = (scene_manager*)malloc( sizeof(scene_manager) );

   Scene->object_registry = (object*)malloc(sizeof(object) * objects ); 

   return Scene;
}
