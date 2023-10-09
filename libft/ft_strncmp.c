/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:38:15 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/09 18:35:57 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((i < n - 1) && n > 1 && s1[i] && s2[i])
	{
		if ((unsigned char) s1[i] == (unsigned char) s2[i])
		{
			i++;
			continue ;
		}
		else
			break ;
	}
	if ((unsigned char ) s1[i] > (unsigned char) s2[i])
		return (1);
	else if ((unsigned char ) s1[i] < (unsigned char ) s2[i])
		return (-1);
	else
		return (0);
}
