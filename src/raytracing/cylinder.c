/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 09:33:51 by aehrlich          #+#    #+#             */
/*   Updated: 2023/09/01 16:39:35 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

t_point	*check_tube(t_object *obj, t_ray r, t_point *hp1, t_point *hp2)
{
	t_vector	x;
	t_vector	cap_center_vec;
	t_result	result;
	t_cylinder	cyl;
	float		m[2];
	
	cyl = *obj->body.cylinder;
	cap_center_vec = subtract_vectors(p_to_origin_vec(cyl.center), scale_vec(cyl.axis, cyl.height / 2));
	x = subtract_points(r.origin, origin_vec_to_p(cap_center_vec));
	result = solve_quadratic(dot_self(r.direction) - powf(dot_product(r.direction, cyl.axis), 2),
			2 * (dot_product(r.direction, x) - dot_product(r.direction, cyl.axis)*dot_product(x, cyl.axis)),
			dot_self(x) - powf(dot_product(x,cyl.axis), 2) - powf(cyl.diameter / 2, 2)
	);
	if (result.solution_type == NONE)
		return (NULL);
	m[0] = dot_product(r.direction, cyl.axis) * result.t1 + dot_product(x, cyl.axis);
	m[1] = dot_product(r.direction, cyl.axis) * result.t2 + dot_product(x, cyl.axis);
	if (m[0] >= 0 && m[0] < cyl.height)
		*hp1 = get_ray_point(result.t1, r);
	if (m[1] >= 0 && m[1] <= cyl.height)
		*hp2 = get_ray_point(result.t2, r);
	if (!(m[0] >= 0 && m[0] < cyl.height) && !(m[1] >= 0 && m[1] <= cyl.height))
		return (NULL);
	return (hp2);
}

t_point	*check_cap(t_ray r, t_point cap_center, t_cylinder cyl, t_point *hit_point)
{
	t_object	plane_obj;
	t_plane		cap_plane;
	t_point		intersection;
	t_vector	intersec_center;

	cap_plane.normal_vector = cyl.axis;
	cap_plane.plane_point = cap_center;
	plane_obj.body.plane = &cap_plane;
	if (plane_intersect(&plane_obj, r, &intersection))
	{
		intersec_center=  init_vector_p(cap_center, intersection);
		if (vector_length(intersec_center) <= cyl.diameter / 2)
		{
			*hit_point = intersection;
			return (hit_point);
		}
	}
	return (NULL);
}

int	check_caps(t_ray r, t_cylinder cyl, t_point *hp_1, t_point *hp_2)
{
	t_solution_type		intersections;
	t_vector			start_cap_center_vec;
	t_point				end_cap_center;
	t_point				*start_cap_result;
	t_point				*end_cap_result;

	start_cap_center_vec = subtract_vectors(p_to_origin_vec(cyl.center), scale_vec(cyl.axis, cyl.height / 2));
	end_cap_center = add_points(origin_vec_to_p(start_cap_center_vec), origin_vec_to_p(scale_vec(cyl.axis, cyl.height)));
	start_cap_result = check_cap(r, origin_vec_to_p(start_cap_center_vec), cyl, hp_1);
	end_cap_result = check_cap(r, end_cap_center, cyl, hp_2);
	if (start_cap_result && !end_cap_result)
		intersections = ONE;
	else if (!start_cap_result && end_cap_result)
	{
		*hp_1 = *hp_2;
		intersections = ONE;
	}
	else if (start_cap_result && end_cap_result)
		intersections = TWO;
	else
		intersections = NONE;
	return (intersections);
}

/* 
	If the ray lays on the tube surface, it is marked as no intersection.
 */
t_point	*cylinder_intersect(t_object *obj, t_ray r, t_point *p)
{
	int			cap_intersections;
	t_point		hit_point_1;
	t_point		hit_point_2;
	t_vector	cap_center_vec;
	
	obj->body.cylinder->axis = normalize(obj->body.cylinder->axis);
	r.direction = normalize(r.direction);
	cap_intersections = check_caps(r, *obj->body.cylinder, &hit_point_1, &hit_point_2);
	if (cap_intersections == TWO)
	{
		obj->surface_normal = normalize(obj->body.cylinder->axis);
		*p = get_nearest_point(hit_point_1, hit_point_2, r.origin);
	}
	else if (cap_intersections == ONE && check_tube(obj, r, &hit_point_2, &hit_point_2))
	{
		*p = get_nearest_point(hit_point_1, hit_point_2, r.origin);
		if (equal_points(hit_point_1, *p))
			obj->surface_normal = normalize(obj->body.cylinder->axis);
		else
			obj->surface_normal = normalize(obj->body.cylinder->axis);
	}
	else if (cap_intersections == NONE && check_tube(obj, r, &hit_point_1, &hit_point_2))
	{
		*p = get_nearest_point(hit_point_1, hit_point_2, r.origin);
		//calc surface normal
	}
	else
		p = NULL;
	return (p);
}

void test(t_scene *scene){
/* 	t_ray		ray;
	t_point		point;

	ray.origin = init_point(0, 5, 0);
	ray.direction = init_vector(0, 0, 1);
	if (plane_intersect(*((t_plane *)scene->planes->content), ray, &point))
		print_point(point, "Intersect");
	else
		printf("No intersection\n"); */
}