#include "raytracer.h"

/*typedef struct hit_test {
  double dist;
  rgb *surf_color;
  vec *surf_norm;
} hit_test; */

  hit_test* hit_test_new(double dist, rgb *surf_color, vec *surf_norm){
  	hit_test* new_hittest = malloc(sizeof(hit_test));
  	if(new_hittest==NULL){
  		fprintf(stderr, "Pointer in hit_test_new was null.\n");
  		exit(1);
  	}
  	new_hittest->dist = dist;
  	new_hittest->surf_color = surf_color;
  	new_hittest->surf_norm = surf_norm;
  	return new_hittest;
  }

  hit_test* hit_test_dup(hit_test* ht){
  	hit_test* duplicate = malloc(sizeof(hit_test));
  	duplicate->dist = ht->dist;
  	duplicate->surf_color=ht->surf_color;
  	duplicate->surf_norm=ht->surf_norm;
  	return duplicate;
  }

  void hit_test_print(hit_test* t){
  	if(t==NULL){
  		printf("Ray did not intersect the sphere\n");
  	}
  	else{
  		char* s = rgb_tos(t->surf_color);
  		char* p = vec_tos(t->surf_norm);
  		printf("Distance: %lf\n", t->dist);
  		printf("Color: %s\n", s);
  		printf("Surface Norm: %s\n",p);
  		free(s);
  		free(p);
  	}
  	return;
  }

  void hit_test_free(hit_test* t){
  	rgb_free(t->surf_color);
  	vec_free(t->surf_norm);
  	free(t);
  	return;
  }
/*
  hit_test* intersect(ray* r, sphere* s){
  	vec* ray_origin = r->origin;
  	vec* ray_direction = vec_norm(r->direction);
  	vec* sphere_center = s -> center;
  	double sphere_radius = s->radius;
  	vec* A = vec_sub(ray_origin, sphere_center);
  	double B = vec_dot(A,ray_direction);
  	double C = (vec_dot(A,A)) - (sphere_radius*sphere_radius);
  	double D = (B*B) - C;
  	double t = (-B - sqrt(D));
  	vec* temp = vec_sub(r,sphere_center);
  	vec* v = ray_position(temp,v);
  	vec* surf_norm = vec_norm(v)
  	if(D>0 && t > 0){
  		hit_test* intersection = hit_test_new(t,s->color,surf_norm);
  		free(ray_direction);
  		free(A);
  		free(B);
  		free(C);
  		free(temp);
  		free(v);
  		return intersection;
  	}
  	if(D > 0 && t<= 0){
  		return NULL;
  	}
  	if(D <= 0){
  		return NULL;
  	}  
    

  }
  */


