/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:39:48 by aehrlich          #+#    #+#             */
/*   Updated: 2023/09/06 12:03:28 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

# include "../lin_algebra/lin_algebra.h"

# define CAP_INTERSECTION intersection[0]
# define TUBE_INTERSECTION intersection[1]
# define TOP_CAP_HIT cap_hit_results[0]
# define BOTTOM_CAP_HIT cap_hit_results[1]

t_result	solve_quadratic(float a, float b, float c);
/*
*************
*	SPHERE	*
*************
*/
t_point	*sphere_intersect(t_object *obj, t_ray r, t_point *p);

/*
*************
*	PLANE	*
*************
*/
t_point	*plane_intersect(t_object *obj, t_ray r, t_point *point);

/*
*****************
*	CYLINDER	*
*****************
*/
t_point	*cylinder_intersect(t_object *obj, t_ray r, t_point *p);
bool	check_tube(t_object *obj, t_ray r, t_point *hit_point, t_vector *tube_normal);
bool	check_caps(t_object *obj, t_ray r, t_point *cap_hit_point, t_vector *cap_normal);

#endif