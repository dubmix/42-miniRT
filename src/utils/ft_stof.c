/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 08:46:31 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/17 08:40:07 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

float	ft_stof(char *str)
{
	float	result;
	int		i;
	int		neg;

	result = 0.0;
	i = 0;
	neg = 0;
	if (str[i] == '-')
	{
		neg = 1;
		i++;
	}
	while (ft_isdigit((int)str[i]) == 1)
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		result += (str[i] - 48) / 10.0;
	}
	if (neg == 1)
		result = -result;
	return (result);
}
