/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:52:43 by jadithya          #+#    #+#             */
/*   Updated: 2022/06/26 23:05:10 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newitem;

	newitem = (t_list *) malloc (sizeof(t_list));
	if (!newitem)
		return (NULL);
	newitem->content = content;
	newitem->next = NULL;
	return (newitem);
}
