/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:00:16 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/21 12:00:44 by pdelanno         ###   ########.fr       */
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

void update_pos(void *param)
{
	t_scene *scene;

	scene = param;
	if (mlx_is_key_down(scene->mlx, MLX_KEY_S)
		&& mlx_is_key_down(scene->mlx, MLX_KEY_DOWN))
	{
		img->instances[0].x += 5;
	}
}

void ft_put_pixel(void *param)
{
	unsigned int i;
	unsigned int j;

	param = NULL;
	j = 0;
	while (j < img->width)
	{

		i = 0;
		while (i < img->height)
		{
			mlx_put_pixel(img, j, i, 0xFF0000FF);
			i++;
		}
		j++;
	}
}

void    print_list(t_list *list)
{
    t_list *current;
    //t_plane *plane;
	t_cylinder *cylinder;

    current = list;
    while (current != NULL)
    {
        //plane = (t_plane *)(current->content);
		cylinder = (t_cylinder *)(current->content);
        // printf("plane x is: %f\n", plane->plane_point.x);
        // printf("plane x vector is: %f\n", plane->normal_vector.x);
        // printf("plane b color is: %u\n", plane->color.b);
		printf("cylinder diameter is: %f\n", cylinder->diameter);
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
	//print_list(scene.cylinders);
	scene.mlx = mlx_init(WIDTH, HEIGHT, "miniRT", 1);
	img = mlx_new_image(scene.mlx, 512, 512);
	mlx_image_to_window(scene.mlx, img, 0, 0);
	mlx_loop_hook(scene.mlx, ft_put_pixel, scene.mlx);
	mlx_loop_hook(scene.mlx, ft_hook, scene.mlx);
	//mlx_loop_hook(scene.mlx, update_pos, &scene);
	mlx_loop(scene.mlx);
	mlx_terminate(scene.mlx);
	return (0);
}
