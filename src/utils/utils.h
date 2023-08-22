/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 08:47:55 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/22 19:53:46 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*ft_memcpy(char *stash);
char	*readtext(int fd, char *stash);
int		findnewline(char *stash);
char	*ft_strjoin(char *stash, char *buf);
int		ft_strlen_gnl(char *str);
char	*split(char *stash);
char	*ft_strcpy(char *stash, char *buf, char *str);

int	    nb_of_strs(char const *s, char c);
void	get_next_str(char **next_str, size_t *next_strlen, char c);
char	**ft_free(char **tab);
char	**ft_split(char const *s, char c);
unsigned int	ft_strlcpy(char *dest, const char *src, size_t size);




#endif
