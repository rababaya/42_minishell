/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:02:20 by rababaya          #+#    #+#             */
/*   Updated: 2025/02/03 16:09:00 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*ret;

	ret = NULL;
	while (lst && f)
	{
		tmp = ft_lstnew(f(lst->content));
		if (tmp)
			ft_lstadd_back(&ret, tmp);
		else
		{
			ft_lstclear(&ret, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (ret);
}
