/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:00:16 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/01 08:05:21 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

mlx_image_t *img;

void ft_hook(void *param)
{
	t_scene *scene;

	scene = param;
	if (mlx_is_key_down(scene->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(scene->mlx);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_UP))
	{
		scene->light.coordinates.z += 5.0;
		ft_render(scene);
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_DOWN))
	{
		scene->light.coordinates.z -= 5.0;
		ft_render(scene);
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_LEFT))
	{
		scene->light.coordinates.x -= 5.0;
		ft_render(scene);
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_RIGHT))
	{
		scene->light.coordinates.x += 5.0;
		ft_render(scene);
	}
}

int main(int argc, char *argv[])
{
	t_scene	scene;
	t_scene *ptr;

	ptr = &scene;
	if (argc != 2)
		return (ft_parsing_error("./miniRT needs one file", "", 0));
	if (parsing_main(ptr, argv[1]) != 0)
		return (0);
	scene.mlx = mlx_init(WIDTH, HEIGHT, "miniRT", 1);
	img = mlx_new_image(scene.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(scene.mlx, img, 0, 0);
	mlx_loop_hook(scene.mlx, ft_hook, ptr);
	ft_render(ptr);
	mlx_loop(scene.mlx);
	mlx_terminate(scene.mlx);
	return (0);
}
