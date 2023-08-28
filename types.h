/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 08:49:13 by aehrlich          #+#    #+#             */
/*   Updated: 2023/08/28 14:55:38 by aehrlich         ###   ########.fr       */
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
	t_color		color;
}				t_plane;

typedef struct 	s_sphere
{
	t_point		center;
	float		diameter;
	t_color		color;
}				t_sphere;

typedef struct 	s_cylinder
{
	t_point		center;
	t_vector	axis;
	float		diameter;
	float		height;
	t_color		color;
}				t_cylinder;

typedef struct 	s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_list		*planes;
	t_list		*spheres;
	t_list		*cylinders;
	mlx_t		*mlx;
}				t_scene;

#endif