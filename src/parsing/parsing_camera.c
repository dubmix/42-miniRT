/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 18:20:04 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/23 18:20:24 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int process_camera(t_scene *scene, char **split)
{
    if (ft_count_str(split) != 4)
        return (ft_parsing_error("unvalid camera params", 0));
    if (process_camera_coordinates(scene, split[1]) != 0)
        return (0);
    if (process_camera_orientation(scene, split[2]) != 0)
        return (0);
    if (ft_atoi(split[3]) >= 0 && ft_atoi(split[3]) <= 180)
    {
        scene->camera.field_of_view = ft_atoi(split[3]);
        return (0);
    }
    else
        return (ft_parsing_error("fov out of range", 0));
    return (0);
}

int process_camera_coordinates(t_scene *scene, char *str)
{
    char **sub_split;
    
    sub_split = ft_split(str, ',');
    if (ft_count_str(sub_split) != 3)
    {   
        free_arr(sub_split);
        return (ft_parsing_error("unvalid camera coordinates", 1));
    }
    if (ft_isnumber(sub_split[0]) == 1
            && ft_isnumber(sub_split[1]) == 1
            && ft_isnumber(sub_split[2]) == 1)
    {
        scene->camera.coordinates.x = ft_atoi(sub_split[0]);
        scene->camera.coordinates.x = ft_atoi(sub_split[1]);
        scene->camera.coordinates.x = ft_atoi(sub_split[2]);
    }
    else
    {
        free_arr(sub_split);
        return (ft_parsing_error("camera coordinates not int", 1));
    }
    free_arr(sub_split);
    return (0);
}

int process_camera_orientation(t_scene *scene, char *str)
{
    char **sub_split;
    
    sub_split = ft_split(str, ',');
    if (ft_count_str(sub_split) != 3)
    {   
        free_arr(sub_split);
        return (ft_parsing_error("unvalid camera orientation params", 1));
    }
    if ((ft_atoi(sub_split[0]) >= -1 && ft_atoi(sub_split[0]) <= 1)
            && (ft_atoi(sub_split[1]) >= -1 && ft_atoi(sub_split[1]) <= 1)
            && (ft_atoi(sub_split[2]) >= -1 && ft_atoi(sub_split[2]) <= 1))

    {
        scene->camera.orientation.x = ft_atoi(sub_split[0]);
        scene->camera.orientation.x = ft_atoi(sub_split[1]);
        scene->camera.orientation.x = ft_atoi(sub_split[2]);
    }
    else
    {
        free_arr(sub_split);
        return (ft_parsing_error("camera orientation out of range", 1));
    }
    free_arr(sub_split);
    return (0);
}

