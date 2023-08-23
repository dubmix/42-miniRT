/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:00:16 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/23 11:50:27 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void ft_hook(void *param)
{
	mlx_t *mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void ft_put_pixel(void *param)
{
	unsigned int i;
	unsigned int j;

	param = NULL;
	j = 0;
	while (j < scene->width)
	{
		i = 0;
		while (i < scene->height)
		{
			mlx_put_pixel(scene, j, i, 0xFF0000FF);
			i++;
		}
		j++;
	}
}

int main(int argc, char *argv[])
{
	//mlx_t *mlx;

	argc = 0;
	argv = NULL;
	//parsing_main("scenes/template.rt");
	// mlx = mlx_init(WIDTH, HEIGHT, "miniRT", 1);
	// scene = mlx_new_image(mlx, 128, 128);
	// mlx_image_to_window(mlx, scene, 100, 100);
	// mlx_loop_hook(mlx, ft_put_pixel, mlx);
	// mlx_loop_hook(mlx, ft_hook, mlx);
	// mlx_loop(mlx);
	// mlx_terminate(mlx);
	test();
	return (0);
}
