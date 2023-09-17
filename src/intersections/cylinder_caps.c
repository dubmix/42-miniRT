/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 08:19:20 by aehrlich          #+#    #+#             */
/*   Updated: 2023/09/17 10:23:12 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

static bool	check_cap(t_ray r,
t_point cap_center,
t_obj *obj,
t_point *p_hit)
{
	t_obj		plane_obj;
	t_plane		cap_plane;
	t_point		intersection;
	t_vector	intersec_center;
	t_cylinder	cyl;

	cyl = *obj->body.cylinder;
	cap_plane.plane_point = cap_center;
	plane_obj.body.plane = &cap_plane;
	plane_obj.body.plane->normal_vector = normalize(cyl.axis);
	if (plane_intersect(&plane_obj, r, &intersection))
	{
		intersec_center = init_vector_p(intersection, cap_center);
		if (vector_length(intersec_center) <= cyl.diameter / 2)
		{
			*p_hit = intersection;
			return (true);
		}
	}
	return (false);
}

static	void	init_cap_centers(
	t_obj *obj,
	t_vector *start_cap_center_vec,
	t_point *end_cap_center)
{
	t_cylinder	cyl;

	cyl = *obj->body.cylinder;
	*start_cap_center_vec = subtract_vectors(
			p_to_origin_vec(cyl.center),
			scale_vec(cyl.axis, cyl.height / 2));
	*end_cap_center = add_points(
			vec_to_p(*start_cap_center_vec),
			vec_to_p(scale_vec(cyl.axis, cyl.height)));
}

static bool	set_cap(
	t_vector *normal,
	t_point *p_hit,
	t_vector set_normal,
	t_point set_point)
{
	*normal = set_normal;
	*p_hit = set_point;
	return (true);
}

bool	check_caps(
	t_obj *obj,
	t_ray r,
	t_point *p_hit,
	t_vector *normal)
{
	t_vector	s_cap_center_vec;
	t_point		end_cap_center;
	t_point		s_cap_hit;
	t_point		e_cap_hit;
	bool		hit_results[2];

	init_cap_centers(obj, &s_cap_center_vec, &end_cap_center);
	hit_results[0] = check_cap(r, vec_to_p(s_cap_center_vec), obj, &s_cap_hit);
	hit_results[1] = check_cap(r, end_cap_center, obj, &e_cap_hit);
	if (hit_results[0] && !hit_results[1])
		return (set_cap(normal, p_hit,
				scale_vec(obj->body.cylinder->axis, -1), s_cap_hit));
	else if (!hit_results[0] && hit_results[1])
		return (set_cap(normal, p_hit, obj->body.cylinder->axis, e_cap_hit));
	else if (hit_results[0] && hit_results[1])
	{
		*p_hit = get_nearest_point(s_cap_hit, e_cap_hit, r.origin);
		if (equal_points(*p_hit, s_cap_hit))
			return (set_cap(normal, p_hit,
					scale_vec(obj->body.cylinder->axis, -1), s_cap_hit));
		else
			return (set_cap(normal,
					p_hit, obj->body.cylinder->axis, e_cap_hit));
	}
	return (false);
}
