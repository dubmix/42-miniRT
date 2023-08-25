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
    if (ft_count_str(split) != 4)
        return (ft_parsing_error("unvalid plane params", 0));
    create_pl_list(scene);
    if (process_pl_coordinates(scene, split[1]) != 0)
        return (0);
    if (process_pl_vector(scene, split[2]) != 0)
        return (0);
    if (process_pl_rgb(scene, split[3]) != 0)
        return (0);
    return (0);
}

void    create_pl_list(t_scene *scene)
{
    t_list *new_object;
    t_list *current_object;

    new_object = ft_lstnew(NULL);
    if (scene->planes == NULL)
        scene->planes = new_object;
    else
    {
        current_object = scene->planes;
        current_object->next = new_object;
    }
}

int process_pl_coordinates(t_scene *scene, char *str)
{
    char **sub_split;
    t_plane *plane;

    plane = (t_plane *)scene->planes;
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

int process_pl_vector(t_scene *scene, char *str)
{
    char **sub_split;
    t_plane *plane;

    plane = (t_plane *)scene->planes;
    sub_split = ft_split(str, ',');
    if (ft_count_str(sub_split) != 3)
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

int process_pl_rgb(t_scene *scene, char *str)
{
    char **sub_split;
    t_plane *plane;
    
    plane = (t_plane *)scene->planes;
    sub_split = ft_split(str, ',');
    if (ft_count_str(sub_split) != 3)
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