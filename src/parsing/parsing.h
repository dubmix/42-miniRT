/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:08:57 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/18 08:09:15 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H

# define PARSING_H

# include "../utils/utils.h"
# include <fcntl.h>

void	init_parsing(t_scene *scene);

int		read_from_file(t_scene *scene, int fd);
int		parsing_line(t_scene *scene, char *line);
int		find_id(t_scene *scene, char **split);
void	rm_nl(char **split);
void	rm_nlpng(char **split);

int		process_ambient(t_scene *scene, char **split);
int		process_rgb(char *str, char *def, t_color *rgb);

int		process_camera(t_scene *scene, char **split);
int		process_camera_coordinates(t_scene *scene, char *str);
int		process_camera_orientation(t_scene *scene, char *str);

int		process_light(t_scene *scene, char **split);
int		process_light_coordinates(t_scene *scene, char *str);

int		process_rgb_obj(t_obj *object, char *str, char *identifier);

int		process_pl(t_scene *scene, char **split);
int		process_pl_coordinates(t_plane *plane, char *str);
int		process_pl_vector(t_plane *plane, char *str);

int		process_sp(t_scene *scene, char **split);
int		process_sp_coordinates(t_sphere *sphere, char *str);

int		process_cy(t_scene *scene, char **split);
int		process_cy_coordinates(t_cylinder *cylinder, char *str);

int		check_if_nb(char **sub_split);
int		check_if_vec(char **sub_split);

int		process_tx(t_scene *scene, char **split);
int		mlx_texture_to_color(mlx_texture_t *mlx_texture, t_obj *obj);
int		process_vec(t_vector *vector, char *str, char *identifier);

int		ft_parsing_error(char *str, char *object, int return_value);

#endif
