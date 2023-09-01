/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:57:29 by aehrlich          #+#    #+#             */
/*   Updated: 2023/09/02 01:25:04 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

t_point	get_ray_point(float t, t_ray r)
{
	t_point	point;

	point.x = r.origin.x + t * r.direction.x;
	point.y = r.origin.y + t * r.direction.y;
	point.z = r.origin.z + t * r.direction.z;
	return (point);
}

t_point	get_nearest_ray_point(t_result result, t_ray ray)
{
	t_point		hit_point_1;
	t_point		hit_point_2;
	float		distance_1;
	float		distance_2;

	if (result.solution_type == ONE)
		return get_ray_point(result.t1, ray);
	{
		hit_point_1 = get_ray_point(result.t1, ray);
		hit_point_2 = get_ray_point(result.t2, ray);
		distance_1 = vector_length(subtract_points(hit_point_1, ray.origin));
		distance_2 = vector_length(subtract_points(hit_point_2, ray.origin));
	}
	if (distance_1 < distance_2)
		return (hit_point_1);
	return (hit_point_2);
}

/* 
	Return nearest Point to camera origin
 */
t_point	get_nearest_point(t_point p1, t_point p2, t_point compare)
{
	float	distance1 = vector_length(subtract_points(p1, compare));
	float	distance2 = vector_length(subtract_points(p2, compare));
	if (distance1 < distance2)
		return (p1);
	return (p2);
}