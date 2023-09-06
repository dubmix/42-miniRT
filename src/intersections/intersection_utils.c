/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:38:34 by aehrlich          #+#    #+#             */
/*   Updated: 2023/09/06 12:43:13 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

t_result	solve_quadratic(float a, float b, float c)
{
	float		d;
	t_result	res;

	d = b * b - (4 * a * c);
	if (a == 0 || d < 0)
		res.solution_type = NONE;
	else if (d == 0)
	{
		res.solution_type = ONE;
		res.t[0] = (-b + sqrt(d)) / (2 * a);
		res.t[1] = res.t[0];
		if (res.t[0] < 0)
			res.solution_type = NONE;
	}
	else
	{
		res.solution_type = TWO;
		res.t[0] = (-b - sqrt(d)) / (2 * a);
		res.t[1] = (-b + sqrt(d)) / (2 * a);
		if (res.t[0] < 0 || res.t[1] < 0)
			res.solution_type = NONE;
	}
	return (res);
}
