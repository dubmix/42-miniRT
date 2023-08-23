/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:52:23 by aehrlich          #+#    #+#             */
/*   Updated: 2023/02/13 10:17:33 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == 0)
		return (0);
	while (lst)
	{
		if (lst->next == 0)
			return (lst);
		lst = lst->next;
	}
	return (0);
}
