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

	//argv = NULL;
	ptr = &scene;
	if (argc != 2)
		return (ft_parsing_error("./miniRT needs one file", "", 0));
	parsing_main(ptr, argv[1]);
	// mlx = mlx_init(WIDTH, HEIGHT, "miniRT", 1);
	// scene = mlx_new_image(mlx, 128, 128);
	// mlx_image_to_window(mlx, scene, 100, 100);
	// mlx_loop_hook(mlx, ft_put_pixel, mlx);
	// mlx_loop_hook(mlx, ft_hook, mlx);
	// mlx_loop(mlx);
	// mlx_terminate(mlx);
	return (0);
}
