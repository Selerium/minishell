/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:21:00 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/09 18:35:57 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*newstr;

	if (!s)
		return (NULL);
	newstr = (char *) malloc ((ft_strlen((char *) s) + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	i = 0;
	while (i < ft_strlen((char *) s))
	{
		newstr[i] = f(i, (char) s[i]);
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
