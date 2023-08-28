/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ambient.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 18:16:25 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/28 09:38:59 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	process_ambient(t_scene *scene, char **split)
{
	if (scene->ambient.set == 1)
		return (ft_parsing_error("cannot redefine: ", "ambient", 1));
	else
		scene->ambient.set = 1;
	if (ft_count_str(split) != 3)
		return (ft_parsing_error("unvalid params: ", "ambient", 1));
	if (ft_stof(split[1]) >= 0.0 && ft_stof(split[1]) <= 1.0)
		scene->ambient.ratio = ft_stof(split[1]);
	else
		return (ft_parsing_error("ratio out of range: ", "ambient", 1));
	if (process_rgb(split[2], "ambient", &scene->ambient.color) != 0)
		return (0);
	return (0);
}

int	process_rgb(char *str, char *def, t_color *rgb)
{
	char	**sub_split;

	sub_split = ft_split(str, ',');
	if (ft_count_str(sub_split) != 3)
	{
		free_arr(sub_split);
		return (ft_parsing_error("unvalid rgb params: ", def, 1));
	}
	if ((ft_atoi(sub_split[0]) >= 0 && ft_atoi(sub_split[0]) <= 255)
		&& (ft_atoi(sub_split[1]) >= 0 && ft_atoi(sub_split[1]) <= 255)
		&& (ft_atoi(sub_split[2]) >= 0 && ft_atoi(sub_split[2]) <= 255))
	{
		rgb->r = ft_atoi(sub_split[0]);
		rgb->g = ft_atoi(sub_split[1]);
		rgb->b = ft_atoi(sub_split[2]);
	}
	else
	{
		free_arr(sub_split);
		return (ft_parsing_error("colors out of range: ", def, 1));
	}
	free_arr(sub_split);
	return (0);
}
