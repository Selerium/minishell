/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:16:25 by jadithya          #+#    #+#             */
/*   Updated: 2022/06/26 21:01:46 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

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
