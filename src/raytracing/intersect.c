/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 09:33:51 by aehrlich          #+#    #+#             */
/*   Updated: 2023/08/23 10:02:51 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"


void test(){
	t_ray		ray;
	t_sphere	sphere;

	init_point(&ray.origin, 0, 0, 0);
	init_vector(&ray.direction, 1, 1, 1);
	init_point(&sphere.center, 2, 2, 2);
	sphere.diameter = 2;
}