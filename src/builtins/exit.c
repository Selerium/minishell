/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:14:38 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/04 19:57:55 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	run_exit(char *num)
{
	int	n;

	n = ft_atoi(num);
	free(num);
	if (n > 255)
		run_exit(ft_itoa(n - 256, '0', 0));
	printf("Exiting minishell. Thanks :\")");
	exit(n);
}
