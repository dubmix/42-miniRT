/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:00:16 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/28 14:25:30 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

mlx_image_t *img;

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

// void	ft_render(void *param)
// {
// 	//t_scene *scene;
// 	//t_color	*color;
// 	unsigned int pixel_x;
// 	unsigned int pixel_y;
// 	//t_ray *ray;

// 	param = NULL;
// 	pixel_x = 0;
// 	while (pixel_x < img->width)
// 	{
//         pixel_y = 0;
// 		while (pixel_y < img->height)
// 		{
// 			//ray = create_ray(scene, pixel_x, pixel_y);
// 			//color = trace_ray(scene, ray);
// 			mlx_put_pixel(img, pixel_x, pixel_y, 0xFF0000FF);
// 			pixel_y++;
// 		}
// 		pixel_x++;
// 	}
// }

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
	ft_render(ptr);
	//test(ptr);
	// mlx_loop_hook(scene.mlx, ft_put_pixel, scene.mlx);
	mlx_loop_hook(scene.mlx, ft_hook, scene.mlx);
	mlx_loop(scene.mlx);
	mlx_terminate(scene.mlx);
	return (0);
}
