/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:58:07 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/23 10:35:19 by aehrlich         ###   ########.fr       */
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

# define WIDTH 512
# define HEIGHT 512

static mlx_image_t *scene;

void	init_parsing(t_scene *scene);
int     parsing_main(t_scene *scene, char *file_name);
int     ft_parsing_error(char *str, char *object, int return_value);

int     read_from_file(t_scene *scene, int fd);
int     parsing_line(t_scene *scene, char *line);
int     find_id(t_scene *scene, char **split);

int     process_ambient(t_scene *scene, char **split);
int     process_rgb(char *str, char *def, t_color *rgb);

int     process_camera(t_scene *scene, char **split);
int     process_camera_coordinates(t_scene *scene, char *str);
int     process_camera_orientation(t_scene *scene, char *str);

int     process_light(t_scene *scene, char **split);
int     process_light_coordinates(t_scene *scene, char *str);

int     process_pl(t_scene *scene, char **split);
int     process_pl_coordinates(t_plane *plane, char *str);
int     process_pl_vector(t_plane *plane, char *str);
int     process_pl_rgb(t_plane *plane, char *str);

int     process_sp(t_scene *scene, char **split);
int     process_sp_coordinates(t_sphere *sphere, char *str);
int     process_sp_rgb(t_sphere *sphere, char *str);
void    del_sphere(void *content);

int     process_cy(t_scene *scene, char **split);
int     process_cy_coordinates(t_cylinder *cylinder, char *str);
int     process_cy_vector(t_cylinder *cylinder, char *str);
int     process_cy_rgb(t_cylinder *cylinder, char *str);
void    del_cylinder(void *content);

void    print_list(t_list *list);
void    del_plane(void *content);
int     check_if_nb(char **sub_split);

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
