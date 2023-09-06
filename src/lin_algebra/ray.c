/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:57:29 by aehrlich          #+#    #+#             */
/*   Updated: 2023/09/06 07:40:08 by aehrlich         ###   ########.fr       */
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
	if (result.solution_type == ONE)
		return (get_ray_point(result.t[0], ray));
	return (get_nearest_point(
			get_ray_point(result.t[0], ray),
			get_ray_point(result.t[1], ray), ray.origin));
}

/* 
	Return nearest Point to camera origin
 */
t_point	get_nearest_point(t_point p1, t_point p2, t_point compare)
{
	float	distance1;
	float	distance2;

	distance1 = vector_length(subtract_points(p1, compare));
	distance2 = vector_length(subtract_points(p2, compare));
	if (distance1 < distance2)
		return (p1);
	return (p2);
}
