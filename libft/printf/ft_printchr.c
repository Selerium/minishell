/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 22:18:31 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/09 18:35:57 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_printchr(int c, char *flags, int *count, char *add)
{
	char	ch;

	ch = (char) c;
	if (flags[0] == '0')
	{
		ft_printspace(add, count, 1);
		(*count)++;
	}
	write(1, &ch, 1);
	if (flags[0] == '1')
	{
		ft_printspace(add, count, 1);
		(*count)++;
	}
}
