/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 09:34:40 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/01 14:56:39 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	process_sp(t_scene *scene, char **split)
{
	t_list		*new_node;
	t_object	*new_object;
	t_sphere	*sphere;

	if (ft_count_str(split) != 4)
		return (ft_parsing_error("unvalid params: ", "sphere", 0));
	sphere = (t_sphere *)malloc(sizeof(t_sphere)); //protect mallocs
	new_object = malloc(sizeof(t_object));
	if (process_sp_coordinates(sphere, split[1]) != 0)
		return (free(sphere), 1);
	if (ft_isnumber(split[2]) != 1)
		return (free(sphere), 1);
	else
		sphere->diameter = ft_stof(split[2]);
/* 	if (process_sp_rgb(sphere, split[3]) != 0)
		return (free(sphere), 1); */
	if (process_rgb_obj(new_object, split[3], "sphere") != 0)
		return (free(sphere), 1);
	new_object->body.sphere = sphere;
	new_object->body_type = SPHERE;
	new_node = ft_lstnew(new_object);
	ft_lstadd_back(&(scene->objects), new_node);
	return (0);
}

int	process_sp_coordinates(t_sphere *sphere, char *str)
{
	char	**sub_split;

	sub_split = ft_split(str, ',');
	if (ft_count_str(sub_split) != 3)
	{
		free_arr(sub_split);
		return (ft_parsing_error("unvalid coordinates: ", "sphere", 1));
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
		return (ft_parsing_error("coordinates not int: ", "sphere", 1));
	}
	free_arr(sub_split);
	return (0);
}