/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 22:30:39 by jadithya          #+#    #+#             */
/*   Updated: 2022/07/06 22:52:30 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libftprintf.h"

static void	ft_checknum(char *str, int *count, char *add, char *flags)
{
	if (str[0] == '-' && flags[1] != '0' && flags[2] != '1')
	{
		ft_printchr('-', "a000001", count, add);
		(*count)++;
		flags[6] = '1';
	}
}

void	ft_printnum(int n, char *flags, int *count, char *add)
{
	char	*str;

	if (flags[5] == '1' && n >= 0)
	{
		flags[5] = '0';
		write(1, "+", 1);
		(*count)++;
	}
	else if (flags[4] == '1' && n > -1)
	{
		flags[4] = '0';
		write(1, " ", 1);
		(*count)++;
	}
	str = ft_itoa(n, flags[2], 0);
	ft_checknum(str, count, add, flags);
	if (flags[2] == '0')
		ft_printstr(str, flags, count, add);
	else
		ft_precisionprint(str, count, add, flags);
	free(str);
}
