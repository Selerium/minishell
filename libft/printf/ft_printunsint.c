/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunsint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 22:31:53 by jadithya          #+#    #+#             */
/*   Updated: 2022/07/08 20:46:14 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libftprintf.h"

static int	printzeros(char *add, int *count, int s, char flag)
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
		write(1, "0", 1);
		(*count)++;
	}
	return (result);
}

void	ft_printunsint(unsigned long n, char *flags, int *count,
						const char *add)
{
	char	ch;
	int		i;
	int		size;
	int		digits;

	digits = 0;
	i = ft_digits(n);
	size = i--;
	if (flags[2] == '1')
		digits = printzeros((char *) add, count, size, '.');
	else if (flags[1] == '1' && flags[0] == '0')
		digits = printzeros((char *) add, count, size, '%');
	else if (flags[0] == '0')
		ft_printspace((char *) add, count, size);
	while (i >= 0 && !(n == 0 && digits == 0 && flags[2] == '1'))
	{
		ch = (n / (ft_power(10, i))) + 48;
		write(1, &ch, 1);
		(*count)++;
		n %= ft_power(10, i);
		i--;
	}
	if (flags[0] == '1')
		ft_printspace((char *) add, count, *count);
}
