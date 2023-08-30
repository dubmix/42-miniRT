/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 09:35:25 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/28 09:56:09 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	process_cy(t_scene *scene, char **split)
{
	t_list		*new_object;
	t_cylinder	*cylinder;

	if (ft_count_str(split) != 6)
		return (ft_parsing_error("unvalid params: ", "cylinder", 1));
	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (process_cy_coordinates(cylinder, split[1]) != 0)
		return (free(cylinder), 1);
	if (process_cy_vector(cylinder, split[2]) != 0)
		return (free(cylinder), 1);
	if (ft_isnumber(split[3]) != 1 || ft_stof(split[3]) <= 0)
		return (free(cylinder), 1);
	else
		cylinder->diameter = ft_stof(split[3]);
	if (ft_isnumber(split[4]) != 1 || ft_stof(split[4]) <= 0)
		return (free(cylinder), 1);
	else
		cylinder->height = ft_stof(split[4]);
	if (process_cy_rgb(cylinder, split[5]) != 0)
		return (free(cylinder), 1);
	new_object = ft_lstnew(cylinder);
	ft_lstadd_back(&(scene->cylinders), new_object);
	return (0);
}

int	process_cy_coordinates(t_cylinder *cylinder, char *str)
{
	char	**sub_split;

	sub_split = ft_split(str, ',');
	if (ft_count_str(sub_split) != 3)
	{
		free_arr(sub_split);
		return (ft_parsing_error("unvalid coordinates: ", "cylinder", 1));
	}
	if (ft_isnumber(sub_split[0]) == 1
		&& ft_isnumber(sub_split[1]) == 1
		&& ft_isnumber(sub_split[2]) == 1)
	{
		cylinder->center.x = ft_stof(sub_split[0]);
		cylinder->center.y = ft_stof(sub_split[1]);
		cylinder->center.z = ft_stof(sub_split[2]);
	}
	else
	{
		free_arr(sub_split);
		return (ft_parsing_error("coordinates not int: ", "cylinder", 1));
	}
	free_arr(sub_split);
	return (0);
}

int	process_cy_vector(t_cylinder *cylinder, char *str)
{
	char	**sub_split;

	sub_split = ft_split(str, ',');
	if (ft_count_str(sub_split) != 3 && check_if_nb(sub_split) != 0)
	{
		free_arr(sub_split);
		return (ft_parsing_error("unvalid vector: ", "cylinder", 1));
	}
	if ((ft_stof(sub_split[0]) >= -1 && ft_stof(sub_split[0]) <= 1
		&& ft_stof(sub_split[1]) >= -1 && ft_stof(sub_split[1]) <= 1
		&& ft_stof(sub_split[2]) >= -1 && ft_stof(sub_split[2]) <= 1)
		&& check_if_vec(sub_split) == 0)
	{
		cylinder->axis.x = ft_stof(sub_split[0]);
		cylinder->axis.y = ft_stof(sub_split[1]);
		cylinder->axis.z = ft_stof(sub_split[2]);
	}
	else
	{
		free_arr(sub_split);
		return (ft_parsing_error("vector out of range: ", "cylinder", 1));
	}
	free_arr(sub_split);
	return (0);
}

int	process_cy_rgb(t_cylinder *cylinder, char *str)
{
	char	**sub_split;

	sub_split = ft_split(str, ',');
	if (ft_count_str(sub_split) != 3 && check_if_nb(sub_split) != 0)
	{
		free_arr(sub_split);
		return (ft_parsing_error("unvalid rgb params", "cylinder", 1));
	}
	if ((ft_atoi(sub_split[0]) >= 0 && ft_atoi(sub_split[0]) <= 255)
		&& (ft_atoi(sub_split[1]) >= 0 && ft_atoi(sub_split[1]) <= 255)
		&& (ft_atoi(sub_split[2]) >= 0 && ft_atoi(sub_split[2]) <= 255))
	{
		cylinder->color.r = ft_atoi(sub_split[0]);
		cylinder->color.g = ft_atoi(sub_split[1]);
		cylinder->color.b = ft_atoi(sub_split[2]);
	}
	else
	{
		free_arr(sub_split);
		return (ft_parsing_error("colors out of range", "cylinder", 1));
	}
	free_arr(sub_split);
	return (0);
}

void	del_cylinder(void *content)
{
	t_cylinder	*cylinder;

	if (content)
	{
		cylinder = (t_cylinder *)content;
		free(cylinder);
	}
}
