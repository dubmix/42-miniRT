/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 09:33:51 by aehrlich          #+#    #+#             */
/*   Updated: 2023/08/28 11:55:00 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

void	intersect_cylinder(t_cylinder cyl, t_ray r, float *t1, float *t2)
{
	float		a;
	float		b;
	float		c;
	float		d;
	float		m1;
	float		m2;
	t_vector	x;
	t_vector	m_vec;
	t_point		cap_center;
	t_vector	cap_center_vec;
	
	init_vector(&m_vec, cyl.center.x, cyl.center.y, cyl.center.z);
	subtract_vectors(&cap_center_vec, m_vec, scale_vec(cyl.axis, cyl.height / 2));
	init_point(&cap_center, cap_center_vec.x, cap_center_vec.y, cap_center_vec.z);
	subtract_points(&x, r.origin, cap_center);
	a = dot_self(r.direction) - dot_product(r.direction, cyl.axis);
	b = 2 * (dot_product(r.direction, x) - dot_product(r.direction, cyl.axis)*dot_product(x, cyl.axis));
	c = dot_self(x) - powf(dot_product(x,cyl.axis), 2) - powf(cyl.diameter / 2, 2);

	d = b * b - (4 * a * c);
	if (d < 0)
		return;
	*t1 = (-b - sqrt(d)) / (2 * a);
	m1 = dot_product(r.direction, cyl.axis) * *t1 + dot_product(x, cyl.axis);
	if (d > 0)
	{
		*t2 = (-b + sqrt(d)) / (2 * a);
		m2 = dot_product(r.direction, cyl.axis) * *t2 + dot_product(x, cyl.axis);
	}
}

void	sphere_intersect(t_sphere s, t_ray r, float *t1, float *t2)
{
	float	a;
	float	b;
	float	c;
	float	d;
	t_vector	origin_center;

	init_vector_p(&origin_center, r.origin, s.center);
	a = dot_self(r.direction);
	b = 2 * dot_product(origin_center, r.direction);
	c = dot_self(origin_center) - (s.diameter/2 * s.diameter/2);
	d = b * b - (4 * a * c);
	if (d < 0)
		return;
	*t1 = (-b - sqrt(d)) / (2 * a);
	if (d > 0)
		*t2 = (-b + sqrt(d)) / (2 * a);
}

void	plane_intersect(t_plane p, t_ray r, float *t)
{
	int			a;
	int			b;
	t_point		scene_origin;
	t_vector	temp_p_vector;
	t_vector	temp_or_vector;

	init_point(&scene_origin, 0, 0 ,0);
	init_vector_p(&temp_p_vector, p.plane_point, scene_origin);
	init_vector_p(&temp_or_vector, r.origin, scene_origin);
	
	a = dot_product(p.normal_vector, r.direction);
	b = dot_product(p.normal_vector, temp_p_vector) - dot_product(p.normal_vector, temp_or_vector);
	if (a == 0 && b == 0)
		*t = 3.402823466e38;
	else if (a != 0)
		*t = b / a;
	else
		*t = 3.333;
}

void test(){
	t_ray		ray;
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;

	init_point(&ray.origin, 0, 0, 0);
	init_vector(&ray.direction, 0, 0, 1);
	
	init_point(&plane.plane_point, 0, 0, 3);
	init_vector(&plane.normal_vector, 0, 0, 1);
	
	init_point(&sphere.center, 0, 0, 3);
	sphere.diameter = 2.5;

	

	float t1 = -1;
	float t2 = -1;
	float t3 = -1;
	sphere_intersect(sphere, ray, &t1, &t2);
	if (t1 == -1 && t2 == -1)
		printf("No intersection\n");
	else if (t2 == -1)
		printf("one intersection\n");
	else
		printf("intersection at t1: %f and t2: %f\n", t1, t2);
	plane_intersect(plane, ray, &t3);
	printf("intersection at t: %f \n", t3);
}