/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 09:44:32 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/25 09:44:53 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int process_pl(t_scene *scene, char **split)
{
    t_list  *new_object;
    t_plane *plane;

    if (ft_count_str(split) != 4)
        return (ft_parsing_error("unvalid plane params", 0));    
    plane = (t_plane *)malloc(sizeof(t_plane));
    if (process_pl_coordinates(plane, split[1]) != 0)
        return (free_plane(scene->planes, plane), 1);
    if (process_pl_vector(plane, split[2]) != 0)
        return (free_plane(scene->planes, plane), 1);
    if (process_pl_rgb(plane, split[3]) != 0)
        return (free_plane(scene->planes, plane), 1);
    new_object = ft_lstnew(plane);
    ft_lstadd_back(&(scene->planes), new_object);
    return (0);
}

int process_pl_coordinates(t_plane *plane, char *str)
{
    char **sub_split;

    sub_split = ft_split(str, ',');
    if (ft_count_str(sub_split) != 3)
    {   
        free_arr(sub_split);
        return (ft_parsing_error("unvalid plane coordinates", 1));
    }
    if (ft_isnumber(sub_split[0]) == 1
            && ft_isnumber(sub_split[1]) == 1
            && ft_isnumber(sub_split[2]) == 1)
    {
        plane->plane_point.x = ft_stof(sub_split[0]);
        plane->plane_point.y = ft_stof(sub_split[1]);
        plane->plane_point.z = ft_stof(sub_split[2]);
    }
    else
    {
        free_arr(sub_split);
        return (ft_parsing_error("plane coordinates not numbers", 1));
    }
    free_arr(sub_split);
    return (0);
}

int process_pl_vector(t_plane *plane, char *str)
{
    char **sub_split;

    sub_split = ft_split(str, ',');
    if (ft_count_str(sub_split) != 3 && check_if_nb(sub_split) != 0)
    {   
        free_arr(sub_split);
        return (ft_parsing_error("unvalid plane vector", 1));
    }
    if (ft_stof(sub_split[0]) >= -1 && ft_stof(sub_split[0]) <= 1
            && ft_stof(sub_split[1]) >= -1 && ft_stof(sub_split[1]) <= 1
            && ft_stof(sub_split[2]) >= -1 && ft_stof(sub_split[2]) <= 1)
    {
        plane->normal_vector.x = ft_stof(sub_split[0]);
        plane->normal_vector.y = ft_stof(sub_split[1]);
        plane->normal_vector.z = ft_stof(sub_split[2]);
    }
    else
    {
        free_arr(sub_split);
        return (ft_parsing_error("plane vector out of range", 1));
    }
    free_arr(sub_split);
    return (0);
}

int process_pl_rgb(t_plane *plane, char *str)
{
    char **sub_split;

    sub_split = ft_split(str, ',');
    if (ft_count_str(sub_split) != 3 && check_if_nb(sub_split) != 0)
    {   
        free_arr(sub_split);
        return (ft_parsing_error("unvalid plane rgb params", 1));
    }
    if ((ft_atoi(sub_split[0]) >= 0 && ft_atoi(sub_split[0]) <= 255)
            && (ft_atoi(sub_split[1]) >= 0 && ft_atoi(sub_split[1]) <= 255)
            && (ft_atoi(sub_split[2]) >= 0 && ft_atoi(sub_split[2]) <= 255))
    {
        plane->color.r = ft_atoi(sub_split[0]);
        plane->color.g = ft_atoi(sub_split[1]);
        plane->color.b = ft_atoi(sub_split[2]);
    }
    else
    {
        free_arr(sub_split);
        return (ft_parsing_error("plane colors out of range", 1));
    }
    free_arr(sub_split);
    return (0);
}