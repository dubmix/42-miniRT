/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:59:42 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/05 11:33:44 by aehrlich         ###   ########.fr       */
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

t_point	pixel_to_coord(t_scene *scene, int pixel_x, int pixel_y)
{
	t_point coord;
	float imageAspectRatio = (float)scene->mlx->width / (float)scene->mlx->height; // assuming width > height, test the other case
	float Px = (2 * ((pixel_x + 0.5) / (float)scene->mlx->width ) - 1) * tan(scene->camera.field_of_view / 2 * M_PI / 180) * imageAspectRatio;
	float Py = (1 - 2 * ((pixel_y + 0.5) / (float)scene->mlx->height)) * tan(scene->camera.field_of_view / 2 * M_PI / 180);
	coord.x = Px;
	coord.y = Py;
	coord.z = 1;
	
	return (coord);
}

void	set_transformation(t_camera *camera)
{
	t_vector	temp;
	t_vector	right;
	t_vector	up;

	temp = init_vector(0, 1, 0);
	right = normalize(cross_product(temp, camera->orientation));
	up = normalize(cross_product(camera->orientation, right));

	camera->transformation_matrix[0][0] = right.x;
	camera->transformation_matrix[0][1] = right.y;
	camera->transformation_matrix[0][2] = right.z;
	camera->transformation_matrix[1][0] = up.x;
	camera->transformation_matrix[1][1] = up.y;
	camera->transformation_matrix[1][2] = up.z;
	camera->transformation_matrix[2][0] = camera->orientation.x;
	camera->transformation_matrix[2][1] = camera->orientation.y;
	camera->transformation_matrix[2][2] = camera->orientation.z;
}

t_point	transform_point(t_camera c, t_point p)
{
	t_point res;

	res.x = p.x * c.transformation_matrix[0][0] + p.y * c.transformation_matrix[1][0] + p.z * c.transformation_matrix[2][0] + c.coordinates.x;
	res.y = p.x * c.transformation_matrix[0][1] + p.y * c.transformation_matrix[1][1] + p.z * c.transformation_matrix[2][1] + c.coordinates.y;
	res.z = p.x * c.transformation_matrix[0][2] + p.y * c.transformation_matrix[1][2] + p.z * c.transformation_matrix[2][2] + c.coordinates.z;
	return (res);
}

t_ray	create_ray(t_scene *scene, int pixel_x, int pixel_y)
{
	t_ray	ray;
	t_point	local_pixel_point;
	t_point	transformed_pixel_point;

	set_transformation(&scene->camera);
	local_pixel_point = pixel_to_coord(scene, pixel_x, pixel_y);
	transformed_pixel_point = transform_point(scene->camera, local_pixel_point);
	ray.origin = scene->camera.coordinates;
	ray.direction = normalize(init_vector_p(transformed_pixel_point, scene->camera.coordinates));
	return (ray);
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