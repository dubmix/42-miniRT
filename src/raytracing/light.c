/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:54:22 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/06 12:23:20 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "../raytracing/raytracing.h"

float	apply_light(t_scene *scene, t_point hit_point, t_object *object)
{
	float i;
	t_vector    N;
	t_vector    L;
	t_vector	V;
	t_vector	R;
	t_ray ray;
	t_point light_intersection;
	t_list  *temp_node;
	t_object *temp_obj;
	int s;
	
	s = make_even(100);
	i = scene->ambient.ratio;
	temp_node = scene->objects;
	N = normalize(object->surface_normal);
	L = subtract_points(scene->light.coordinates, hit_point);
	ray.origin = hit_point;
	ray.direction = normalize(L);
	while (temp_node)
	{
		temp_obj = (t_object *)temp_node->content;
		if (temp_obj != object && intersection(temp_obj, ray, &light_intersection) &&
			equal_points(get_nearest_point(light_intersection, scene->light.coordinates, hit_point), light_intersection))
			return (i);
		temp_node = temp_node->next;
	}
	if (dot_product(N, L) > 0)
		i += scene->light.brightness_ratio * (dot_product(N, L)/(vector_length(N) * vector_length(L)));
	if (s > 0)
	{
		V = init_vector_p(hit_point, scene->camera.coordinates);
		R = subtract_vectors(scale_vec(scale_vec(N, 2.0), dot_product(N, L)), L);
		if (dot_product(R, V) < 0)
			i += scene->light.brightness_ratio * pow(dot_product(R, V)/(vector_length(R) * vector_length(V)), s);
	}
	return (i);
}
