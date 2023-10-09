/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printspace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:14:36 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/09 18:35:57 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

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
