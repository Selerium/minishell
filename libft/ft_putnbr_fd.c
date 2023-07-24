/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:29:44 by jadithya          #+#    #+#             */
/*   Updated: 2022/06/26 18:46:45 by jadithya         ###   ########.fr       */
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

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	int		size;
	char	newstr[12];

	size = ft_count(n);
	i = 0;
	if (n < 0)
	{
		newstr[i++] = '-';
		size--;
	}
	while (size--)
		newstr[i++] = ft_abs((n / ft_power(10, size)) % 10) + 48;
	newstr[i] = '\0';
	write(fd, newstr, ft_strlen(newstr));
}
