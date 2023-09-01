/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 09:44:32 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/01 14:57:01 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	process_pl(t_scene *scene, char **split)
{
	t_list		*new_node;
	t_object	*new_object;
	t_plane		*plane;

	if (ft_count_str(split) != 4)
		return (ft_parsing_error("unvalid params: ", "plane", 0)); 
	plane = (t_plane *)malloc(sizeof(t_plane));
	new_object = malloc(sizeof(t_object));
	if (process_pl_coordinates(plane, split[1]) != 0)
		return (free(plane), 1);
	if (process_pl_vector(plane, split[2]) != 0)
		return (free(plane), 1);
	/* if (process_pl_rgb(plane, split[3]) != 0)
		return (free(plane), 1); */
	if (process_rgb_obj(new_object, split[3], "plane") != 0)
		return (free(plane), 1);
	new_object->body.plane = plane;
	new_object->body_type = PLANE;
	new_node = ft_lstnew(new_object);
	ft_lstadd_back(&(scene->objects), new_node);
	return (0);
}

int	process_pl_coordinates(t_plane *plane, char *str)
{
	char	**sub_split;

	sub_split = ft_split(str, ',');
	if (ft_count_str(sub_split) != 3)
	{
		free_arr(sub_split);
		return (ft_parsing_error("unvalid coordinates: ", "plane", 1));
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
		return (ft_parsing_error("coordinates not int: ", "plane", 1));
	}
	free_arr(sub_split);
	return (0);
}

int	process_pl_vector(t_plane *plane, char *str)
{
	char	**sub_split;

	sub_split = ft_split(str, ',');
	if (ft_count_str(sub_split) != 3 || check_if_nb(sub_split) != 0)
	{
		free_arr(sub_split);
		return (ft_parsing_error("unvalid vector: ", "plane", 1));
	}
	if ((ft_stof(sub_split[0]) >= -1 && ft_stof(sub_split[0]) <= 1
		&& ft_stof(sub_split[1]) >= -1 && ft_stof(sub_split[1]) <= 1
		&& ft_stof(sub_split[2]) >= -1 && ft_stof(sub_split[2]) <= 1)
		&& check_if_vec(sub_split) == 0)
	{
		plane->normal_vector.x = ft_stof(sub_split[0]);
		plane->normal_vector.y = ft_stof(sub_split[1]);
		plane->normal_vector.z = ft_stof(sub_split[2]);
	}
	else
	{
		free_arr(sub_split);
		return (ft_parsing_error("vector out of range: ", "plane", 1));
	}
	free_arr(sub_split);
	return (0);
}

/* int	process_pl_rgb(t_plane *plane, char *str)
{
	char	**sub_split;

	sub_split = ft_split(str, ',');
	if (ft_count_str(sub_split) != 3 && check_if_nb(sub_split) != 0)
	{
		free_arr(sub_split);
		return (ft_parsing_error("unvalid rgb params: ", "plane", 1));
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
		return (ft_parsing_error("colors out of range: ", "plane", 1));
	}
	free_arr(sub_split);
	return (0);
} */

void	del_plane(void *content)
{
	t_plane	*plane;

	if (content)
	{
		plane = (t_plane *)content;
		free(plane);
	}
}
