/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_tube.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 08:20:24 by aehrlich          #+#    #+#             */
/*   Updated: 2023/09/17 09:34:54 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

static t_result	solve_infinite_tube(t_cylinder cyl, t_ray r, t_vector x)
{
	float	a;
	float	b;
	float	c;

	a = dot_self(r.direction) - powf(dot_product(r.direction, cyl.axis), 2);
	b = 2 * (dot_product(r.direction, x)
			- dot_product(r.direction, cyl.axis) * dot_product(x, cyl.axis));
	c = dot_self(x) - powf(dot_product(x, cyl.axis), 2)
		- powf(cyl.diameter / 2, 2);
	return (solve_quadratic(a, b, c));
}

static int	get_hitpoint_res(
	t_cylinder cyl,
	t_ray r,
	t_result result,
	t_vector x)
{
	float	m1;
	float	m2;

	if (result.solution_type == NONE)
		return (-1);
	m1 = dot_product(r.direction, cyl.axis) * result.t[0]
		+ dot_product(x, cyl.axis);
	m2 = dot_product(r.direction, cyl.axis) * result.t[1]
		+ dot_product(x, cyl.axis);
	if ((m1 >= 0 && m1 < cyl.height) && !(m2 >= 0 && m2 <= cyl.height))
		return (0);
	else if (!(m1 >= 0 && m1 < cyl.height) && (m2 >= 0 && m2 <= cyl.height))
		return (1);
	else if ((m1 >= 0 && m1 < cyl.height) && (m2 >= 0 && m2 <= cyl.height))
		return (2);
	else
		return (-1);
}

static t_vector	get_tube_normal(
	t_point hit_point,
	t_vector cap_center,
	t_cylinder cyl,
	float m)
{
	t_vector	res;

	res = subtract_vectors(
			subtract_points(hit_point, vec_to_p(cap_center)),
			scale_vec(cyl.axis, m));
	res = normalize(res);
	return (res);
}

static bool	set_tube_hitpoint(
	int *result_idx,
	t_point *hit_point,
	t_result result,
	t_ray r)
{
	t_point	temp_hit_1;
	t_point	temp_hit_2;

	if (*result_idx == -1)
		return (false);
	if (*result_idx < 2)
		*hit_point = get_ray_point(result.t[*result_idx], r);
	if (*result_idx == 2)
	{
		temp_hit_1 = get_ray_point(result.t[0], r);
		temp_hit_2 = get_ray_point(result.t[1], r);
		*hit_point = get_nearest_point(temp_hit_1, temp_hit_2, r.origin);
		if (equal_points(temp_hit_1, *hit_point))
			*result_idx = 0;
		else
			*result_idx = 1;
	}
	return (true);
}

bool	check_tube(
	t_obj *obj,
	t_ray r,
	t_point *hit_point,
	t_vector *tube_normal)
{
	t_vector	cap_center_vec;
	t_vector	x;
	t_result	res;
	int			result_idx;
	float		m;

	cap_center_vec = subtract_vectors(
			p_to_origin_vec((*obj->body.cylinder).center),
			scale_vec((*obj->body.cylinder).axis,
				(*obj->body.cylinder).height / 2));
	x = subtract_points(r.origin, vec_to_p(cap_center_vec));
	res = solve_infinite_tube(*obj->body.cylinder, r, x);
	result_idx = get_hitpoint_res(*obj->body.cylinder, r, res, x);
	if (!set_tube_hitpoint(&result_idx, hit_point, res, r))
		return (false);
	m = dot_product(r.direction,
			(*obj->body.cylinder).axis) * res.t[result_idx]
		+ dot_product(x, (*obj->body.cylinder).axis);
	*tube_normal = get_tube_normal(*hit_point, cap_center_vec,
			*obj->body.cylinder, m);
	return (true);
}
