/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:01:04 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/18 07:56:03 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	process_rgb_obj(t_obj *object, char *str, char *identifier)
{
	char	**sub_split;

	sub_split = ft_split(str, ',');
	rm_nl(sub_split);
	if (ft_count_str(sub_split) != 3 || check_if_nb(sub_split) != 0)
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
		return (ft_parsing_error("colors out of range: ", identifier, 1));
	}
	free_arr(sub_split);
	return (0);
}
