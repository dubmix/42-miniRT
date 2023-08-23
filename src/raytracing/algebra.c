/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 09:47:57 by aehrlich          #+#    #+#             */
/*   Updated: 2023/08/23 10:00:14 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

void init_point(t_point *p, int x, int y, int z)
{
	p->x = x;
	p->y = y;
	p->z = z;
}

void init_vector(t_vector *v, int x, int y, int z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

float	dot_product(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z + v2.z);
}
