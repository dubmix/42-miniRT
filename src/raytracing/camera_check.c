/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:10:09 by aehrlich          #+#    #+#             */
/*   Updated: 2023/09/07 16:18:25 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

bool	cam_in_cylinder(t_object *obj, t_point p_cam)
{
	t_cylinder	c;
	t_point		cap_center;
	t_point		plump_point;
	t_ray		axis_ray;
	float		t;

	c = *obj->body.cylinder;
	cap_center = vec_to_p(subtract_vectors(p_to_origin_vec(c.center), scale_vec(c.axis, c.height / 2)));
	axis_ray.direction = normalize(c.axis);
	axis_ray.origin = cap_center;
	t = (c.axis.x * p_cam.x + c.axis.y * p_cam.y + c.axis.z * p_cam.z
		- (c.axis.x * cap_center.x + c.axis.y * cap_center.y + c.axis.z * cap_center.z))
		/ (powf(c.axis.x, 2) + powf(c.axis.y, 2) + powf(c.axis.z, 2));
	if (t < 0 || t > c.height)
		return (false);
	plump_point = get_ray_point(t, axis_ray);
	if (sqrt(powf(p_cam.x - plump_point.x, 2) + powf(p_cam.y - plump_point.y, 2) + powf(p_cam.z - plump_point.z, 2)) <= c.diameter / 2)
		return (true);
	return (false);
}

bool	cam_in_plane(t_object *obj, t_point cam_coordinates)
{
	t_point		plane_point;
	t_vector	plane_norm;
	
	plane_norm = obj->body.plane->normal_vector;
	plane_point = obj->body.plane->plane_point;
	if (plane_norm.x * (cam_coordinates.x - plane_point.x) 
		+ plane_norm.y * (cam_coordinates.y - plane_point.y)
		+ plane_norm.z * (cam_coordinates.z - plane_point.z) == 0)
		return (true);
	return (false);
}

bool	cam_in_sphere(t_object *obj, t_point cam_coordinates)
{
	t_point	sphere_center;
	float	radius;

	sphere_center = obj->body.sphere->center;
	radius = obj->body.sphere->diameter / 2;
	if ((powf(cam_coordinates.x - sphere_center.x, 2) 
			+ powf(cam_coordinates.y - sphere_center.y, 2)
			+ powf(cam_coordinates.z - sphere_center.z, 2)) <= powf(radius, 2))
		return (true);
	return (false);
}

bool	camera_is_in_object(t_scene *scene)
{
	t_list		*tmp_node;
	t_object	*obj;
	t_camera	c;

	tmp_node = scene->objects;
	c = scene->camera;
	while (tmp_node)
	{
		obj = (t_object *)tmp_node->content;
		if (obj->body_type == SPHERE)
			if (cam_in_sphere(obj, c.coordinates))
				return (true);
		if (obj->body_type == PLANE)
			if (cam_in_plane(obj, c.coordinates))
				return (true);
		if (obj->body_type == CYLINDER)
			if (cam_in_cylinder(obj, c.coordinates))
				return (true);
		tmp_node = tmp_node->next;
	}
	return (false);
}
