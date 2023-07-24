/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:57:56 by jadithya          #+#    #+#             */
/*   Updated: 2022/06/22 15:12:26 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memset(void *ptr, int value, size_t length)
{
	size_t	i;
	char	*p;

	p = (char *) ptr;
	i = 0;
	while (i < length)
	{
		p[i] = value;
		i++;
	}
	return (ptr);
}
