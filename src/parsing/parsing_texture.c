/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:58:49 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/17 13:16:16 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*ignore_nl(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str[len - 1] == '\n')
		str[len - 1] = '\0';
	return (str);
}

int	process_tx(t_scene *scene, char **split)
{
	mlx_texture_t	*mlx_texture;
	t_obj			*object;
	t_list			*temp;

	temp = scene->objects;
	if (temp == NULL)
		return (0);
	if (ft_count_str(split) != 2)
		return (ft_parsing_error("unvalid params: ", "texture", 1));
	while (temp)
	{
		object = (t_obj *)temp->cont;
		if (object->body_type != SPHERE || object->texture.set == 1)
			temp = temp->next;
		else
			break ;
	}
	if (ft_strncmp_rev(ignore_nl(split[1]), ".png", 4))
		return (ft_parsing_error("unvalid extension: ", "texture", 1));
	mlx_texture = mlx_load_png(split[1]);
	if (mlx_texture == NULL)
		return (ft_parsing_error("unvalid file: ", "texture", 1));
	if (mlx_texture_to_color(mlx_texture, object) != 0)
		return (ft_parsing_error("malloc failed: ", "texture", 1));
	return (0);
}

int	mlx_texture_to_color(mlx_texture_t *mlx_texture, t_obj *obj)
{
	unsigned int	i;
	int				pixel;

	obj->texture.color = malloc(sizeof(t_color) 
			* mlx_texture->width * mlx_texture->height);
	if (obj->texture.color == NULL)
		return (free(mlx_texture), 1);
	i = 0;
	while (i < mlx_texture->width * mlx_texture->height)
	{
		pixel = i * mlx_texture->bytes_per_pixel;
		obj->texture.color[i].r = mlx_texture->pixels[pixel];
		obj->texture.color[i].g = mlx_texture->pixels[pixel + 1];
		obj->texture.color[i].b = mlx_texture->pixels[pixel + 2];
		i++;
	}
	obj->texture.width = mlx_texture->width;
	obj->texture.height = mlx_texture->height;
	obj->texture.set = 1;
	return (free(mlx_texture), 0);
}
