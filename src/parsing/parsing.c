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

#include "parsing.h"

int parsing_main(t_scene *scene, char *file_name)
{
    int fd;

    if (file_name && ft_strncmp_rev(file_name, ".rt", 3) != 0)
        return (ft_parsing_error("file must be .rt", 1));
    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        return (ft_parsing_error("file not found", 1));
    if (read_from_file(scene, fd) == 1)
         return (EXIT_FAILURE);
    close(fd);
    return (0);
}

int read_from_file(t_scene *scene, int fd)
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
        if (parsing_line(scene, line) != 0)
        {
            free(line);
            break ;
        }
        free(line);
        i++;
    }
    return (0);
}

static void print_arr(char **split)
{
    int i;

    i = 0;
    //printf("nb of str in split is: %d\n", ft_count_str(split));
    while (split[i])
    {
        //printf("split [%d] is %s\n", i, split[i]);
        i++;
    }
}

int parsing_line(t_scene *scene, char *line)
{
    char **split;

    if (line[0] != '#' && line[0] != '\n')
    {
        split = ft_split(line, ' ');
        if (!split)
            return (ft_parsing_error("split failed", 1));
        print_arr(split);
        if (find_id(scene, split) != 0)
        {   
            free_arr(split);
            //free_all
            return (1);
        }
        free_arr(split);
    }
    return (0);
}

int find_id(t_scene *scene, char **split)
{
    if (!split[0])
        return (0);
    else if (ft_strncmp(split[0], "A", 1) == 0)
        return (process_ambient(scene, split));
    else if (ft_strncmp(split[0], "C", 1) == 0)
        return (process_camera(scene, split));
    else if (ft_strncmp(split[0], "L", 1) == 0)
        return (process_light(scene, split));
    else if (ft_strncmp(split[0], "sp", 2) == 0)
        return (process_sp(scene, split));
    else if (ft_strncmp(split[0], "pl", 2) == 0)
        return (process_pl(scene, split));
    else if (ft_strncmp(split[0], "cy", 2) == 0)
        return (process_cy(scene, split));
    else
        return (ft_parsing_error("unvalid id", 0));
}