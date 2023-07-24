/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:21:15 by jadithya          #+#    #+#             */
/*   Updated: 2023/06/10 21:53:20 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	size_t	i;
	size_t	length;

	i = 0;
	if (!s)
		return (ft_strdup(""));
	length = ft_strlen((char *) s);
	if (start > (length - 1))
		return (ft_strdup(""));
	if (len > length)
		len = length;
	newstr = (char *) malloc ((len + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	if (len != 0)
	{
		while (i < len && i < length)
		{
			newstr[i] = (char) s[(size_t) start + i];
			i++;
		}
	}
	newstr[i] = '\0';
	return (newstr);
}
