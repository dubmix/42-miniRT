/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:54:22 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/17 11:20:49 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

int	apply_shadow(t_point hit_point, t_obj *object, t_scene *scene)
{
	t_ray	ray;
	t_obj	*temp_obj;
	t_list	*temp_node;
	t_point	light_intersection;

	ray.origin = hit_point;
	ray.direction = normalize(subtract_points(scene->light.coordinates,
				hit_point));
	temp_node = scene->objects;
	while (temp_node)
	{
		temp_obj = (t_obj *)temp_node->cont;
		if (temp_obj != object
			&& intersection(temp_obj, ray, &light_intersection)
			&& equal_points(get_nearest_point(light_intersection,
					scene->light.coordinates,
					hit_point), light_intersection))
			return (1);
		temp_node = temp_node->next;
	}
	return (0);
}

/* 
	This function applies shadow, diffuse light and shinyness to a pixle
	if neccessary. Thefore the formula is taken from here:
	https://gabrielgambetta.com/computer-graphics-from-scratch/03-light.html
	@arguments:	scene:		The scene to render
				hit_point:	Point where the primary rat hits the closest object
				object:		The closest object hit by the primary ray
	@variables:	i:			Coefficent applied to the 
							components of the color
				n:			Surface normal of the hit object
				l:			direction of secondary ray from hitpoint to light
				v:			direction of primary ray from cam to hitpoint
				r:			direction of the specular reflected light
 */
float	light(t_scene *scene, t_point hit_point, t_obj *object)
{
	float		i;
	t_vector	n;
	t_vector	l;
	t_vector	v;
	t_vector	r;

	i = scene->ambient.ratio;
	n = object->surface_normal;
	l = subtract_points(scene->light.coordinates, hit_point);
	if (apply_shadow(hit_point, object, scene))
		return (i);
	if (dot_product(n, l) > 0)
		i += scene->light.brightness_ratio
			* (dot_product(n, l) / vector_length(l));
	v = init_vector_p(hit_point, scene->camera.coordinates);
	r = subtract_vectors(scale_vec(scale_vec(n, 2.0), dot_product(n, l)), l);
	if (dot_product(r, v) < 0)
		i += scene->light.brightness_ratio
			* pow(dot_product(r, v) / (vector_length(r)
					* vector_length(v)), PHONG);
	return (i);
}
