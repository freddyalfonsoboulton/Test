#include "raytracer.h"

vec* logical_loc(camera* c, vec* pos){
	double pixel_width = 2/(fmax(c->w,c->h));
	double w = (double)c->w;
	double h = (double)c->h;
	double logical_x;
	double logical_y;
	if(w>h){
		logical_x = -1+((pos->x)+0.5)*pixel_width;
		logical_y = h/w - ((pos->y)+0.5)*pixel_width;
	}
	else{
		logical_x = -w/h + ((pos->x)+0.5)*pixel_width;
		logical_y = 1 - ((pos->y)+0.5)*pixel_width;
	}
	return vec_new(logical_x,logical_y,0.0);
}

hit_test* intersect(ray* r, sphere* s){
	vec* ray_origin = r->origin;
	//Maybe take off norm?
	vec* ray_direction = r->direction;
	vec* sphere_center = s->center;
	double sphere_radius = s->radius;
	vec* A = vec_sub(ray_origin,sphere_center);
	double B = vec_dot(A,ray_direction);
	double C = vec_dot(A,A) - (sphere_radius*sphere_radius);
	double D = (B * B) - C;
	if(D>0){
		double t = (-1)*B - sqrt(D);
		if(t>0){
			vec* temp = ray_position(r,t);
			vec* v = vec_sub(temp,sphere_center);
			vec* surf_norm = vec_norm(v);
			hit_test* i = hit_test_new(t,s->color,surf_norm);
			return i;
		}
		else{
			return NULL;
		}
	}	
	else{
		return NULL;
		}
}

int shadow(vec* v, light* l, sphere_list* ss){
	vec* light_dir = l->direction;
	vec* nudge = vec_scale(0.001,light_dir);
	vec* lift = vec_add(v,nudge);
	ray* shadow_ray = ray_new(lift,light_dir);
	while(ss != NULL){
		hit_test* test = intersect(shadow_ray,ss->s);
		//If we hit something, we're in shadow
		if(test!=NULL){
			return 1;
		}
		else{
			ss = ss->next;
		}
	}
	//If we're out of the loop, we haven't hit anything
	return 0;
}

rgb* lighting(scene* s, ray* r, hit_test* h){
	sphere_list* sl = s->spheres;
	light* scene_light = s->light;
	rgb* ambient = s->amb;
	if(h==NULL){
		return s->bg;
	}
	else{
		rgb* surf_color = h->surf_color;
		vec* surf_norm = h->surf_norm;
		vec* hit_site = ray_position(r,h->dist);
		int shadow_bool = shadow(hit_site,scene_light,sl);
		//If we're in shadow
		if(shadow_bool){
			rgb* return_color = rgb_modulate(surf_color,ambient);
			return return_color;
		}
		//We're not in shadow
		else{
			vec* light_dir = scene_light->direction;
			rgb* light_color = scene_light->color;
			double temp = fmax(0.0,vec_dot(surf_norm,light_dir));
			rgb* diffuse = rgb_scale(temp,light_color);
			rgb* dif_plus_amb = rgb_add(ambient,diffuse);
			rgb* return_color = rgb_modulate(dif_plus_amb,surf_color);
			return return_color;
		}
	}
}

rgb* trace_ray(scene* s, ray* r){
	sphere_list* list = s->spheres;
	hit_test* test = NULL;
	while(list != NULL){
		hit_test* perm = intersect(r,list->s);
		if(perm != NULL){
			//The first thing we hit
			if(test == NULL){
				test = perm;
				list = list->next;
			}
			else{
				//
				if(perm->dist<test->dist){
					test = perm;
					list = list->next;
				}
				else{
					list = list->next;
				}
			}
		}
		//In the case we don't hit anything
		else{
			list = list->next;
		}	
	}
	return lighting(s,r,test);
}

void iterate_row(camera* camera, sphere_list* sl, scene* s, unsigned width, unsigned fixed_y){
	vec* camera_loc = camera->loc;
	int i=0;
	while(i<width){
		vec* physical_loc = vec_new((double)i,fixed_y,0.0);
		vec* pixel_loc = logical_loc(camera,physical_loc);
		vec* normed_direction = vec_norm(vec_sub(pixel_loc,camera_loc));
		ray * iterated_ray = ray_new(camera_loc,normed_direction);
		rgb* hit_color = trace_ray(s,iterated_ray);
		rgb_print_bytes(hit_color);
		i++;
	}
}

void iterate_grid(camera* camera, sphere_list* sl, scene* s, unsigned width, unsigned height){
	int i = 0;
	while(i<height){
		iterate_row(camera,sl,s,width, i);
		++i;
	}
}

void render(stage* g){
	unsigned height = g->c->h;
	unsigned width = g->c->w;
	camera* camera = g->c;
	sphere_list* list = g->s->spheres;
	scene* scene = g->s;
	printf("P3\n");
	printf("%u %u\n",width,height);
	iterate_grid(camera,list,scene,width,height);
}

