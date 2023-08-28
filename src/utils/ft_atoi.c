/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 08:46:19 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/28 08:46:21 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	nb;

	i = 0;
	neg = 1;
	nb = 0;
	if (str[i] == 7 || str[i] == 8)
		return (0);
	while (str[i] == ' ' || (str[i] <= 13 && str[i] >= 7))
		i++;
	if (str[i] == '-')
		neg = neg * -1;
	if (str[i] == '+' || str [i] == '-')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (neg * nb);
}
