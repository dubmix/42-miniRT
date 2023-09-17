/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:58:49 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/17 10:24:08 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	process_tx(t_scene *scene, char **split)
{
	mlx_texture_t	*mlx_texture;
	char			*trimmed;
	t_obj			*object;
	t_list			*temp;

	temp = scene->objects;
	if (temp == NULL)
		return (0);
	if (ft_count_str(split) != 2)
		return (ft_parsing_error("unvalid params: ", "texture", 1));
	while (temp || object->body_type != SPHERE || object->texture.set == 1)
	{
		object = (t_obj *)temp->cont;
		temp = temp->next;
	}
	trimmed = ft_strtrim(split[1], "\n");
	mlx_texture = mlx_load_png(trimmed);
	if (mlx_texture == NULL)
		return (ft_parsing_error("unvalid file: ", "texture", 1));
	if (mlx_texture_to_color(mlx_texture, &object->texture) != 0)
		return (ft_parsing_error("malloc failed: ", "texture", 1));
	free(mlx_texture);
	free(trimmed);
	object->texture.set = 1;
	return (0);
}

int	mlx_texture_to_color(mlx_texture_t *mlx_texture, t_texture *texture)
{
	unsigned int	i;
	int				pixel;

	texture->color = malloc(sizeof(t_color) 
			* mlx_texture->width * mlx_texture->height);
	if (texture->color == NULL)
		return (1);
	i = 0;
	while (i < mlx_texture->width * mlx_texture->height)
	{
		pixel = i * mlx_texture->bytes_per_pixel;
		texture->color[i].r = mlx_texture->pixels[pixel];
		texture->color[i].g = mlx_texture->pixels[pixel + 1];
		texture->color[i].b = mlx_texture->pixels[pixel + 2];
		i++;
	}
	texture->width = mlx_texture->width;
	texture->height = mlx_texture->height;
	return (0);
}
