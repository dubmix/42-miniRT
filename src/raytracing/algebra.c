/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 09:47:57 by aehrlich          #+#    #+#             */
/*   Updated: 2023/09/05 10:02:22 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

t_point	init_point(float x, float y, float z)
{
	t_point	p;
	
	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

t_vector	init_vector(float x, float y, float z)
{
	t_vector	v;
	
	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vector	init_vector_p(t_point p1, t_point p2)
{
	t_vector	v;

	v.x = p1.x - p2.x;
	v.y = p1.y - p2.y;
	v.z = p1.z - p2.z;
	return (v);
}

t_vector	add_vectors(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vector	subtract_vectors(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_vector	subtract_points(t_point p1, t_point p2)
{
	t_vector	result;

	result.x = p1.x - p2.x;
	result.y = p1.y - p2.y;
	result.z = p1.z - p2.z;
	return (result);
}

t_point	add_points(t_point p1, t_point p2)
{
	t_point	result;

	result.x = p1.x + p2.x;
	result.y = p1.y + p2.y;
	result.z = p1.z + p2.z;
	return (result);
}
float	dot_product(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	cross_product(t_vector v1, t_vector v2)
{
	t_vector	res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
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

t_vector	p_to_origin_vec(t_point p)
{
	t_vector	v;
	v.x = p.x;
	v.y = p.y;
	v.z = p.z;
	return (v);
}

t_point	origin_vec_to_p(t_vector v)
{
	t_point	p;

	p.x = v.x;
	p.y = v.y;
	p.z = v.z;
	return (p);
}

bool	equal_points(t_point p1, t_point p2)
{
	return (p1.x == p2.x && p1.y == p2.y && p1.z == p2.z);
}
