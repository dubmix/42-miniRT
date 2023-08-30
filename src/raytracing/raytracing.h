/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 09:49:28 by aehrlich          #+#    #+#             */
/*   Updated: 2023/08/30 10:12:11 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

typedef enum e_solution_type
{
	ONE,
	TWO,
	NONE,
}			t_solution_type;

typedef struct s_result
{
	t_solution_type	solution_type;
	float			t1;
	float			t2;
}			t_result;

t_point	init_point(float x, float y, float z);
t_vector	init_vector(float x, float y, float z);
t_vector	init_vector_p(t_point p1, t_point p2);
void	print_vector(t_vector v, char *name);
void	print_point(t_point p, char *name);
t_vector	scale_vec(t_vector v, float s);
float	dot_product(t_vector v1, t_vector v2);
float	dot_self(t_vector v1);
t_vector	add_vectors(t_vector v1, t_vector v2);
t_vector	subtract_vectors(t_vector v1, t_vector v2);
t_vector	subtract_points(t_point p1, t_point p2);
float		vector_length(t_vector v);
t_point	get_nearest_ray_point(t_result result, t_ray ray);
t_point	get_nearest_point(t_point p1, t_point p2, t_point compare);
t_point	get_ray_point(float t, t_ray r);
t_result	solve_quadratic(float a, float b, float c);

t_point	*sphere_intersect(t_sphere s, t_ray r, t_point *p);
t_point	*plane_intersect(t_plane p, t_ray r, t_point *point);
t_point	*cylinder_intersect(t_cylinder cyl, t_ray r, t_point *p);

t_vector	p_to_origin_vec(t_point p);
t_point	origin_vec_to_p(t_vector v);
t_point	add_points(t_point p1, t_point p2);
