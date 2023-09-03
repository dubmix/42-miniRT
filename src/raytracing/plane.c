/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:41:24 by aehrlich          #+#    #+#             */
/*   Updated: 2023/09/03 15:24:03 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/* 
	If the ray lays in the plane, it is marked as no intersection.
 */
t_point	*plane_intersect(t_object *obj, t_ray r, t_point *point)
{
	t_vector	x;
	float		a;
	float		b;

	obj->body.plane->normal_vector = obj->body.plane->normal_vector;
	obj->surface_normal = scale_vec(obj->body.plane->normal_vector, -1); // does the direction matter? Light can be under plane
	x = subtract_points(r.origin, obj->body.plane->plane_point);
	a = -(dot_product(x, obj->body.plane->normal_vector));
	b = dot_product(r.direction, obj->body.plane->normal_vector);
	if (b == 0 || (a / b) < 0)
		return (NULL);
	*point = get_ray_point(a / b, r);
	return (point);
}
