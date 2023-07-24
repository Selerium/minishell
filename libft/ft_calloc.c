/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:07:12 by jadithya          #+#    #+#             */
/*   Updated: 2022/06/22 17:15:30 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	char	*ns;

	if (size != 0 && num > (SIZE_MAX / size))
		return (NULL);
	ns = (char *) malloc (num * size);
	if (!ns)
		return (NULL);
	ft_bzero(ns, num * size);
	return (ns);
}
