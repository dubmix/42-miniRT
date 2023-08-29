/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 09:47:57 by aehrlich          #+#    #+#             */
/*   Updated: 2023/08/29 16:27:39 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

void	init_point(t_point *p, float x, float y, float z)
{
	p->x = x;
	p->y = y;
	p->z = z;
}

void	init_vector(t_vector *v, float x, float y, float z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

void	init_vector_p(t_vector *v, t_point p1, t_point p2)
{
	v->x = p1.x - p2.x;
	v->y = p1.y - p2.y;
	v->z = p1.z - p2.z;
}

void	add_vectors(t_vector *result, t_vector v1, t_vector v2)
{
	result->x = v1.x + v2.x;
	result->y = v1.y + v2.y;
	result->z = v1.z + v2.z;
}

void	subtract_vectors(t_vector *result, t_vector v1, t_vector v2)
{
	result->x = v1.x - v2.x;
	result->y = v1.y - v2.y;
	result->z = v1.z - v2.z;
}

void	subtract_points(t_vector *result, t_point p1, t_point p2)
{
	result->x = p1.x - p2.x;
	result->y = p1.y - p2.y;
	result->z = p1.z - p2.z;
}

float	dot_product(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float	dot_self(t_vector v1)
{
	return (v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
}

t_vector	scale_vec(t_vector v, float s)
{
	v.x = v.x * s;
	v.y = v.y * s;
	v.z = v.z * s;
	return (v);
}

float		vector_length(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector	normalize(t_vector v)
{
	t_vector	norm;
	float		len;

	len = vector_length(v);
	norm.x = v.x / len;
	norm.y = v.y / len;
	norm.z = v.z / len;
	return (norm);
}
