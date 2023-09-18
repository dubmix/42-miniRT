/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 09:35:25 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/18 08:06:53 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	process_cy_sub(char **split, t_cylinder *cylinder)
{
	if (process_cy_coordinates(cylinder, split[1]) != 0)
		return (free(cylinder), 1);
	if (process_vec(&cylinder->axis, split[2], "cylinder") != 0)
		return (free(cylinder), 1);
	if (ft_stof(split[3]) <= 0)
		return (free(cylinder), 1);
	else
		cylinder->diameter = ft_stof(split[3]);
	if (ft_stof(split[4]) <= 0)
		return (free(cylinder), 1);
	else
		cylinder->height = ft_stof(split[4]);
	return (0);
}

int	process_cy(t_scene *scene, char **split)
{
	t_list		*new_node;
	t_obj		*new_object;
	t_cylinder	*cylinder;

	if (ft_count_str(split) != 6 || ft_isnumber(split[3]) != 1
		|| ft_isnumber(split[4]) != 1)
		return (ft_parsing_error("unvalid params: ", "cylinder", 1));
	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (1);
	new_object = malloc(sizeof(t_obj));
	if (!new_object)
		return (free(cylinder), 1);
	if (process_cy_sub(split, cylinder) != 0)
		return (free(new_object), 1);
	if (process_rgb_obj(new_object, split[5], "cylinder") != 0)
		return (free(cylinder), free(new_object), 1);
	new_object->body.cylinder = cylinder;
	new_object->body_type = CYLINDER;
	new_node = ft_lstnew(new_object);
	return (ft_lstadd_back(&(scene->objects), new_node), 0);
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
