/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:41:24 by aehrlich          #+#    #+#             */
/*   Updated: 2023/09/01 18:44:12 by aehrlich         ###   ########.fr       */
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

	obj->body.plane->normal_vector = normalize(obj->body.plane->normal_vector);
	obj->surface_normal = obj->body.plane->normal_vector; // does the direction matter? Light can be under plane
	x = subtract_points(r.origin, obj->body.plane->plane_point);
	a = -(dot_product(x, obj->body.plane->normal_vector)); //should it be lenght 1???
	b = dot_product(r.direction, obj->body.plane->normal_vector);
	if (b == 0 || (a / b) < 0) //must be handled if the camera goes in the other direction, then t can be negative!!!
		return (NULL);
	*point = get_ray_point(a / b, r);
	return (point);
}
