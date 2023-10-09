/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:18:37 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/09 18:35:18 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int s)
{
	if (s == 32 || (s >= 9 && s <= 13))
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *s)
{
	int		index;
	long	number;
	int		j;

	j = -1;
	index = 0;
	number = 0;
	while (ft_isspace((int) s[index]))
		index++;
	if (s[index] == '-' || s[index] == '+')
		j = index++;
	while (ft_isdigit(s[index]))
	{
		number *= 10;
		number += (((int) s[index]) - 48);
		index++;
	}
	if (j > -1 && s[j] == '-')
		number *= -1;
	if (number > INT_MAX)
		return (-1);
	if (number < INT_MIN)
		return (0);
	return (number);
}
