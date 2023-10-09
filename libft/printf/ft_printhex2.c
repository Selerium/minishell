/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 22:47:20 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/09 18:35:57 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	printspace(char *add, int *count, int s, char flag)
{
	int	digits;
	int	power;
	int	result;

	digits = 0;
	power = 1;
	while ((*(--add)) != flag)
	{
		if (ft_isdigit(*add))
		{
			digits += ((*add) - 48) * power;
			power *= 10;
		}
	}
	result = digits;
	digits -= s;
	while (digits-- > 0)
	{
		if (flag == '%')
			write(1, " ", 1);
		else
			write(1, "0", 1);
		(*count)++;
	}
	return (result);
}

static void	ft_highhex(int n, int *count)
{
	char	ch;

	if (n < 10)
		ch = n + 48;
	else
		ch = n + 55;
	write(1, &ch, 1);
	(*count)++;
}

static void	ft_rechigh(unsigned int n, int *count)
{
	if (n > 15)
		ft_rechigh((n / 16), count);
	ft_highhex((n % 16), count);
}

void	ft_printhexhigh(unsigned int n, char *flags, int *count,
							const char *add)
{
	int	digits;

	digits = 0;
	if (flags[2] == '1' && flags[1] == '0')
		digits = printspace((char *) add, count, ft_hexdigits(n), '.');
	else if (flags[0] == '0')
		digits = printspace((char *) add, count, ft_hexdigits(n), '%');
	if (flags[3] == '1' && n != 0)
	{
		write(1, "0X", 2);
		(*count) += 2;
		flags[3] = '0';
	}
	if (flags[2] == '1' && flags[1] == '1')
		ft_printzeros((char *) add, count, *count + 1, flags);
	if (!(n == 0 && digits == 0 && flags[2] == '1'))
		ft_rechigh(n, count);
	if (flags[0] == '1')
		ft_printspace((char *) add, count, *count);
}
