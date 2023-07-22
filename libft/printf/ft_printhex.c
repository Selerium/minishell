/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 22:47:20 by jadithya          #+#    #+#             */
/*   Updated: 2022/07/08 20:06:50 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libftprintf.h"

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

static void	ft_lowhex(int n, int *count)
{
	char	ch;

	if (n < 10)
		ch = n + 48;
	else
		ch = n + 87;
	write(1, &ch, 1);
	(*count)++;
}

static void	ft_reclow(unsigned int n, int *count)
{
	if (n > 15)
		ft_reclow((n / 16), count);
	ft_lowhex((n % 16), count);
}

void	ft_printhexlow(unsigned int n, char *flags, int *count, const char *add)
{
	int	digits;

	digits = 0;
	if (flags[2] == '1' && flags[1] == '0')
		digits = printspace((char *) add, count, ft_hexdigits(n), '.');
	else if (flags[0] == '0')
		digits = printspace((char *) add, count, ft_hexdigits(n), '%');
	if (flags[3] == '1' && n != 0)
	{
		write(1, "0x", 2);
		(*count) += 2;
		flags[3] = '0';
	}
	if (flags[2] == '1' && flags[1] == '1')
		ft_printzeros((char *) add, count, *count + 1, flags);
	if (!(n == 0 && digits == 0 && flags[2] == '1'))
		ft_reclow(n, count);
	if (flags[0] == '1')
		ft_printspace((char *) add, count, *count);
}
