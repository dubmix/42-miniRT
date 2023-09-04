/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:59:42 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/04 15:19:59 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "../raytracing/raytracing.h"

/* t_point    pixel_to_coord(t_scene *scene, int pixel_x, int pixel_y)
{
	t_point coord;
	float   width = 2.0;
	float   height = 2 * (float)img->height/(float)img->width;

	coord.x = scene->camera.coordinates.x - (width / 2)
		+ (width * ((float)pixel_x / (float)img->width));
	coord.y = scene->camera.coordinates.y + (height / 2)
		- (height * ((float)pixel_y / (float)img->height));
	coord.z = 1.0;
	return (coord);
} */

t_point    pixel_to_coord(t_scene *scene, int pixel_x, int pixel_y)
{
	t_point coord;
	float   width = 2.0;
	float   height = 2.0; //adapt later with ratio
	
	float	pixel_NDC_x = ((float)(pixel_x) + 0.5) / (float)scene->mlx->width;
	float	pixel_NDC_y = ((float)(pixel_y) + 0.5) / (float)scene->mlx->height;

	float	image_aspect_ratio = (float)scene->mlx->width / (float )scene->mlx->height;
	float	pixel_screen_x = (2 * pixel_NDC_x - 1) * image_aspect_ratio * tanf(scene->camera.field_of_view / 2);
	float	pixel_screen_y = 1 - 2 * pixel_NDC_y;

	coord.x = pixel_screen_x;
	coord.
	
	return (coord);
}

void	ft_render(void *param)
{
	t_scene		*scene;
	uint32_t	color;
	unsigned int pixel_x;
	unsigned int pixel_y;
	t_ray ray;

	scene = param;
	pixel_x = 0;
	while (pixel_x < img->width)
	{
		pixel_y = 0;
		while (pixel_y < img->height)
		{
			ray = create_ray(scene, pixel_x, pixel_y);
			color = trace_ray(scene, ray);
			mlx_put_pixel(img, pixel_x, pixel_y, color);
			pixel_y++;
		}
		pixel_x++;
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

uint32_t trace_ray(t_scene *scene, t_ray ray)
{
	uint32_t	color;
	t_list		*temp;
	t_object	*object;
	t_point		temp_hit;
	t_point		closest_hit;
	t_object	*closest_obj;

	temp = scene->objects;
	closest_obj = NULL;
	color = rgb_to_uint32(0, 0, 0, 0, scene);
	while (temp)
	{
		object = (t_object *)temp->content;
		if (intersection(object, ray, &temp_hit))
		{
			if (!closest_obj || equal_points(get_nearest_point(temp_hit, closest_hit, ray.origin), temp_hit))
			{
				closest_hit = temp_hit;
				closest_obj = object;
				color = rgb_to_uint32(closest_obj->color.r,
					closest_obj->color.g, closest_obj->color.b, apply_light(scene, temp_hit, object), scene);
			}
		}
		temp = temp->next;
	}
	return (color);
}
