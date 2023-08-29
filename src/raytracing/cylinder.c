/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 09:33:51 by aehrlich          #+#    #+#             */
/*   Updated: 2023/08/29 18:51:40 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

t_result	verify_t_values(t_ray r, t_cylinder cyl, t_vector x, t_result t_values)
{
	float		m1;
	float		m2;

	m1 = dot_product(r.direction, cyl.axis) * t_values.t1 + dot_product(x, cyl.axis);
	m2 = dot_product(r.direction, cyl.axis) * t_values.t2 + dot_product(x, cyl.axis);

}
/* 
	If the ray lays in the tube, it is marked as no intersection.
 */
t_point	*cylinder_intersect(t_cylinder cyl, t_ray r, t_point *p)
{

	t_vector	x;
	t_vector	m_vec;
	t_point		cap_center;
	t_vector	cap_center_vec;
	t_result	result;
	
	init_vector(&m_vec, cyl.center.x, cyl.center.y, cyl.center.z);
	subtract_vectors(&cap_center_vec, m_vec, scale_vec(cyl.axis, cyl.height / 2));
	init_point(&cap_center, cap_center_vec.x, cap_center_vec.y, cap_center_vec.z);
	subtract_points(&x, r.origin, cap_center);
	result = solve_quadratic(dot_self(r.direction) - powf(dot_product(r.direction, cyl.axis), 2),
		2 * (dot_product(r.direction, x) - dot_product(r.direction, cyl.axis)*dot_product(x, cyl.axis)),
		dot_self(x) - powf(dot_product(x,cyl.axis), 2) - powf(cyl.diameter / 2, 2)
	);
	if (result.solution_type == NONE)
		return (NULL);
	printf("Intersection at: t1: %f and t2: %f\n", result.t1, result.t2);
	printf("m1: %f and m2: %f\n", m1, m2);
	return (NULL);
}

void test(t_scene *scene){
	t_ray		ray;
	t_point		point;

	init_point(&ray.origin, 0, 0, 0);
	init_vector(&ray.direction, 0, 0, 1);

	cylinder_intersect(*((t_cylinder *)scene->cylinders->content), ray, &point);
/* 
	if (plane_intersect(*((t_plane *)scene->planes->content), ray, &point))
	{
		print_point(point, "closest intersection");
	}
	else
	{
		 printf("No intersection\n");
	}
	if (t1 == -1 && t2 == -1)
		printf("No intersection\n");
	else if (t2 == -1)
		printf("one intersection\n");
	else
		printf("intersection at t1: %f and t2: %f\n", t1, t2); */
}