/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:47:30 by aehrlich          #+#    #+#             */
/*   Updated: 2023/08/23 11:02:10 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.h"

int	ft_lstsize(t_list *lst)
{
	int	cnt;

	cnt = 0;
	if (lst == 0)
		return (0);
	while (lst)
	{
		lst = lst->next;
		cnt++;
	}
	return (cnt);
}
