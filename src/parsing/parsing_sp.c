/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 09:34:40 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/25 09:35:00 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int process_sp(t_scene *scene, char **split)
{
    t_list  *new_object;
    t_sphere *sphere;

    if (ft_count_str(split) != 4)
        return (ft_parsing_error("unvalid sphere params", 0));    
    sphere = (t_sphere *)malloc(sizeof(t_sphere));
    if (process_sp_coordinates(sphere, split[1]) != 0)
        return (free_sphere(scene->spheres, sphere), 1);
    if (ft_isnumber(split[2]) != 1)
        return (free_sphere(scene->spheres, sphere), 1);
    else
        sphere->diameter = ft_stof(split[2]);
    if (process_sp_rgb(sphere, split[3]) != 0)
        return (free_sphere(scene->spheres, sphere), 1);
    new_object = ft_lstnew(sphere);
    ft_lstadd_back(&(scene->spheres), new_object);
    return (0);
}

int process_sp_coordinates(t_sphere *sphere, char *str)
{
    char **sub_split;

    sub_split = ft_split(str, ',');
    if (ft_count_str(sub_split) != 3)
    {   
        free_arr(sub_split);
        return (ft_parsing_error("unvalid sphere coordinates", 1));
    }
    if (ft_isnumber(sub_split[0]) == 1
            && ft_isnumber(sub_split[1]) == 1
            && ft_isnumber(sub_split[2]) == 1)
    {
        sphere->center.x = ft_stof(sub_split[0]);
        sphere->center.y = ft_stof(sub_split[1]);
        sphere->center.z = ft_stof(sub_split[2]);
    }
    else
    {
        free_arr(sub_split);
        return (ft_parsing_error("sphere coordinates not numbers", 1));
    }
    free_arr(sub_split);
    return (0);
}

int process_sp_rgb(t_sphere *sphere, char *str)
{
    char **sub_split;

    sub_split = ft_split(str, ',');
    if (ft_count_str(sub_split) != 3 && check_if_nb(sub_split) != 0)
    {   
        free_arr(sub_split);
        return (ft_parsing_error("unvalid sphere rgb params", 1));
    }
    if ((ft_atoi(sub_split[0]) >= 0 && ft_atoi(sub_split[0]) <= 255)
            && (ft_atoi(sub_split[1]) >= 0 && ft_atoi(sub_split[1]) <= 255)
            && (ft_atoi(sub_split[2]) >= 0 && ft_atoi(sub_split[2]) <= 255))
    {
        sphere->color.r = ft_atoi(sub_split[0]);
        sphere->color.g = ft_atoi(sub_split[1]);
        sphere->color.b = ft_atoi(sub_split[2]);
    }
    else
    {
        free_arr(sub_split);
        return (ft_parsing_error("sphere colors out of range", 1));
    }
    free_arr(sub_split);
    return (0);
}