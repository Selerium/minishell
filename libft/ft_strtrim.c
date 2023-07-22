/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:01:50 by jadithya          #+#    #+#             */
/*   Updated: 2022/06/26 20:46:15 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_belongs(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen((char *) set))
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*newstr;

	i = 0;
	if (!s1)
		return (NULL);
	while (ft_belongs(s1[i], set))
		i++;
	j = ft_strlen((char *) s1) - 1;
	while (ft_belongs(s1[j], set) && j > 0)
		j--;
	if (i > j)
		return (ft_strdup(""));
	newstr = ft_substr(s1, (unsigned int) i, (j - i + 1));
	if (!newstr)
		return (NULL);
	return (newstr);
}
