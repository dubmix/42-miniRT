/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:36:27 by aehrlich          #+#    #+#             */
/*   Updated: 2023/09/06 12:38:53 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lin_algebra.h"

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

float	vector_length(t_vector v)
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

bool	equal_vec(t_vector v1, t_vector v2)
{
	return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}
