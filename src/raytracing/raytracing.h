/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 09:49:28 by aehrlich          #+#    #+#             */
/*   Updated: 2023/08/23 13:45:19 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../types.h"
#include "../../miniRT.h"

void	init_point(t_point *p, float x, float y, float z);
void	init_vector(t_vector *v, float x, float y, float z);
float	dot_product(t_vector v1, t_vector v2);
void	add_vectors(t_vector *result, t_vector v1, t_vector v2);
void	subtract_vectors(t_vector *result, t_vector v1, t_vector v2);
