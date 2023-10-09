/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 22:28:40 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/09 18:35:57 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	ft_initdigits(int *digits, int *power, char *add, char flag)
{
	(*digits) = 0;
	(*power) = 1;
	while ((*(--add)) != flag)
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
}

static char	*ft_numcheck(char *s, char flag)
{
	if (flag == '1')
		return (++s);
	return (s);
}

//static int	ft_precheck(char *add)
//{
//	int	digits;
//	int	power;

//	digits = 0;
//	power = 1;
//	while ((*(--add)) != '.')
//	{
//		if (*add == '%')
//			break ;
//		if (ft_isdigit(*add))
//		{
//			digits += ((*add) - 48) * power;
//			power *= 10;
//		}
//		else if (ft_flag(*add) && (*add) != '-')
//		{
//			digits = 0;
//			power = 1;
//		}
//	}
//	if ((*(add)) == '%')
//		return (1);
//	return (digits);
//}

static int	ft_check(char *add)
{
	int	digits;
	int	power;

	digits = 0;
	power = 1;
	while ((*(--add)) != '%')
	{
		if (ft_isdigit(*add))
		{
			digits += ((*add) - 48) * power;
			power *= 10;
		}
		else if (ft_flag(*add) && (*add) != '-')
		{
			digits = 0;
			power = 1;
		}
	}
	return (digits);
}

void	ft_printstr(char *s, char *flags, int *count, char *add)
{
	int	digits;
	int	power;

	digits = 0;
	power = 1;
	if (s)
	{
		if (flags[2] == '0')
			digits = ft_strlen(s);
		else
			ft_initdigits(&digits, &power, add, '.');
		s = ft_numcheck(s, flags[6]);
		if (flags[0] == '0' && flags[1] != '1')
			ft_printspace(add, count, digits);
		else if (flags[1] == '1' && ft_check(add))
			ft_printzeros(add, count, digits, flags);
		if (digits > (int) ft_strlen(s))
			digits = (int) ft_strlen(s);
		write(2, s, digits);
		(*count) += digits;
		if (flags[0] == '1')
			ft_printspace(add, count, *count);
	}
	else
		ft_printstr("(null)", flags, count, add);
}
