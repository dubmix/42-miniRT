/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_vec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:00:43 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/17 08:36:31 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	process_vec(t_vector *vector, char *str, char *identifier)
{
	char	**sub_split;

	sub_split = ft_split(str, ',');
	if (ft_count_str(sub_split) != 3 || check_if_nb(sub_split) != 0)
	{
		free_arr(sub_split);
		return (ft_parsing_error("unvalid vector: ", identifier, 1));
	}
	if ((ft_stof(sub_split[0]) >= -1 && ft_stof(sub_split[0]) <= 1
			&& ft_stof(sub_split[1]) >= -1 && ft_stof(sub_split[1]) <= 1
			&& ft_stof(sub_split[2]) >= -1 && ft_stof(sub_split[2]) <= 1)
		&& check_if_vec(sub_split) == 0)
	{
		vector->x = ft_stof(sub_split[0]);
		vector->y = ft_stof(sub_split[1]);
		vector->z = ft_stof(sub_split[2]);
	}
	else
	{
		free_arr(sub_split);
		return (ft_parsing_error("vector out of range: ", identifier, 1));
	}
	free_arr(sub_split);
	return (0);
}
