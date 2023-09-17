/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:59:42 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/17 10:15:06 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

t_ray	create_ray(t_scene *scene, int pixel_x, int pixel_y)
{
	t_ray	ray;
	t_point	local_point;
	t_point	transformed;

	set_transformation(&scene->camera);
	local_point = pixel_to_coord(scene, pixel_x, pixel_y);
	transformed = transform_point(scene->camera, local_point);
	ray.origin = scene->camera.coordinates;
	ray.direction = init_vector_p(transformed, scene->camera.coordinates);
	ray.direction = normalize(ray.direction);
	return (ray);
}

t_point	*intersection(t_obj	*obj, t_ray ray, t_point *temp_hit)
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

/* 
	This function gets a ray with direction from camera through a pixel
	and checks for intersection with the objects. It determines the
	intersection with the closest object and calculates the 
	color taking care if the light situation.
	@arguments:	s:		scene
				ray:	ray from camera throug hcurrent pixel
				c:		color in form of int to set accordingly
	@variables:	t:		temp node of the list to iterate over
				th:		Temporary hit with the curent object
				ch:		Closet hit. Gets replaced by the
						temporary hit, if it is closer
						than the old closest hit
				co:		Closest object the ray hit, used
						to get color information
 */

void	trace_ray(t_scene *s, t_ray ray, uint32_t *c)
{
	t_list		*t;
	t_point		th;
	t_point		ch;
	t_obj		*co;

	t = s->objects;
	co = NULL;
	while (t)
	{
		if (intersection((t_obj *)t->cont, ray, &th))
		{
			if (!co || equal_points(get_nearest_point(th, ch, ray.origin), th))
			{
				ch = th;
				co = (t_obj *)t->cont;
				if (((t_obj *)t->cont)->body_type == SPHERE
					&& ((t_obj *)t->cont)->texture.set == 1)
					*c = c_int(sp_tx(ch, ((t_obj *)t->cont)),
							light(s, th, ((t_obj *)t->cont)), s);
				else
					*c = c_int(co->color, light(s, th, ((t_obj *)t->cont)), s);
			}
		}
		t = t->next;
	}
}

void	ft_render(t_scene *scene)
{
	uint32_t		color;
	unsigned int	pixel_x;
	unsigned int	pixel_y;
	bool			cam_in_object;

	pixel_x = 0;
	scene->camera.orientation = normalize(scene->camera.orientation);
	cam_in_object = camera_is_in_object(scene);
	while (pixel_x < scene->img->width)
	{
		pixel_y = 0;
		while (pixel_y < scene->img->height)
		{
			color = 255;
			if (!cam_in_object)
				trace_ray(scene,
					create_ray(scene, pixel_x, pixel_y), &color);
			mlx_put_pixel(scene->img, pixel_x, pixel_y, color);
			pixel_y++;
		}
		pixel_x++;
	}
}
