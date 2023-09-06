/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 09:47:57 by aehrlich          #+#    #+#             */
/*   Updated: 2023/09/06 12:39:08 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lin_algebra.h"

t_vector	scale_vec(t_vector v, float s)
{
	v.x = v.x * s;
	v.y = v.y * s;
	v.z = v.z * s;
	return (v);
}

t_vector	p_to_origin_vec(t_point p)
{
	t_vector	v;

	v.x = p.x;
	v.y = p.y;
	v.z = p.z;
	return (v);
}
