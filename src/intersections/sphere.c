/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:42:00 by aehrlich          #+#    #+#             */
/*   Updated: 2023/09/17 11:02:02 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

t_point	*sphere_intersect(t_obj *obj, t_ray r, t_point *p)
{
	t_vector	origin_center;
	t_result	result;

	origin_center = init_vector_p(r.origin, obj->body.sphere->center);
	result = solve_quadratic(dot_self(r.direction),
			2 * dot_product(origin_center, r.direction),
			dot_self(origin_center)
			- (obj->body.sphere->diameter / 2 * obj->body.sphere->diameter / 2)
			);
	if (result.solution_type == NONE)
		return (NULL);
	else
	{
		*p = get_nearest_ray_point(result, r);
		obj->surface_normal = normalize(
				subtract_points(*p, obj->body.sphere->center));
	}
	return (p);
}
