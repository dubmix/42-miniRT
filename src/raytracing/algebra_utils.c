/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:29:06 by aehrlich          #+#    #+#             */
/*   Updated: 2023/08/30 07:18:29 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

void	print_vector(t_vector v, char *name)
{
	printf("Vektor: %s:\n", name);
	printf("x: %f | y: %f | z: %f\n", v.x, v.y, v.z);
}

void	print_point(t_point p, char *name)
{
	printf("Point: %s:\n", name);
	printf("x: %f | y: %f | z: %f\n", p.x, p.y, p.z);
}
