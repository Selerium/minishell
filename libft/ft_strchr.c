/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:33:35 by jadithya          #+#    #+#             */
/*   Updated: 2022/06/23 19:39:00 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*ch;
	char	c2;

	c2 = (char) c;
	i = 0;
	ch = (char *) s;
	while (i <= ft_strlen(ch))
	{
		if (c2 == ch[i])
			return (ch + i);
		i++;
	}
	return (NULL);
}
