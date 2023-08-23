/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:58:07 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/23 11:49:58 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "mlx/include/MLX42/MLX42.h"
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "src/parsing/parsing.h"
# include "src/utils/utils.h"

# define WIDTH 512
# define HEIGHT 512

static mlx_image_t *scene;

void test();

#endif
