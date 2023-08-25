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

#include "parsing.h"

int ft_parsing_error(char *str, int return_value)
{
    write(STDERR_FILENO, "Parsing error: ", 15);
    write(STDERR_FILENO, str, ft_strlen(str));
    write(STDERR_FILENO, "\n", 1);
    return (return_value);
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

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i--;
	}
	return (0);
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

int	ft_count_str(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0' && i < n)
	{
		if (str1[i] != str2[i])
			break ;
		i++;
	}
	if (str1[i++])
		return (1);
	if (i < n)
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	return (0);
}

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

float ft_stof(char *str)
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

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int ft_isnumber(char *str)
{
	int	i;
	int dec;

	i = 0;
	dec = 0;
	if (str[i] == '-' && str[i + 1] != '\0')
		i++;
	while (str[i])
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