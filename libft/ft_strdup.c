/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:16:25 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/09 18:35:57 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*newstr;
	int		index;

	index = 0;
	newstr = (char *) malloc((ft_strlen((char *) s) + 1) * (sizeof(char)));
	if (!newstr)
		return (NULL);
	while (s[index] != '\0')
	{
		newstr[index] = s[index];
		index++;
	}
	newstr[index] = '\0';
	return (newstr);
}
