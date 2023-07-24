/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:56:41 by jadithya          #+#    #+#             */
/*   Updated: 2022/07/02 22:45:00 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	ft_count(int n)
{
	int	count;

	count = 1;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n > 9)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static int	ft_power(int n, int p)
{
	int	num;

	num = 1;
	while (p--)
		num *= n;
	return (num);
}

static int	ft_abs(int n)
{
	if (n >= 0)
		return (n);
	else
		return (n * -1);
}

char	*ft_itoa(int n, char flag, int values)
{
	int		i;
	int		size;
	char	*newstr;

	size = ft_count(n);
	newstr = (char *) malloc ((size + 1) * sizeof(char));
	if (!newstr)
		return (newstr);
	i = 0;
	if (n < 0)
	{
		newstr[i++] = '-';
		size--;
	}
	if (flag == '1')
		while (values-- > 0)
			write(1, "0", 1);
	while (size--)
		newstr[i++] = ft_abs((n / ft_power(10, size)) % 10) + 48;
	newstr[i] = '\0';
	return (newstr);
}
