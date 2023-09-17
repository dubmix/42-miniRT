/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:52:58 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/17 10:17:28 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

uint32_t	c_int(t_color c, float brightness, t_scene *scene)
{
	uint32_t	sc_r;
	uint32_t	sc_g;
	uint32_t	sc_b;

	sc_r = (uint32_t)(c.r * brightness
			+ (scene->ambient.color.r * scene->ambient.ratio * 0.4));
	sc_g = (uint32_t)(c.g * brightness
			+ (scene->ambient.color.g * scene->ambient.ratio * 0.4));
	sc_b = (uint32_t)(c.b * brightness
			+ (scene->ambient.color.b * scene->ambient.ratio * 0.4));
	if (sc_r > 255)
		sc_r = 255;
	if (sc_g > 255)
		sc_g = 255;
	if (sc_b > 255)
		sc_b = 255;
	return (sc_r << 24 | sc_g << 16 | sc_b << 8 | 255);
}

t_color	sp_tx(t_point closest_hit, t_obj *object)
{
	t_vector		p;
	float			u;
	float			v;
	unsigned int	pixel;
	t_sphere		*sphere;

	sphere = (t_sphere *)object->body.sphere;
	p = normalize(subtract_points(closest_hit, sphere->center));
	u = 0.5 - (atan2(-p.z, p.x) / (2.0 * 3.14));
	v = 0.5 - (asin(p.y) / 3.14);
	pixel = (int)(v * object->texture.height)
		* object->texture.width + (int)(u * object->texture.width);
	return (object->texture.color[pixel]);
}
