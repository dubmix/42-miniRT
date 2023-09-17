/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:36:24 by aehrlich          #+#    #+#             */
/*   Updated: 2023/09/17 09:42:17 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.h"

t_list	*ft_lstnew(void *cont)
{
	t_list	*ret;

	ret = malloc(sizeof(t_list));
	if (ret == NULL)
		return (NULL);
	ret->cont = cont;
	ret->next = NULL;
	return (ret);
}
