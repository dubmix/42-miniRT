/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:58:49 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/05 09:58:56 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	process_tx(t_scene *scene, char **split)
{
	mlx_texture_t *mlx_texture;
	//t_object *sphere;
	t_object *object;
	t_list *temp;

	temp = scene->objects;
	if (temp == NULL)
		return (0);
	if (ft_count_str(split) != 2)
		return (ft_parsing_error("unvalid params: ", "texture", 1));
	// if (ft_strncmp_rev(split[2], ".png", 4) != 0)
	// return (ft_parsing_error("unvalid path: ", "texture", 1));
	while (temp)
	{
		object = (t_object *)temp->content;
		if (object->body_type != SPHERE || object->texture.set == 1)
			temp = temp->next;
		else
			break ;
	}
	mlx_texture = mlx_load_png(ft_strtrim(split[1], "\n"));
	//free(split[1]); malloc in ft strim 
	if (mlx_texture == NULL)
	 	return (ft_parsing_error("unvalid file: ", "texture", 1));
	if (mlx_texture_to_color(mlx_texture, &object->texture) != 0)
	 	return (ft_parsing_error("malloc failed: ", "texture", 1));
	object->texture.set = 1;
	return (0);
}

int	mlx_texture_to_color(mlx_texture_t *mlx_texture, t_texture *texture)
{
	unsigned int i;
	int	pixel;

	texture->color = malloc(sizeof(t_color) * mlx_texture->width * mlx_texture->height);
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