/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:57:29 by aehrlich          #+#    #+#             */
/*   Updated: 2023/08/29 17:21:59 by aehrlich         ###   ########.fr       */
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

t_point	get_nearest_point(t_result result, t_ray ray)
{
	t_point		hit_point_1;
	t_point		hit_point_2;
	t_vector	temp_vec;
	float		distance_1;
	float		distance_2;

	if (result.solution_type == ONE)
		return get_ray_point(result.t1, ray);
	{
		hit_point_1 = get_ray_point(result.t1, ray);
		hit_point_2 = get_ray_point(result.t2, ray);
		init_vector_p(&temp_vec, hit_point_1, ray.origin);
		distance_1 = vector_length(temp_vec);
		init_vector_p(&temp_vec, hit_point_2, ray.origin);
		distance_2 = vector_length(temp_vec);
	}
	if (distance_1 < distance_2)
		return (hit_point_1);
	return (hit_point_2);
}