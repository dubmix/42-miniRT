/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:41:24 by aehrlich          #+#    #+#             */
/*   Updated: 2023/09/17 09:34:54 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

/* 
	This function calculates - if there is one - the intersection between
	a ray and a plane. For lighting, the surface normal must point in direction
	of the light, so we have to check with the dot product that the normal vector
	from parsing does not go in the same direction as the ray. If so, we reverse it.
	If the ray lays in the plane, it is marked as no intersection.
 */
t_point	*plane_intersect(t_obj *obj, t_ray r, t_point *point)
{
	t_vector	x;
	float		a;
	float		b;

	obj->body.plane->normal_vector = normalize(obj->body.plane->normal_vector);
	if (dot_product(r.direction, obj->body.plane->normal_vector) > 0)
		obj->surface_normal = scale_vec(obj->body.plane->normal_vector, -1);
	else
		obj->surface_normal = obj->body.plane->normal_vector;
	x = subtract_points(r.origin, obj->body.plane->plane_point);
	a = -(dot_product(x, obj->body.plane->normal_vector));
	b = dot_product(r.direction, obj->body.plane->normal_vector);
	if ((a / b) < 0 || b == 0)
		return (NULL);
	*point = get_ray_point(a / b, r);
	return (point);
}
