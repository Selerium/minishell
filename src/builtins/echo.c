/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:19:42 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/10 18:13:02 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdbool.h>

void	run_echo(char **cmd)
{
	int		i;
	bool	n;
	int		flag;

	flag = 0;
	n = (cmd[1] && ft_strncmp(cmd[1], "-n", 2) == 0);
	i = 0;
	while (cmd[++i] && ++flag)
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
