/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:59:42 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/28 13:59:46 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_point    pixel_to_coord(t_scene *scene, int pixel_x, int pixel_y)
{
    t_point coord;
    float   width = 30.0;
    float   height = 30.0;

    coord.x = scene->camera.coordinates.x - (width / 2)
        + (width * (pixel_x / scene->mlx->width));
    coord.y = scene->camera.coordinates.y - (height / 2)
        + (height * (pixel_y / scene->mlx->height));
    coord.z = width / (2 * tan((double)scene->camera.field_of_view / 2));
    return (coord);
}
