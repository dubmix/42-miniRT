/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:59:46 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/22 15:00:10 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

int ft_parsing_error(char *str)
{
    write(STDERR_FILENO, "Parsing error: ", 15);
    write(STDERR_FILENO, str, ft_strlen(str));
    return (EXIT_FAILURE);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int ft_strncmp_rev(char *str, char *str_to_find, int n)
{
    int i;
    int j;

    i = ft_strlen(str);
    j = ft_strlen(str_to_find);
    while (i >= 0 && j >= 0 && n >= 0)
    {
        if (str[i--] != str_to_find[j--])
            return (1);
        n--;
    }
    return (0);
}
