/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 09:35:25 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/01 11:20:35 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	process_cy(t_scene *scene, char **split)
{
	t_list		*new_node;
	t_object	*new_object;
	t_cylinder	*cylinder;

	if (ft_count_str(split) != 6)
		return (ft_parsing_error("unvalid params: ", "cylinder", 1));
	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	new_object = malloc(sizeof(t_object));
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
/* 	if (process_cy_rgb(cylinder, split[5]) != 0)
		return (free(cylinder), 1); */
	if (process_rgb_obj(new_object, split[3], "cylinder") != 0)
		return (free(cylinder), 1);
	new_object->body.cylinder = cylinder;
	new_object->intersec_fptr.cyl_func = cylinder_intersect;
	new_object->body_type = CYLINDER;
	new_node = ft_lstnew(new_object);
	ft_lstadd_back(&(scene->objects), new_node);
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
	if (ft_count_str(sub_split) != 3 || check_if_nb(sub_split) != 0)
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

int	process_rgb_obj(t_object *object, char *str, char *identifier)
{
	char	**sub_split;

	sub_split = ft_split(str, ',');
	if (ft_count_str(sub_split) != 3 || check_if_nb(sub_split) != 1)
	{
		free_arr(sub_split);
		return (ft_parsing_error("unvalid rgb params: ", identifier, 1));
	}
	if ((ft_atoi(sub_split[0]) >= 0 && ft_atoi(sub_split[0]) <= 255)
		&& (ft_atoi(sub_split[1]) >= 0 && ft_atoi(sub_split[1]) <= 255)
		&& (ft_atoi(sub_split[2]) >= 0 && ft_atoi(sub_split[2]) <= 255))
	{
		object->color.r = ft_atoi(sub_split[0]);
		object->color.g = ft_atoi(sub_split[1]);
		object->color.b = ft_atoi(sub_split[2]);
	}
	else
	{
		free_arr(sub_split);
		return (ft_parsing_error("colors out of range", identifier, 1));
	}
	free_arr(sub_split);
	return (0);
}

/* int	process_cy_rgb(t_cylinder *cylinder, char *str)
{
	char	**sub_split;

	sub_split = ft_split(str, ',');
	if (ft_count_str(sub_split) != 3 || check_if_nb(sub_split) != 1)
	{
		free_arr(sub_split);
		return (ft_parsing_error("unvalid rgb params: ", "cylinder", 1));
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
} */

void	del_cylinder(void *content)
{
	t_cylinder	*cylinder;

	if (content)
	{
		cylinder = (t_cylinder *)content;
		free(cylinder);
	}
}
