/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lin_algebra.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 09:49:28 by aehrlich          #+#    #+#             */
/*   Updated: 2023/09/06 12:02:24 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIN_ALGEBRA_H
# define LIN_ALGEBRA_H

//#include "../../miniRT.h"
# include <math.h>
# include "../../types.h"

/*
*************
*	POINT	*
*************
*/
t_point		init_point(float x, float y, float z);
t_point		vec_to_p(t_vector v);
t_point		add_points(t_point p1, t_point p2);
t_point		get_nearest_ray_point(t_result result, t_ray ray);
t_point		get_nearest_point(t_point p1, t_point p2, t_point compare);
t_point		get_ray_point(float t, t_ray r);
bool		equal_points(t_point p1, t_point p2);

/*
*************
*	VECTOR	*
*************
*/
t_vector	init_vector(float x, float y, float z);
t_vector	init_vector_p(t_point p1, t_point p2);
t_vector	scale_vec(t_vector v, float s);
t_vector	normalize(t_vector v);
t_vector	p_to_origin_vec(t_point p);
t_vector	cross_product(t_vector v1, t_vector v2);
t_vector	add_vectors(t_vector v1, t_vector v2);
t_vector	subtract_vectors(t_vector v1, t_vector v2);
t_vector	subtract_points(t_point p1, t_point p2);
float		vector_length(t_vector v);
float		dot_product(t_vector v1, t_vector v2);
float		dot_self(t_vector v1);
bool		equal_vec(t_vector v1, t_vector v2);

#endif