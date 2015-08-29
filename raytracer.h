#ifndef __RAYTRACER_H__
#define __RAYTRACER_H__

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

/* ============================= */ 
/* ============================= */ 
/* === STRUCTURE DEFINITIONS === */ 
/* ============================= */ 
/* ============================= */ 

typedef unsigned char byte;

typedef struct vec {
  double x;
  double y;
  double z;
} vec;

typedef struct rgb {
  /* each value must be on interval [0, 1] */
    double r;
    double g;
    double b;
} rgb;

typedef struct ray {
  vec *origin;
  vec *direction;
} ray;

typedef struct sphere {
  vec *center;
  double radius;
  rgb *color;
} sphere;

typedef struct sphere_list sphere_list;
/* convention: NULL is the empty sphere list */
struct sphere_list {
  sphere *s;
  sphere_list *next;
};

typedef struct light {
  vec *direction;
  rgb *color;
} light;

typedef struct scene {
  rgb *bg;
  sphere_list *spheres;
  light *light;
  rgb *amb;
} scene;

typedef struct hit_test {
  double dist;
  rgb *surf_color;
  vec *surf_norm;
} hit_test;
/* hit_test convention: NULL is a miss */

typedef struct camera {
  vec *loc;
  unsigned int h;
  unsigned int w;
} camera;

typedef struct stage {
  camera *c;
  scene *s;
} stage;

/* ================== */ 
/* ================== */ 
/* === OPERATIONS === */ 
/* ================== */ 
/* ================== */ 

/* Please note: the following is not necessarily every operation you will need,
 * nor will you necessarily use every operation here in your implementation.
 */

/* ================================== */ 
/* === vector operations => vec.c === */ 
/* ================================== */ 

vec *vec_new(double x, double y, double z);

vec *vec_dup(vec *v);

vec *vec_add(vec *v1, vec *v2);

vec *vec_sub(vec *v1, vec *v2);

vec *vec_neg(vec *v);

vec *vec_scale(double s, vec *v);

double vec_dot(vec *v1, vec *v2);

double vec_mag(vec *v);

/* if a vector's magnitude is zero, it can't be normalized; simply return it */
vec *vec_norm(vec *v);

char *vec_tos(vec *v);

void vec_print(vec *v);

void vec_free(vec *v);

/* =============================== */ 
/* === rgb operations => rgb.c === */ 
/* =============================== */ 

rgb *rgb_new(double r, double g, double b);

rgb *rgb_dup(rgb *c);

rgb *rgb_modulate(rgb *c1, rgb *c2);

rgb *rgb_scale(double s, rgb *c);

rgb *rgb_add(rgb *c1, rgb *c2);

char *rgb_tos(rgb *c);

void rgb_print(rgb *c);

void rgb_free(rgb *c);

/* print three integer values on [0,255] with spaces in between and a newline */
void rgb_print_bytes(rgb *c);

/* =============================== */ 
/* === ray operations => ray.c === */ 
/* =============================== */ 

ray *ray_new(vec *origin, vec *direction);

ray *ray_dup(ray *r);

vec *ray_position(ray *r, double time);

char *ray_tos(ray *r);

void ray_print(ray *r);

void ray_free(ray *r);

/* ===================================== */ 
/* === sphere operations => sphere.c === */ 
/* ===================================== */ 

sphere *sphere_new(vec *center, double radius, rgb *color);

sphere *sphere_dup(sphere *s);

char *sphere_tos(sphere *s);

void sphere_print(sphere *s);

void sphere_free(sphere *s);

/* ======================================== */ 
/* === sphere list ops => sphere_list.c === */ 
/* ======================================== */ 

sphere_list *sl_cons(sphere *s, sphere_list *ss);

sphere_list *sl_singleton(sphere *s);

sphere_list* sl_dup(sphere_list* ss); 

void sl_print(sphere_list *ss);

void sl_free(sphere_list *ss);

/* =================================== */ 
/* === light operations => light.c === */ 
/* =================================== */ 

light *light_new(vec *direction, rgb *color);

light *light_dup(light *l);

void light_print(light *l);

void light_free(light *l);

/* =================================== */ 
/* === scene operations => scene.c === */ 
/* =================================== */ 

scene *scene_new(rgb *bg, sphere_list *ss, light *light, rgb *amb);

scene* scene_dup(scene* s); 

void scene_print(scene *s);

void scene_free(scene *s);

/* ========================================= */ 
/* === hit_test operations => hit_test.c === */ 
/* ========================================= */ 

hit_test *hit_test_new(double dist, rgb *surf_color, vec *surf_norm);

hit_test *hit_test_dup(hit_test *t);

void hit_test_print(hit_test *t);

void hit_test_free(hit_test *t);

/* ===================================== */ 
/* === camera operations => camera.c === */ 
/* ===================================== */ 

camera *camera_new(vec *loc, unsigned int h, unsigned int w);

camera *camera_dup(camera *c);

void camera_print(camera *c);

void camera_free(camera *c);

/* =================================== */ 
/* === stage operations => stage.c === */ 
/* =================================== */ 

stage *stage_new(camera *c, scene *s);

stage *stage_dup(stage *c); 

void stage_print(stage *s); 

void stage_free(stage *s); 

/* The function get_stage just needs to return a valid stage. */
/* Any valid stage. */
/* The string future_expansion is not used in project 1. */
stage *get_stage(char *future_expansion);

/* ================================================ */ 
/* ================================================ */ 
/* === RAY TRACER LOGIC and MAIN => raytracer.c === */ 
/* ================================================ */ 
/* ================================================ */ 

hit_test *intersect(ray *r, sphere *s);

int shadow(vec *v, light *l, sphere_list *ss);

rgb *lighting(scene *s, ray *r, hit_test *h);

vec *logical_loc(camera *c, vec *pos);

rgb *trace_ray(scene *s, ray *r);

void render(stage *g);

/* main should simply call get_stage */
/* and render the stage it gets */
/* (printing the resulting ppm to stdout) */
int main(int argc, char *argv[]);

#endif /* __RAYTRACER_H__ */