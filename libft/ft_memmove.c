/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:13:20 by jadithya          #+#    #+#             */
/*   Updated: 2022/06/26 19:12:56 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dest;
	char	*surc;

	dest = (char *) dst;
	surc = (char *) src;
	if (!dest && !surc)
		return (NULL);
	if (dest < surc)
		while (len--)
			*dest++ = *surc++;
	else
	{
		dest += (len - 1);
		surc += (len - 1);
		while (len--)
			*dest-- = *surc--;
	}
	return (dst);
}
