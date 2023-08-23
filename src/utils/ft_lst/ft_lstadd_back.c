/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:55:43 by aehrlich          #+#    #+#             */
/*   Updated: 2023/08/23 10:59:48 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (lst == 0 || new == 0)
		return ;
	temp = *lst;
	if (temp == 0)
	{
		*lst = new;
		return ;
	}
	while (temp)
	{
		if (temp->next == 0)
		{
			temp->next = new;
			return ;
		}
		temp = temp->next;
	}
}
