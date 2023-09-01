/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 09:33:51 by aehrlich          #+#    #+#             */
/*   Updated: 2023/09/01 19:06:16 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

bool	check_tube(t_object *obj, t_ray r, t_point *hit_point, t_vector *tube_normal)
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
		return (false);
	m[0] = dot_product(r.direction, cyl.axis) * result.t1 + dot_product(x, cyl.axis);
	m[1] = dot_product(r.direction, cyl.axis) * result.t2 + dot_product(x, cyl.axis);
	if ((m[0] >= 0 && m[0] < cyl.height) && !(m[1] >= 0 && m[1] <= cyl.height))
	{
		*hit_point = get_ray_point(result.t1, r);
		*tube_normal = normalize(subtract_vectors(subtract_points(*hit_point, origin_vec_to_p( cap_center_vec)), scale_vec(obj->body.cylinder->axis, m[0])));
	}
	else if (!(m[0] >= 0 && m[0] < cyl.height) && (m[1] >= 0 && m[1] <= cyl.height))
	{
		*hit_point = get_ray_point(result.t2, r);
		*tube_normal = normalize(subtract_vectors(subtract_points(*hit_point, origin_vec_to_p( cap_center_vec)), scale_vec(obj->body.cylinder->axis, m[1])));
	}
	else if ((m[0] >= 0 && m[0] < cyl.height) && (m[1] >= 0 && m[1] <= cyl.height))
	{
		*hit_point = get_nearest_point(get_ray_point(result.t1, r), get_ray_point(result.t2, r), r.origin);
		if (equal_points(*hit_point, get_ray_point(result.t1, r)))
			*tube_normal = normalize(subtract_vectors(subtract_points(*hit_point, origin_vec_to_p( cap_center_vec)), scale_vec(obj->body.cylinder->axis, m[0])));
		else
			*tube_normal = normalize(subtract_vectors(subtract_points(*hit_point, origin_vec_to_p( cap_center_vec)), scale_vec(obj->body.cylinder->axis, m[1])));
	}
	else
		return (false);
	return (true);
}

bool	check_cap(t_ray r, t_point cap_center, t_cylinder cyl, t_point *hit_point)
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
		intersec_center =  init_vector_p(cap_center, intersection);
		if (vector_length(intersec_center) <= cyl.diameter / 2)
		{
			*hit_point = intersection;
			return (true);
		}
	}
	return (false);
}

bool	check_caps(t_object *obj, t_ray r, t_point *cap_hit_point, t_vector *cap_normal)
{
	t_vector	start_cap_center_vec;
	t_point		end_cap_center;
	t_point		start_cap_hit;
	t_point		end_cap_hit;
	bool		cap_hit_results[2];

	start_cap_center_vec = subtract_vectors(p_to_origin_vec(obj->body.cylinder->center), scale_vec(obj->body.cylinder->axis, obj->body.cylinder->height / 2));
	end_cap_center = add_points(origin_vec_to_p(start_cap_center_vec), origin_vec_to_p(scale_vec(obj->body.cylinder->axis, obj->body.cylinder->height)));
	cap_hit_results[0] = check_cap(r, origin_vec_to_p(start_cap_center_vec), *obj->body.cylinder, &start_cap_hit);
	cap_hit_results[1]= check_cap(r, end_cap_center, *obj->body.cylinder, &end_cap_hit);
	if (cap_hit_results[0] && !cap_hit_results[1])
	{
		*cap_normal = scale_vec(obj->body.cylinder->axis, -1);
		*cap_hit_point = start_cap_hit;
	}
	else if (!cap_hit_results[0] && cap_hit_results[1])
	{
		*cap_normal = obj->body.cylinder->axis;
		*cap_hit_point = end_cap_hit;
	}
	else if (cap_hit_results[0] && cap_hit_results[1])
	{
		*cap_hit_point = get_nearest_point(start_cap_hit, end_cap_hit, r.origin);
		if (equal_points(*cap_hit_point, start_cap_hit))
			*cap_normal = scale_vec(obj->body.cylinder->axis, -1);
		else
			*cap_normal = obj->body.cylinder->axis;
	}
	else
		return (false);
	return (true);
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
	bool		cap_intersection;
	bool		tube_intersection;
	
	obj->body.cylinder->axis = normalize(obj->body.cylinder->axis); //move to init function
	r.direction = normalize(r.direction); //in init verscheiben!
	cap_intersection = check_caps(obj, r, &cap_hit_point, &cap_normal);
	tube_intersection = check_tube(obj, r, &tube_hit_point, &tube_normal);
	if (cap_intersection && !tube_intersection)
	{
		*p = cap_hit_point;
		obj->surface_normal = cap_normal;
	}
	else if (cap_intersection && tube_intersection)
	{
		*p = get_nearest_point(cap_hit_point, tube_hit_point, r.origin);
		if (equal_points(cap_hit_point, *p))
			obj->surface_normal = cap_normal;
		else
			obj->surface_normal = tube_normal;
	}
	else if (!cap_intersection && tube_intersection)
	{
		*p = tube_hit_point;
		obj->surface_normal = tube_normal;
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