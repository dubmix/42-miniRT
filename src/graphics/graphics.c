/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:59:42 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/30 10:40:58 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "../raytracing/raytracing.h"

t_point    pixel_to_coord(t_scene *scene, int pixel_x, int pixel_y)
{
    t_point coord;
    float   width = 30.0;
    float   height = 30.0;

    coord.x = scene->camera.coordinates.x - (width / 2)
        + (width * ((float)pixel_x / (float)img->width));
    coord.y = scene->camera.coordinates.y + (height / 2)
        - (height * ((float)pixel_y / (float)img->height));
    coord.z = width / (2 * tan((double)scene->camera.field_of_view / 2));
    return (coord);
}

void	ft_render(void *param)
{
	t_scene *scene;
	uint32_t	color;
	unsigned int pixel_x;
	unsigned int pixel_y;
	t_ray ray;
	t_ray n;

	scene = param;
	pixel_x = 0;
	while (pixel_x < img->width)
	{
        pixel_y = 0;
		while (pixel_y < img->height)
		{
			ray = create_ray(scene, pixel_x, pixel_y);
			color = trace_ray(scene, ray);
			//color = (uint32_t)(color * 0.7);// apply_light(scene);
			mlx_put_pixel(img, pixel_x, pixel_y, color);
			pixel_y++;
		}
		pixel_x++;
	}
}

/* float	apply_light(t_scene *scene, t_point p)
{
	float i;
	t_vector	N;
	t_list *temp;
	t_sphere sphere;
	t_point t1;
	t_vector L;

	t1.x = 10.0;
	t1.y = 10.0;
	t1.z = 10.0;
	temp = scene->spheres;
	i = 0.0;
	i += scene->ambient.ratio;
	while (temp)
	{
		sphere = *((t_sphere *)temp->content);
		normalize(&N, t1, sphere.center);
		subtract_points(&L, scene->light.coordinates, t1);
		//shadow_check;
		//closest intersection;

		if (dot_product(N, L) > 0)
			i += scene->light.brightness_ratio * dot_product(N, L)/vector_length(scene->light.coordinates, t1);
	}
	return (i);
} */

t_ray	create_ray(t_scene *scene, int pixel_x, int pixel_y)
{
    t_ray ray;
	
	ray.origin = scene->camera.coordinates;
	ray.direction = init_vector_p(pixel_to_coord(scene, pixel_x, pixel_y),
					scene->camera.coordinates);
	return (ray);
}

uint32_t rgb_to_uint32(uint32_t r, uint32_t g, uint32_t b, float brightness)
{
	uint32_t sc_r;
	uint32_t sc_g;
	uint32_t sc_b;

	sc_r = (uint32_t)(r * brightness);
	sc_g = (uint32_t)(g * brightness);
	sc_b = (uint32_t)(b * brightness);
	return (sc_r << 24 | sc_g << 16 | sc_b << 8 | 255);
}

uint32_t trace_ray(t_scene *scene, t_ray ray)
{
    uint32_t color;
	t_list *temp;
	t_sphere sphere;
    t_point closest;
    //t_result result;

	temp = scene->spheres;
	while (temp)
	{
		sphere = *((t_sphere *)temp->content);
		if (sphere_intersect(sphere, ray, &closest))
		{
			color = rgb_to_uint32(sphere.color.r,
					sphere.color.g, sphere.color.b, scene->ambient.ratio);
			return (color);
		}
		temp = temp->next;
	}
    return (rgb_to_uint32(0, 0, 0, 0));
}