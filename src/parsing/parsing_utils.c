/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:59:46 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/18 08:06:32 by pdelanno         ###   ########.fr       */
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

void	rm_nl(char **split)
{
	int	i;

	i = ft_count_str(split) - 1;
	if (i < 0)
		return ;
	if (split[i][0] == '\n')
	{
		free(split[i]);
		split[i] = NULL;
	}
}

void	rm_nlpng(char **split)
{
	int	j;

	j = 0;
	while (split[1][j] != '\0')
		j++;
	if (split[1][j - 1] == '\n')
		split[1][j - 1] = '\0';
}
