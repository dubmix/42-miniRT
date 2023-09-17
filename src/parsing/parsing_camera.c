/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 18:20:04 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/17 08:35:45 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	process_camera(t_scene *scene, char **split)
{
	if (scene->camera.set == 1)
		return (ft_parsing_error("cannot redefine: ", "camera", 1));
	else
		scene->camera.set = 1;
	if (ft_count_str(split) != 4)
		return (ft_parsing_error("unvalid params: ", "camera", 1));
	if (process_camera_coordinates(scene, split[1]) != 0)
		return (1);
	if (process_vec(&scene->camera.orientation, split[2], "camera") != 0)
		return (1);
	if (ft_atoi(split[3]) >= 0 && ft_atoi(split[3]) <= 180)
	{
		scene->camera.field_of_view = ft_atoi(split[3]);
		return (0);
	}
	else
		return (ft_parsing_error("out of range: ", "fov", 1));
	return (0);
}

int	process_camera_coordinates(t_scene *scene, char *str)
{
	char	**sub_split;

	sub_split = ft_split(str, ',');
	if (ft_count_str(sub_split) != 3 || check_if_nb(sub_split) != 0)
	{
		free_arr(sub_split);
		return (ft_parsing_error("unvalid coordinates: ", "camera", 0));
	}
	if (ft_isnumber(sub_split[0]) == 1
		&& ft_isnumber(sub_split[1]) == 1
		&& ft_isnumber(sub_split[2]) == 1)
	{
		scene->camera.coordinates.x = ft_stof(sub_split[0]);
		scene->camera.coordinates.y = ft_stof(sub_split[1]);
		scene->camera.coordinates.z = ft_stof(sub_split[2]);
	}
	else
	{
		free_arr(sub_split);
		return (ft_parsing_error("coordinates not int: ", "camera", 0));
	}
	free_arr(sub_split);
	return (0);
}

int	process_camera_orientation(t_scene *scene, char *str)
{
	char	**sub_split;

	sub_split = ft_split(str, ',');
	if (ft_count_str(sub_split) != 3 || check_if_nb(sub_split) != 0)
	{
		free_arr(sub_split);
		return (ft_parsing_error("unvalid or. params: ", "camera", 1));
	}
	if (((ft_stof(sub_split[0]) >= -1 && ft_stof(sub_split[0]) <= 1)
			&& (ft_stof(sub_split[1]) >= -1 && ft_stof(sub_split[1]) <= 1)
			&& (ft_stof(sub_split[2]) >= -1 && ft_stof(sub_split[2]) <= 1))
		&& check_if_vec(sub_split) == 0)
	{
		scene->camera.orientation.x = ft_stof(sub_split[0]);
		scene->camera.orientation.y = ft_stof(sub_split[1]);
		scene->camera.orientation.z = ft_stof(sub_split[2]);
	}
	else
	{
		free_arr(sub_split);
		return (ft_parsing_error("or. out of range: ", "camera", 1));
	}
	free_arr(sub_split);
	return (0);
}
