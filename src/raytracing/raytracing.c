/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:59:42 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/06 15:01:00 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static t_point	pixel_to_coord(t_scene *scene, int pixel_x, int pixel_y)
{
	t_point	coord;
	float	fov_ratio;
	float	image_ratio;
	float	width;
	float	height;

	width = (float)scene->mlx->width;
	height = (float)scene->mlx->height;
	fov_ratio = tan(scene->camera.field_of_view / 2 * M_PI / 180);
	image_ratio = width / height;
	coord.x = (2 * ((pixel_x + 0.5) / width) - 1) * fov_ratio * image_ratio;
	coord.y = (1 - 2 * ((pixel_y + 0.5) / height)) * fov_ratio;
	coord.z = 1;
	return (coord);
}

static void	set_transformation(t_camera *camera)
{
	t_vector	temp;
	t_vector	right;
	t_vector	up;

	temp = init_vector(0, 1, 0);
	if (equal_vec(temp, camera->orientation) ||
		equal_vec(scale_vec(temp, -1), camera->orientation))
		temp = init_vector(0, 0, 1);
	right = normalize(cross_product(temp, camera->orientation));
	up = normalize(cross_product(camera->orientation, right));
	camera->m[0][0] = right.x;
	camera->m[0][1] = right.y;
	camera->m[0][2] = right.z;
	camera->m[1][0] = up.x;
	camera->m[1][1] = up.y;
	camera->m[1][2] = up.z;
	camera->m[2][0] = camera->orientation.x;
	camera->m[2][1] = camera->orientation.y;
	camera->m[2][2] = camera->orientation.z;
}

static t_point	transform_point(t_camera c, t_point p)
{
	t_point	r;
	t_point	translate;

	translate = c.coordinates;
	r.x = p.x * c.m[0][0] + p.y * c.m[1][0] + p.z * c.m[2][0] + translate.x;
	r.y = p.x * c.m[0][1] + p.y * c.m[1][1] + p.z * c.m[2][1] + translate.y;
	r.z = p.x * c.m[0][2] + p.y * c.m[1][2] + p.z * c.m[2][2] + translate.z;
	return (r);
}

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


uint32_t trace_ray(t_scene *scene, t_ray ray)
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

void	ft_render(t_scene *scene)
{
	uint32_t		color;
	t_ray			ray;
	unsigned int	pixel_x;
	unsigned int	pixel_y;

	pixel_x = 0;
	scene->camera.orientation = normalize(scene->camera.orientation);
	while (pixel_x < scene->img->width)
	{
		pixel_y = 0;
		while (pixel_y < scene->img->height)
		{
			ray = create_ray(scene, pixel_x, pixel_y);
			color = trace_ray(scene, ray);
			mlx_put_pixel(scene->img, pixel_x, pixel_y, color);
			pixel_y++;
		}
		pixel_x++;
	}
}
