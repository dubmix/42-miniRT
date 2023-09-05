/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 08:49:13 by aehrlich          #+#    #+#             */
/*   Updated: 2023/09/05 10:15:06 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

#include "miniRT.h"

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;


typedef struct 	s_point
{
	float		x;
	float		y;
	float		z;
}				t_point;

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

typedef struct 	s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vector;

typedef struct 	s_color
{
	uint32_t r;
	uint32_t g;
	uint32_t b;
}				t_color;

typedef struct 	s_ambient
{
	float		ratio;
	t_color		color;
	int			set;
}				t_ambient;

typedef struct 	s_camera
{
	t_point		coordinates;
	t_vector	orientation;
	int			field_of_view;
	int			set;
	float		transformation_matrix[3][3];
}				t_camera;

typedef struct 	s_light
{
	t_point		coordinates;
	float		brightness_ratio;
	int			set;
}				t_light;

typedef struct 	s_ray
{
	t_point		origin;
	t_vector	direction;		
}				t_ray;

typedef struct 	s_plane
{
	t_point		plane_point;
	t_vector	normal_vector;
}				t_plane;

typedef struct 	s_sphere
{
	t_point		center;
	float		diameter;
}				t_sphere;

typedef struct 	s_cylinder
{
	t_point		center;
	t_vector	axis;
	float		diameter;
	float		height;
}				t_cylinder;

typedef struct 	s_texture
{
	t_color	*color;
	int		set;
	int		width;
	int		height;		
}				t_texture;

typedef struct 	s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_list		*objects;
	mlx_t		*mlx;
	mlx_texture_t *tx;
	t_texture	texture;
}				t_scene;

typedef enum e_body_type
{
	SPHERE,
	PLANE,
	CYLINDER
}t_body_type;

typedef union body
{
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	t_plane		*plane;
}t_body;

typedef struct s_object
{
	t_body_type		body_type;
	t_body			body;
	t_color			color;
	t_vector		surface_normal;
}			t_object;
#endif
