/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 09:33:51 by aehrlich          #+#    #+#             */
/*   Updated: 2023/08/23 13:53:38 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

void	sphere_intersect(t_sphere s, t_ray r, float *t1, float *t2)
{
	float	a;
	float	b;
	float	c;
	float	d;
	t_vector	origin_center;

	init_vector(&origin_center, -s.center.x, -s.center.y, -s.center.z);
	a = dot_product(r.direction, r.direction);
	b = 2 * dot_product(origin_center, r.direction);
	c = dot_product(origin_center, origin_center) - (s.diameter/2 * s.diameter/2);
	d = b * b - (4 * a * c);
	if (d < 0)
		return;
	*t1 = (-b - sqrt(d)) / (2 * a);
	if (d > 0)
		*t2 = (-b + sqrt(d)) / (2 * a);
}

void test(){
	t_ray		ray;
	t_sphere	sphere;

	init_point(&ray.origin, 0, 0, 0);
	init_vector(&ray.direction, 1, 1, 1);
	init_point(&sphere.center, 2, 2, 2);
	sphere.diameter = 2;

	float t1 = -1;
	float t2 = -1;
	sphere_intersect(sphere, ray, &t1, &t2);
	if (t1 == -1 && t2 == -1)
		printf("No intersection\n");
	else if (t2 == -1)
		printf("one intersection\n");
	else
		printf("intersection at t1: %f and t2: %f\n", t1, t2);
}