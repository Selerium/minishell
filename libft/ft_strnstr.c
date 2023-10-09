/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:35:21 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/09 18:35:57 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!little[0])
		return ((char *) big);
	if (len == 0)
		return (NULL);
	while (i < len && i < ft_strlen((char *) big))
	{
		j = 0;
		if (little[0] == big[i])
		{
			while ((little[j] == big[i + j]) && little[j] != '\0')
				j++;
			if (little[j] == '\0')
				break ;
		}
		i++;
	}
	if (big[i] != '\0' && (i + j) <= len && (i + j) <= ft_strlen(big) && j)
		return ((char *)(big + i));
	return (NULL);
}
