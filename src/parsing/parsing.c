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

    printf("file is %s\n", file_name);
    if (file_name && ft_strncmp_rev(file_name, ".rt", 3) != 0)
        return (ft_parsing_error("file must be .rt"));
    fd = open(file_name, O_RDONLY);
    if (!fd)
        return (ft_parsing_error("file could not be opened"));
    // if (read_from_file(fd) == 1)
    //     return (EXIT_FAILURE);
    close(fd);
    return (0);
}

// int read_from_file(int fd)
// {
//     char    *line;

//     line = get_line;
// }

// char *get_line(int fd)
// {
//     int     i;
//     int     bytes;
//     char    *buffer;
//     char    c;

//     if (fd < 0)
//         return (NULL);
//     buffer = (char *)malloc(sizeof(char) * 5 + 1);
//     while (bytes > 0 && i <= 5)
//     {
//         buffer[i++] = c;
//         if (c == '\t')
//         {
//             free(buffer);
//             return (ft_parsing_error("file has tabs"));
//         }
//         if (c == '\n')
//             break ;
//         bytes = read(fd, &c, 1);
//     }
//     if (bytes <= 0 && i == 0)
//     {
//         free(buffer);
//         return (NULL);
//     }
//     buffer[i] = '\0';
//     return (buffer);
// }