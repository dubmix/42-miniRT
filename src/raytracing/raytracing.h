/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 09:49:28 by aehrlich          #+#    #+#             */
/*   Updated: 2023/08/23 09:58:25 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../types.h"
#include "../../miniRT.h"

void	init_point(t_point *p, int x, int y, int z);
void	init_vector(t_vector *v, int x, int y, int z);
void	init_ray(t_ray *r, t_point origin, t_vector direction);
float	dot_product(t_vector v1, t_vector v2);