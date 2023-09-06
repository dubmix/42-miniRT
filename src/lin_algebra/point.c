/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:38:44 by aehrlich          #+#    #+#             */
/*   Updated: 2023/09/06 11:30:02 by aehrlich         ###   ########.fr       */
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

t_point	vec_to_p(t_vector v)
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
