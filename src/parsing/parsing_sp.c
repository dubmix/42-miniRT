/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 09:34:40 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/18 07:48:04 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	process_sp(t_scene *scene, char **split)
{
	t_list		*new_node;
	t_obj		*new_object;
	t_sphere	*sphere;

	if (ft_count_str(split) != 4 || ft_isnumber(split[2]) != 1)
		return (ft_parsing_error("unvalid params: ", "sphere", 1));
	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
		return (1);
	new_object = malloc(sizeof(t_obj));
	if (!new_object || process_sp_coordinates(sphere, split[1]) != 0)
		return (free(sphere), 1);
	sphere->diameter = ft_stof(split[2]);
	if (process_rgb_obj(new_object, split[3], "sphere") != 0)
		return (free(sphere), free(new_object), 1);
	new_object->body.sphere = sphere;
	new_object->body_type = SPHERE;
	new_object->texture.set = 0;
	new_object->texture.color = NULL;
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
