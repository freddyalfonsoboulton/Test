#include "raytracer.h"

/* typedef struct camera {
  vec *loc;
  unsigned int h;
  unsigned int w;
} camera;*/

 camera* camera_new(vec* loc, unsigned h, unsigned w){
 	camera* new_camera = malloc(sizeof(camera));
 	if(new_camera==NULL){
 		fprintf(stderr, "Pointer in camera_new was null\n");
 		exit(1);
 	}
 	new_camera->loc = loc;
 	new_camera->h = h;
 	new_camera->w = w;
 	return new_camera;
 }

 camera* camera_dup(camera* c){
 	//Deep Copy Implementation
 	camera* new_camera = malloc(sizeof(camera));
 	new_camera ->loc = vec_dup(c->loc);
 	new_camera->h = c->h;
 	new_camera->w = c->w;
 	return new_camera;
 }

 void camera_print(camera* c){
 	char* s = vec_tos(c->loc);
 	printf("Location: %s height: %u width: %u\n", s, c->h, c->w);
 	free(s);
 }

 void camera_free(camera* c){
 	vec_free(c->loc);
 	free(c);
 }
