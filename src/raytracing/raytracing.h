/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:00:01 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/17 10:59:47 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H

# include "../../types.h"
# include "../intersections/intersection.h"

# define PHONG 100

int			make_even(int nb);
float		light(t_scene *scene, t_point hit_point, t_obj *object);
uint32_t	c_int(t_color c, float brightness, t_scene *scene);
t_color		sp_tx(t_point closest_hit, t_obj *object);
t_point		*intersection(t_obj	*obj, t_ray ray, t_point *temp_hit);
bool		camera_is_in_object(t_scene *scene);
t_point		pixel_to_coord(t_scene *scene, int pixel_x, int pixel_y);
void		set_transformation(t_camera *camera);
t_point		transform_point(t_camera c, t_point p);

#endif
