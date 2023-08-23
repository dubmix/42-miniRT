/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ambient.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 18:16:25 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/23 18:16:56 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int process_ambient(t_scene *scene, char **split)
{
    if (ft_count_str(split) != 3)
        return (ft_parsing_error("unvalid ambient params", 0));
    if (str_to_float(split[1]) >= 0.0 && str_to_float(split[1]) <= 1.0)
        scene->ambient.ratio = str_to_float(split[1]);
    else
        return (ft_parsing_error("ambient ratio out of range", 0));
    if (process_ambient_rgb(scene, split[2]) != 0)
        return (0);
    //printf("int is %d\n", scene->ambient.color.r);
    return (0);
}

int process_ambient_rgb(t_scene *scene, char *str)
{
    char **sub_split;
    
    sub_split = ft_split(str, ',');
    if (ft_count_str(sub_split) != 3)
    {   
        free_arr(sub_split);
        return (ft_parsing_error("unvalid ambient rgb params", 1));
    }
    if ((ft_atoi(sub_split[0]) >= 0 && ft_atoi(sub_split[0]) <= 255)
            && (ft_atoi(sub_split[1]) >= 0 && ft_atoi(sub_split[1]) <= 255)
            && (ft_atoi(sub_split[2]) >= 0 && ft_atoi(sub_split[2]) <= 255))
    {
        scene->ambient.color.r = ft_atoi(sub_split[0]);
        scene->ambient.color.g = ft_atoi(sub_split[1]);
        scene->ambient.color.b = ft_atoi(sub_split[2]);
    }
    else
    {
        free_arr(sub_split);
        return (ft_parsing_error("ambient colors out of range", 1));
    }
    free_arr(sub_split);
    return (0);
}