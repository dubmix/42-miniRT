/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:08:57 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/22 15:09:55 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H

# define PARSING_H

int     parsing_main(char *file_name);

int     ft_parsing_error(char *str);
int     ft_strncmp_rev(char *str, char *str_to_find, int n);
int	    ft_strlen(char *str);

#endif
