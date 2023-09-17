/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:00:16 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/17 13:23:45 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	main(int argc, char *argv[])
{
	t_scene	scene;

	if (argc != 2)
		return (ft_parsing_error("./miniRT needs one file", "", 0));
	if (parsing_main(&scene, argv[1]) != 0)
		return (1);
	scene.mlx = mlx_init(WIDTH, HEIGHT, "miniRT", 1);
	scene.img = mlx_new_image(scene.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(scene.mlx, scene.img, 0, 0);
	mlx_loop_hook(scene.mlx, ft_hook, &scene);
	ft_render(&scene);
	mlx_loop(scene.mlx);
	mlx_terminate(scene.mlx);
	free_all(&scene);
	return (0);
}

 void	ft_hook(void *param)
{
	t_scene	*scene;

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
	//######
	if (mlx_is_key_down(scene->mlx, MLX_KEY_E))
	{
		scene->camera.coordinates.x += 1.0;
		ft_render(scene);
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_D))
	{
		scene->camera.coordinates.x -= 1.0;
		ft_render(scene);
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_R))
	{
		scene->camera.coordinates.y += 1.0;
		ft_render(scene);
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_F))
	{
		scene->camera.coordinates.y -= 1.0;
		ft_render(scene);
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_T))
	{
		scene->camera.coordinates.z += 1.0;
		printf("New Z: %f\n", scene->camera.coordinates.z);
		ft_render(scene);
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_G))
	{
		scene->camera.coordinates.z -= 1.0;
		ft_render(scene);
	}
	//######
	if (mlx_is_key_down(scene->mlx, MLX_KEY_Y))
	{
		scene->camera.orientation.x += 0.1;
		ft_render(scene);
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_H))
	{
		scene->camera.orientation.x -= 0.1;
		ft_render(scene);
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_U))
	{
		scene->camera.orientation.y += 0.1;
		ft_render(scene);
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_J))
	{
		scene->camera.orientation.y -= 0.1;
		ft_render(scene);
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_I))
	{
		scene->camera.orientation.z += 0.1;
		ft_render(scene);
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_K))
	{
		scene->camera.orientation.z -= 0.1;
		ft_render(scene);
	}
}
