/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:25:05 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/09 18:35:57 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	holder;

	holder = ft_strlen(dst);
	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	if (size < holder)
		return (size + ft_strlen(src));
	if (size > (ft_strlen(src) + holder))
		size = ft_strlen(src) + holder + 1;
	while (dst[i] != '\0')
		i++;
	j = 0;
	while ((i + j) < size - 1)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (size != 0)
		dst[i + j] = '\0';
	j++;
	return (ft_strlen(src) + holder);
}
