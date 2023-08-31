/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:41:24 by aehrlich          #+#    #+#             */
/*   Updated: 2023/08/30 10:47:10 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/* 
	If the ray lays in the plane, it is marked as no intersection.
 */
t_point	*plane_intersect(t_plane p, t_ray r, t_point *point)
{
	t_vector	x;
	float		a;
	float		b;

	x = subtract_points(r.origin, p.plane_point);
	a = - (dot_product(x, p.normal_vector)); //should it be lenght 1???
	b = dot_product(r.direction, p.normal_vector);
	if (a == 0)
		return (NULL);
	*point = get_ray_point(a / b, r);
	return (point);
}
