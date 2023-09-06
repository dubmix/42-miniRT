/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:58:07 by pdelanno          #+#    #+#             */
/*   Updated: 2023/09/06 14:22:42 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "types.h"

# define WIDTH 512
# define HEIGHT 512

void	ft_hook(void *param);
void	ft_render(t_scene *scene);
int		parsing_main(t_scene *scene, char *file_name);
int		ft_parsing_error(char *str, char *object, int return_value);

#endif
