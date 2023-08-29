/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:41:24 by aehrlich          #+#    #+#             */
/*   Updated: 2023/08/29 18:41:48 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/* 
	If the ray lays in the plane, it is marked as no intersection.
 */
t_point	*plane_intersect(t_plane p, t_ray r, t_point *point)
{
	int			a;
	int			b;
	t_point		scene_origin;
	t_vector	temp_p_vector;
	t_vector	temp_or_vector;

	init_point(&scene_origin, 0, 0 ,0);
	init_vector_p(&temp_p_vector, p.plane_point, scene_origin);
	init_vector_p(&temp_or_vector, r.origin, scene_origin);
	a = dot_product(p.normal_vector, r.direction);
	b = dot_product(p.normal_vector, temp_p_vector) - dot_product(p.normal_vector, temp_or_vector);
	if (a == 0)
		return (NULL);
	*point = get_ray_point(a / b, r);
	return (point);
}
