/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:00:01 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/06 12:15:11 by aehrlich         ###   ########.fr       */
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

#endif
