/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 08:55:08 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/01 10:16:49 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_parsing_error(char *str, char *object, int return_value)
{
	write(STDERR_FILENO, "Parsing error: ", 15);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, object, ft_strlen(object));
	write(STDERR_FILENO, "\n", 1);
	return (return_value);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	del_obj(void *arg)
{
	t_object	*obj;

	if (!arg)
		return ;
	obj = (t_object *)arg;
	if (obj->body_type == PLANE)
		free(obj->body.plane);
	if (obj->body_type == SPHERE)
		free(obj->body.sphere);
	if (obj->body_type == CYLINDER)
		free(obj->body.cylinder);
	free(obj);
}

void	free_all(t_scene *scene)
{
	ft_lstclear(&scene->objects, del_obj);
/* 	if (scene->planes != NULL)
		ft_lstclear(&scene->planes, del_plane);
	if (scene->spheres != NULL)
		ft_lstclear(&scene->spheres, del_sphere);
	if (scene->cylinders != NULL)
		ft_lstclear(&scene->cylinders, del_cylinder); */
}
