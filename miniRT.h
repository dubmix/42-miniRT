/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:58:07 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/02 17:11:13 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "mlx/include/MLX42/MLX42.h"
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "types.h"

# define WIDTH 768
# define HEIGHT 512

extern mlx_image_t *img;

uint32_t rgb_to_uint32(uint32_t r, uint32_t g, uint32_t b, float brightness, t_scene *scene);
t_point	*intersection(t_object	*obj, t_ray ray, t_point *temp_hit);

t_color sphere_texture(t_point closest_hit, t_object *object);

void    ft_hook(void *param);
void	ft_render(void *param);

int     ft_parsing_error(char *str, char *object, int return_value);
int     parsing_main(t_scene *scene, char *file_name);

int     ft_strncmp_rev(char *str, char *str_to_find, int n);
int	    ft_strlen(char *str);
char	*ft_strrchr(const char *str, int c);
void	free_arr(char **arr);
void    free_all(t_scene *scene);
int     ft_count_str(char **split);
int	    ft_strncmp(const char *str1, const char *str2, size_t n);
int	    ft_atoi(const char *str);
float   ft_stof(char *str);
int	    ft_isdigit(int c);
int     ft_isnumber(char *str);

char	*get_next_line(int fd, int flag);
char	*ft_memcpy(char *stash);
char	*readtext(int fd, char *stash);
int		findnewline(char *stash);
char	*ft_strjoin(char *stash, char *buf);
int		ft_strlen_gnl(char *str);
char	*split(char *stash);
char	*ft_strcpy(char *stash, char *buf, char *str);
int	     ft_isinset(char c, char const *set);
char	*ft_strtrim(char *s1, char const *set);

int		nb_of_strs(char const *s, char c);
void	get_next_str(char **next_str, size_t *next_strlen, char c);
char	**ft_free(char **tab);
char	**ft_split(char const *s, char c);
unsigned int	ft_strlcpy(char *dest, const char *src, size_t size);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
