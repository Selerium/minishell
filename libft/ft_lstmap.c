/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 18:16:14 by jadithya          #+#    #+#             */
/*   Updated: 2022/08/31 19:54:38 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *))
{
	t_list	*first;
	t_list	*newitem;

	if (!lst)
		return (NULL);
	first = ft_lstnew(f(lst->content));
	lst = lst->next;
	while (lst)
	{
		newitem = ft_lstnew(f(lst->content));
		if (!newitem)
		{
			ft_lstdelone(newitem, del);
			return (NULL);
		}
		ft_lstadd_back(&first, newitem);
		lst = lst->next;
	}
	return (first);
}
