/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printzeros.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:14:36 by jadithya          #+#    #+#             */
/*   Updated: 2022/07/07 16:07:26 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libftprintf.h"

static int	ft_precheck(char *add)
{
	int	digits;
	int	power;
	int	hold;

	hold = 0;
	digits = 0;
	power = 1;
	while ((*(add - (++hold))) != '.')
	{
		if (*add == '%')
			break ;
		if (ft_isdigit(*(add - hold)))
		{
			digits += ((*(add - hold)) - 48) * power;
			power *= 10;
		}
		else if (ft_flag(*(add - hold)) && (*(add - hold)) != '-')
		{
			digits = 0;
			power = 1;
		}
	}
	return (digits);
}

static void	ft_printing(int digits, int *count, char *add, char *flags)
{
	while (digits > ft_precheck(add) && flags[1] == '1')
	{
		write(1, " ", 1);
		(*count)++;
		digits--;
	}
	while (digits-- > 0 && ft_precheck(add) > 0)
	{
		write(1, "0", 1);
		(*count)++;
	}
}

void	ft_printzeros(char *add, int *count, int s, char *flags)
{
	int	digits;
	int	power;
	int	hold;

	hold = 0;
	digits = 0;
	power = 1;
	while ((*(add - (++hold))) != '%')
	{
		if (ft_isdigit(*(add - hold)))
		{
			digits += ((*(add - hold)) - 48) * power;
			power *= 10;
		}
		else if (ft_flag(*(add - hold)) && (*(add - hold)) != '-')
		{
			digits = 0;
			power = 1;
		}
	}
	digits -= s;
	ft_printing(digits, count, add, flags);
}
