/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:59:42 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/04 09:29:41 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "../raytracing/raytracing.h"

t_point    pixel_to_coord(t_scene *scene, int pixel_x, int pixel_y)
{
	t_point coord;
	float   width = 30.0;
	float   height = 30.0;

	coord.x = scene->camera.coordinates.x - (width / 2)
		+ (width * ((float)pixel_x / (float)img->width));
	coord.y = scene->camera.coordinates.y + (height / 2)
		- (height * ((float)pixel_y / (float)img->height));
	coord.z = width / (2 * tan((double)scene->camera.field_of_view / 2));
	return (coord);
}

void	ft_render(void *param)
{
	t_scene		*scene;
	uint32_t	color;
	unsigned int pixel_x;
	unsigned int pixel_y;
	t_ray ray;
	int i;

	i = 0;
	scene = param;
	pixel_y = 0;
	while (pixel_y < img->width)
	{
		pixel_x = 0;
		while (pixel_x < img->height)
		{
			i++;
			ray = create_ray(scene, pixel_x, pixel_y);
			color = trace_ray(scene, ray, i);
			mlx_put_pixel(img, pixel_x, pixel_y, color);
			pixel_x++;
		}
		pixel_y++;
	}
}

t_point	*intersection(t_object	*obj, t_ray ray, t_point *temp_hit)
{
	if (obj->body_type == SPHERE)
		if (sphere_intersect(obj, ray, temp_hit))
			return (temp_hit);
	if (obj->body_type == PLANE)
		if (plane_intersect(obj, ray, temp_hit))
			return (temp_hit);
	if (obj->body_type == CYLINDER)
		if (cylinder_intersect(obj, ray, temp_hit))
			return (temp_hit);
	return (NULL);
}

float   apply_light(t_scene *scene, t_point hit_point, t_object *object)
{
	float i;
	t_vector    N;
	t_vector    L;
	t_ray ray;
	t_point light_intersection;
	t_list  *temp_node;
	t_object *temp_obj;
	
	i = scene->ambient.ratio;
	temp_node = scene->objects;
	N = normalize(object->surface_normal);
	L = subtract_points(scene->light.coordinates, hit_point);
	ray.origin = hit_point;
	ray.direction = normalize(L);
	while (temp_node)
	{
		temp_obj = (t_object *)temp_node->content;
		if (temp_obj != object && intersection(temp_obj, ray, &light_intersection) &&
			equal_points(get_nearest_point(light_intersection, scene->light.coordinates, hit_point), light_intersection))
			return (i);
		temp_node = temp_node->next;
	}
	if (dot_product(N, L) > 0)
		i += scene->light.brightness_ratio * (dot_product(N, L)/(vector_length(N) * vector_length(L)));
	return (i);
}

t_ray	create_ray(t_scene *scene, int pixel_x, int pixel_y)
{
	t_ray ray;
	
	ray.origin = scene->camera.coordinates;
	ray.direction = normalize(init_vector_p(pixel_to_coord(scene, pixel_x, pixel_y),
					scene->camera.coordinates));
	return (ray);
}

uint32_t rgb_to_uint32(uint32_t r, uint32_t g, uint32_t b, float brightness, t_scene *scene)
{
	uint32_t sc_r;
	uint32_t sc_g;
	uint32_t sc_b;

	sc_r = (uint32_t)(r * brightness + (scene->ambient.color.r * scene->ambient.ratio * 0.4));
	sc_g = (uint32_t)(g * brightness + (scene->ambient.color.g * scene->ambient.ratio * 0.4));
	sc_b = (uint32_t)(b * brightness + (scene->ambient.color.b * scene->ambient.ratio * 0.4));

	if (sc_r > 255)
		sc_r = 255;
	if (sc_g > 255)
		sc_g = 255;
	if (sc_b > 255)
		sc_b = 255;
	
	return (sc_r << 24 | sc_g << 16 | sc_b << 8 | 255);
}

uint32_t trace_ray(t_scene *scene, t_ray ray, int i)
{
	uint32_t	color;
	t_list		*temp;
	t_object	*object;
	t_point		temp_hit;
	t_point		closest_hit;
	t_object	*closest_obj;
	t_color test;

	temp = scene->objects;
	closest_obj = NULL;
	i = 0;
	color = rgb_to_uint32(0, 0, 0, 0, scene);
	//color = rgb_to_uint32(scene->texture.color[i].r, scene->texture.color[i].g, scene->texture.color[i].b, 1, scene);
	//return (color);
	while (temp)
	{
		object = (t_object *)temp->content;
		if (intersection(object, ray, &temp_hit))
		{
			if (!closest_obj || equal_points(get_nearest_point(temp_hit, closest_hit, ray.origin), temp_hit))
			{
				closest_hit = temp_hit;
				closest_obj = object;
				if (object->body_type == SPHERE)
				{
					test = sphere_texture(scene, closest_hit, object);
					color = rgb_to_uint32(test.r, test.g, test.b, apply_light(scene, temp_hit, object), scene);
				}
				else
					color = rgb_to_uint32(closest_obj->color.r,
						closest_obj->color.g, closest_obj->color.b, apply_light(scene, temp_hit, object), scene);
			}
		}
		temp = temp->next;
	}
	return (color);
}

float clamp(float value, float min, float max) {
    if (value < min) {
        return min;
    } else if (value > max) {
        return max;
    } else {
        return value;
    }
}

t_color sphere_texture(t_scene *scene, t_point closest_hit, t_object *object)
{
	t_vector p;
	float u;
	float v;
	unsigned int pixel;
	t_sphere *sphere;

	sphere = (t_sphere *)object->body.sphere;
	p = normalize(subtract_points(closest_hit, sphere->center));
	u = 0.5 - (atan2(-p.z, p.x) / (2.0 * M_PI));
	if (u == 0.5)
		printf("u is: %f\n", u);
	v = 0.5 - (asin(p.y) / M_PI);
	// 	p = normalize(subtract_points(closest_hit, sphere->center));
	if (v == 0)
		printf("v is: %f\n\n", v);
	pixel = (u * 2048) * 2048 + (v * 1024); 
	int x = (int)(u * 2048);
	int y = (int)(v * 1024);
	// x = clamp(x, 0, 2047);
	// y = clamp(x, 0, 1023);
	pixel = y * 2048 + x;
	//printf("pixel is: %u\n", pixel);
	// if (pixel > 100000)
	// 	pixel = 100000;
	return (scene->texture.color[pixel]);
}

// t_color sphere_texture(t_scene *scene, t_point closest_hit, t_object *object)
// {
// 	t_vector p;
// 	float u;
// 	float v;
// 	unsigned int pixel;
// 	t_sphere *sphere;

// 	sphere = (t_sphere *)object->body.sphere;
// 	p = normalize(subtract_points(closest_hit, sphere->center));
// 	u = (atan2(-p.z, p.x) + M_PI) / (2.0 * M_PI);
// 	printf("u is: %f\n", u);
// 	v = acos(p.y) / M_PI;
// 	printf("v is: %f\n\n", v);
// 	pixel = (unsigned int)(v * 1024) * (2048 + u * 2048);
// 	//printf("pixel is: %u\n", pixel);
// 	if (pixel > 100000)
// 		pixel = 100000;
// 	return (scene->texture.color[pixel]);
// }