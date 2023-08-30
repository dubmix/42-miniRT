/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:00:16 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/30 10:34:03 by aehrlich         ###   ########.fr       */
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
	if (mlx_is_key_down(scene->mlx, MLX_KEY_S) 
			&& mlx_is_key_down(scene->mlx, MLX_KEY_UP))
	{
		scene->light.coordinates.z += 0.3;
		ft_render(scene);
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_S) 
			&& mlx_is_key_down(scene->mlx, MLX_KEY_DOWN))
	{
		scene->light.coordinates.z -= 0.3;
		ft_render(scene);
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_S) 
			&& mlx_is_key_down(scene->mlx, MLX_KEY_LEFT))
	{
		scene->light.coordinates.x -= 0.3;
		ft_render(scene);
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_S) 
			&& mlx_is_key_down(scene->mlx, MLX_KEY_RIGHT))
	{
		scene->light.coordinates.x += 0.3;
		ft_render(scene);
	}
}

void    print_list(t_list *list)
{
    t_list *current;
    //t_plane *plane;
	//t_cylinder *cylinder;
	t_sphere *sphere;

    current = list;
    while (current != NULL)
    {
        //plane = (t_plane *)(current->content);
		sphere = (t_sphere *)(current->content);
        // printf("plane x is: %f\n", plane->plane_point.x);
        // printf("plane x vector is: %f\n", plane->normal_vector.x);
        // printf("plane b color is: %u\n", plane->color.b);
		printf("sphere diameter is: %f\n", sphere->diameter);
        current = current->next;
    }
}

int main(int argc, char *argv[])
{
	//mlx_t *mlx;
	t_scene	scene;
	t_scene *ptr;

	ptr = &scene;
	//argv = NULL;
	if (argc != 2)
		return (ft_parsing_error("./miniRT needs one file", "", 0));
	parsing_main(ptr, argv[1]);
	//print_list(scene.spheres);
	scene.mlx = mlx_init(WIDTH, HEIGHT, "miniRT", 1);
	img = mlx_new_image(scene.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(scene.mlx, img, 0, 0);
	mlx_loop_hook(scene.mlx, ft_hook, ptr);
	ft_render(ptr);
	//test(ptr);
	// mlx_loop_hook(scene.mlx, ft_put_pixel, scene.mlx);
	mlx_loop(scene.mlx);
	mlx_terminate(scene.mlx);
	return (0);
}
