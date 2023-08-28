/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:39:20 by jadithya          #+#    #+#             */
/*   Updated: 2023/08/27 20:01:13 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	l1;
	size_t	l2;
	char	*newstr;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen((char *) s1);
	l2 = ft_strlen((char *) s2);
	j = (l1 + l2 + 1);
	newstr = (char *) malloc (j * sizeof(char));
	if (!newstr)
		return (NULL);
	i = -1;
	while (++i < l1)
		newstr[i] = s1[i];
	j = -1;
	while (++j < l2)
		newstr[i + j] = s2[j];
	newstr[i + j] = '\0';
	free(s1);
	return (newstr);
}
