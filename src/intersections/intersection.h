/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:39:48 by aehrlich          #+#    #+#             */
/*   Updated: 2023/09/17 09:34:54 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

# include "../lin_algebra/lin_algebra.h"

t_result	solve_quadratic(float a, float b, float c);
/*
*************
*	SPHERE	*
*************
*/
t_point		*sphere_intersect(t_obj *obj, t_ray r, t_point *p);

/*
*************
*	PLANE	*
*************
*/
t_point		*plane_intersect(t_obj *obj, t_ray r, t_point *point);

/*
*****************
*	CYLINDER	*
*****************
*/
t_point		*cylinder_intersect(t_obj *obj, t_ray r, t_point *p);
bool		check_tube(t_obj *obj,
				t_ray r, t_point *hit_point, t_vector *tube_normal);
bool		check_caps(t_obj *obj,
				t_ray r, t_point *cap_hit_point, t_vector *cap_normal);
#endif