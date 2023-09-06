/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:00:01 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/06 12:37:45 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H

# include "../../types.h"
# include "../intersections/intersection.h"

int			make_even(int nb);
t_ray		create_ray(t_scene *scene, int pixel_x, int pixel_y);
uint32_t	trace_ray(t_scene *scene, t_ray ray);
float		apply_light(t_scene *scene, t_point hit_point, t_object *object);
uint32_t	rgb_to_uint32(uint32_t r, uint32_t g, uint32_t b, float brightness, t_scene *scene);
t_color		sphere_texture(t_scene *scene, t_point closest_hit, t_object *object);
t_point		*intersection(t_object	*obj, t_ray ray, t_point *temp_hit);
#endif
