/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:00:42 by jadithya          #+#    #+#             */
/*   Updated: 2022/06/26 19:10:03 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*dst;
	char	*surc;

	dst = (char *) dest;
	surc = (char *) src;
	i = 0;
	if (!dst && !surc)
		return (NULL);
	while (i < n)
	{
		dst[i] = surc[i];
		i++;
	}
	return (dest);
}
