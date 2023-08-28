/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 09:49:28 by aehrlich          #+#    #+#             */
/*   Updated: 2023/08/28 14:53:38 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

void	init_point(t_point *p, float x, float y, float z);
void	init_vector_p(t_vector *v, t_point p1, t_point p2);
void	init_vector(t_vector *v, float x, float y, float z);
t_vector	scale_vec(t_vector v, float s);
float	dot_product(t_vector v1, t_vector v2);
float	dot_self(t_vector v1);
void	add_vectors(t_vector *result, t_vector v1, t_vector v2);
void	subtract_vectors(t_vector *result, t_vector v1, t_vector v2);
void	subtract_points(t_vector *result, t_point p1, t_point p2);
