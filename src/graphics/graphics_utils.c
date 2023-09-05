/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:53:32 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/05 09:53:51 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "../raytracing/raytracing.h"

int	make_even(int nb)
{
	if (nb % 2 == 1)
		return (nb - 1);
	else
		return (nb);
}