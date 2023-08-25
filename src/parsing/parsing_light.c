/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:47:48 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/23 19:48:07 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int process_light(t_scene *scene, char **split)
{
    if (ft_count_str(split) != 3)
        return (ft_parsing_error("unvalid light params", 0));
    if (process_light_coordinates(scene, split[1]) != 0)
        return (0);
    if (ft_stof(split[2]) >= 0.0 && ft_stof(split[2]) <= 1.0)
        scene->light.brightness_ratio = ft_stof(split[2]);
    else
        return (ft_parsing_error("light brightness out of range", 0));
    return (0);
}

int process_light_coordinates(t_scene *scene, char *str)
{
    char **sub_split;
    
    sub_split = ft_split(str, ',');
    if (ft_count_str(sub_split) != 3)
    {   
        free_arr(sub_split);
        return (ft_parsing_error("unvalid light coordinates", 1));
    }
    if (ft_isnumber(sub_split[0]) == 1
            && ft_isnumber(sub_split[1]) == 1
            && ft_isnumber(sub_split[2]) == 1)
    {
        scene->light.coordinates.x = ft_atoi(sub_split[0]);
        scene->light.coordinates.x = ft_atoi(sub_split[1]);
        scene->light.coordinates.x = ft_atoi(sub_split[2]);
    }
    else
    {
        free_arr(sub_split);
        return (ft_parsing_error("light coordinates not int", 1));
    }
    free_arr(sub_split);
    return (0);
}