/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:58:07 by pdelanno          #+#    #+#             */
/*   Updated: 2023/08/21 11:59:44 by pdelanno         ###   ########.fr       */
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

typedef struct s_color
{
    uint32_t r;
    uint32_t g;
    uint32_t b;
}   t_color;

#endif
