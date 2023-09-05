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

t_ray	create_ray(t_scene *scene, int pixel_x, int pixel_y)
{
	t_ray ray;
	
	ray.origin = scene->camera.coordinates;
	ray.direction = normalize(init_vector_p(pixel_to_coord(scene, pixel_x, pixel_y),
					scene->camera.coordinates));
	return (ray);
}

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
	while (temp)
	{
		object = (t_object *)temp->content;
		if (intersection(object, ray, &temp_hit))
		{
			if (!closest_obj || equal_points(get_nearest_point(temp_hit, closest_hit, ray.origin), temp_hit))
			{
				closest_hit = temp_hit;
				closest_obj = object;
				if (object->body_type == SPHERE && scene->texture.set == 1)
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