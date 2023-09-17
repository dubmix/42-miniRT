/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 09:33:51 by aehrlich          #+#    #+#             */
/*   Updated: 2023/09/17 10:32:26 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

static t_point	*set_cylinder(
	t_obj *obj,
	t_point *p,
	t_point hitpoint,
	t_vector normal)
{
	*p = hitpoint;
	obj->surface_normal = normalize(normal);
	return (p);
}

/* 
	If the ray lays on the tube surface, it is marked as no intersection.
 */
t_point	*cylinder_intersect(t_obj *obj, t_ray r, t_point *p)
{
	t_point		cap_hit_point;
	t_point		tube_hit_point;
	t_vector	cap_normal;
	t_vector	tube_normal;
	bool		intersections[2];

	obj->body.cylinder->axis = normalize(obj->body.cylinder->axis);
	intersections[0] = check_caps(obj, r, &cap_hit_point, &cap_normal);
	intersections[1] = check_tube(obj, r, &tube_hit_point, &tube_normal);
	if (intersections[0] && !intersections[1])
		return (set_cylinder(obj, p, cap_hit_point, cap_normal));
	else if (intersections[0] && intersections[1])
	{
		*p = get_nearest_point(cap_hit_point, tube_hit_point, r.origin);
		if (equal_points(cap_hit_point, *p))
			return (set_cylinder(obj, p, cap_hit_point, cap_normal));
		else
			return (set_cylinder(obj, p, tube_hit_point, tube_normal));
	}
	else if (!intersections[0] && intersections[1])
		return (set_cylinder(obj, p, tube_hit_point, tube_normal));
	return (NULL);
}
