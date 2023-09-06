/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 09:33:51 by aehrlich          #+#    #+#             */
/*   Updated: 2023/09/06 12:43:10 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

static t_point	*set_cylinder(
	t_object *obj,
	t_point *p,
	t_point hitpoint,
	t_vector normal)
{
	*p = hitpoint;
	obj->surface_normal = normal;
	return (p);
}

/* 
	If the ray lays on the tube surface, it is marked as no intersection.
 */
t_point	*cylinder_intersect(t_object *obj, t_ray r, t_point *p)
{
	t_point		cap_hit_point;
	t_point		tube_hit_point;
	t_vector	cap_normal;
	t_vector	tube_normal;
	bool		intersection[2];

	obj->body.cylinder->axis = normalize(obj->body.cylinder->axis);
	CAP_INTERSECTION = check_caps(obj, r, &cap_hit_point, &cap_normal);
	TUBE_INTERSECTION = check_tube(obj, r, &tube_hit_point, &tube_normal);
	if (CAP_INTERSECTION && !TUBE_INTERSECTION)
		return (set_cylinder(obj, p, cap_hit_point, cap_normal));
	else if (CAP_INTERSECTION && TUBE_INTERSECTION)
	{
		*p = get_nearest_point(cap_hit_point, tube_hit_point, r.origin);
		if (equal_points(cap_hit_point, *p))
			return (set_cylinder(obj, p, cap_hit_point, cap_normal));
		else
			return (set_cylinder(obj, p, tube_hit_point, tube_normal));
	}
	else if (!CAP_INTERSECTION && TUBE_INTERSECTION)
		return (set_cylinder(obj, p, tube_hit_point, tube_normal));
	return (NULL);
}
