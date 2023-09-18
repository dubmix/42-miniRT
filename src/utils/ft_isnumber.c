/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 08:46:56 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/17 16:54:40 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_isnumber(char *str)
{
	int	i;
	int	dec;

	i = 0;
	dec = 0;
	if (str[i] == '-' && str[i + 1] != '\0')
		i++;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == '.' && dec == 0 && i != 0)
		{
			dec = 1;
			i++;
		}
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
