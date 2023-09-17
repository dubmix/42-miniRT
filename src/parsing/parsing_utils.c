/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:59:46 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/17 08:36:16 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_count_str(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	check_if_nb(char **sub_split)
{
	if (ft_isnumber(sub_split[0]) != 1)
		return (1);
	if (ft_isnumber(sub_split[1]) != 1)
		return (1);
	if (ft_isnumber(sub_split[2]) != 1)
		return (1);
	return (0);
}

int	check_if_vec(char **sub_split)
{
	if (ft_stof(sub_split[0]) == 0 && ft_stof(sub_split[1]) == 0
		&& ft_stof(sub_split[2]) == 0)
		return (1);
	else
		return (0);
}
