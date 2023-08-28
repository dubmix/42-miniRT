/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_rev.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 08:45:08 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/28 08:45:10 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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
