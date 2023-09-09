/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:19:42 by jadithya          #+#    #+#             */
/*   Updated: 2023/09/09 17:13:43 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	run_echo(char **cmd)
{
	int		i;

	i = -1;
	while (cmd[++i])
		printf("%s ", cmd[i]);
	if (ft_strncmp(cmd[1], "-n", 2) == 0)
		printf("\n");
	exit(0);
}
