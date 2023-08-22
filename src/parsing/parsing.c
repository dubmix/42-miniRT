/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:55:41 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/22 14:56:02 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

int parsing_main(char *file_name)
{
    int fd;

    if (file_name && ft_strncmp_rev(file_name, ".rt", 3) != 0)
        return (ft_parsing_error("file must be .rt"));
    fd = open(file_name, O_RDONLY);
    if (!fd)
        return (ft_parsing_error("file could not be opened"));
    if (read_from_file(fd) == 1)
         return (EXIT_FAILURE);
    close(fd);
    return (0);
}

int read_from_file(int fd)
{
    char    *line;
    int     i;

    i = 0;
    while (1)
    {
        line = get_next_line(fd);
        if (line == NULL)
            break ;
        //printf("line is: %s\n", line);
        parsing_line(line);
        free(line);
        i++;
    }
    return (0);
}

static void print_arr(char **split)
{
    int i;

    i = 0;
    while (split[i])
    {
        printf("split [%d] is %s\n", i, split[i]);
        i++;
    }
}

int parsing_line(char *line)
{
    char **split;

    if (line[0] != '#' && line[0] != '\n')
    {
        split = ft_split(line, ' ');
        if (!split)
            return (ft_parsing_error("split failed"));
        print_arr(split);
        //parsing_data();
        free_arr(split);
    }
    return (0);
}

// int parsing_data(void)
// {
//     return (0);
// }