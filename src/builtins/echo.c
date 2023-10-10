/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:19:42 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/10 18:14:06 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdbool.h>

void	run_echo(char **cmd)
{
	int		i;
	bool	n;

	i = 2;
	n = (cmd[1] && ft_strncmp(cmd[1], "-n", 2) == 0);
	if (!n)
		i = 0;
	else
		while (ft_strncmp(cmd[i], "-n", 2) == 0)
			i++;
	if (n)
		i--;
	while (cmd[++i])
	{
		if (n && i == 1)
			continue ;
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
	}
	if (!n)
		printf("\n");
}
