/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:53:32 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/17 10:16:08 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

int	make_even(int nb)
{
	if (nb % 2 == 1)
		return (nb - 1);
	else
		return (nb);
}

t_point	pixel_to_coord(t_scene *scene, int pixel_x, int pixel_y)
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

void	set_transformation(t_camera *camera)
{
	t_vector	temp;
	t_vector	right;
	t_vector	up;

	temp = init_vector(0, 1, 0);
	if (equal_vec(temp, camera->orientation)
		|| equal_vec(scale_vec(temp, -1), camera->orientation))
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

t_point	transform_point(t_camera c, t_point p)
{
	t_point	r;
	t_point	translate;

	translate = c.coordinates;
	r.x = p.x * c.m[0][0] + p.y * c.m[1][0] + p.z * c.m[2][0] + translate.x;
	r.y = p.x * c.m[0][1] + p.y * c.m[1][1] + p.z * c.m[2][1] + translate.y;
	r.z = p.x * c.m[0][2] + p.y * c.m[1][2] + p.z * c.m[2][2] + translate.z;
	return (r);
}
