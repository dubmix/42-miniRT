/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 08:47:55 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/06 14:22:53 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

#include "../../types.h"

int		ft_strncmp_rev(char *str, char *str_to_find, int n);
int		ft_strlen(char *str);
char	*ft_strrchr(const char *str, int c);
void	free_arr(char **arr);
void	free_all(t_scene *scene);
int		ft_count_str(char **split);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		ft_atoi(const char *str);
float	ft_stof(char *str);
int		ft_isdigit(int c);
int		ft_isnumber(char *str);
char	*get_next_line(int fd, int flag);
char	*ft_memcpy(char *stash);
char	*readtext(int fd, char *stash);
int		findnewline(char *stash);
char	*ft_strjoin(char *stash, char *buf);
int		ft_strlen_gnl(char *str);
char	*ft_strcpy(char *stash, char *buf, char *str);
int		nb_of_strs(char const *s, char c);
void	get_next_str(char **next_str, size_t *next_strlen, char c);
char	**ft_free(char **tab);
char	*split(char *stash);
char	**ft_split(char const *s, char c);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
unsigned int	ft_strlcpy(char *dest, const char *src, size_t size);

#endif
