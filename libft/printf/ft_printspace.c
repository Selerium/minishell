/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printspace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:14:36 by jadithya          #+#    #+#             */
/*   Updated: 2022/07/07 14:57:53 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libftprintf.h"

void	ft_printspace(char *add, int *count, int s)
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
		else if (ft_flag(*add) && (*add != '-'))
		{
			digits = 0;
			power = 1;
		}
	}
	digits -= s;
	while (digits-- > 0)
	{
		write(1, " ", 1);
		(*count)++;
	}
}
