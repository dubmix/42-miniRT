/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:52:07 by aehrlich          #+#    #+#             */
/*   Updated: 2023/08/23 11:01:47 by pdelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*node;

	if (!lst || !f || !del)
		return (0);
	ret = 0;
	while (lst)
	{
		node = ft_lstnew((*f)(lst->content));
		if (!node)
		{
			ft_lstclear(&ret, del);
			return (NULL);
		}
		ft_lstadd_back(&ret, node);
		lst = lst->next;
	}
	return (ret);
}
