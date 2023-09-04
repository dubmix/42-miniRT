/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:38:34 by aehrlich          #+#    #+#             */
/*   Updated: 2023/09/04 08:11:26 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

t_result	solve_quadratic(float a, float b, float c)
{
	float		d;
	t_result	res;

	d = b * b - (4 * a * c);
	if (a == 0 || d < 0)
	{
		res.solution_type = NONE;
		return (res);
	}
	else if (d == 0)
	{
		res.solution_type = ONE;
		res.t1 = (-b + sqrt(d)) / (2 * a);
		res.t2 = res.t1;
		if (res.t1 < 0)
			res.solution_type = NONE;
	}
	else
	{
		res.solution_type = TWO;
		res.t1 = (-b - sqrt(d)) / (2 * a);
		res.t2 = (-b + sqrt(d)) / (2 * a);
		if (res.t1 < 0 || res.t2 < 0)
			res.solution_type = NONE;
	}
	return (res);
}