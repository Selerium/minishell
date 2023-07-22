/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precisionprint.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:02:20 by jadithya          #+#    #+#             */
/*   Updated: 2022/07/07 14:23:04 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libftprintf.h"

static void	ft_checker(char *add, int *digits, int *power, char *str)
{
	(*digits) = 0;
	(*power) = 1;
	while ((*(--add)) != '.')
	{
		if (ft_isdigit(*add))
		{
			(*digits) += ((*add) - 48) * (*power);
			(*power) *= 10;
		}
		else if (ft_flag(*add))
		{
			(*digits) = 0;
			(*power) = 1;
		}
	}
	(*digits) -= ft_strlen(str);
	if (str[0] == '-')
		(*digits)++;
}

void	ft_precisionprint(char *str, int *count, char *add, char *flags)
{
	int	digits;
	int	power;
	int	neg;

	digits = 0;
	power = 1;
	neg = 0;
	ft_checker(add, &digits, &power, str);
	if (flags[6] != '1' && str[0] == '-')
	{
		write(1, "-", 1);
		(*count)++;
		str++;
		neg++;
	}
	while (digits-- > 0)
	{
		write(1, "0", 1);
		(*count)++;
	}
	if (ft_strncmp(str, "0", 2) != 0)
		flags[2] = '0';
	ft_printstr(str, flags, count, add);
	if (neg != 0)
		str--;
}
