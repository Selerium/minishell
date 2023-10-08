/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:14:38 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/08 23:40:44 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	single_exit(t_chunk *cmds, t_env *envs, char *cmd)
{
	free_cmd(cmds);
	free_envs(envs);
	run_exit(cmd);
}

void	run_exit(char *num)
{
	int	n;
	int	i;
	int	space;

	i = 0;
	if (!num)
	{
		printf("Exiting minishell. Thanks :\")");
		exit(0);
	}
	while (num[i])
	{
		if (ft_isdigit(num[i]))
			exit(255);
		if (ft_isspace(num[i]))
			space++;
		if (space > 1)
			exit (1);
		i++;
	}
	n = ft_atoi(num);
	free(num);
	if (n > 255)
		run_exit(ft_itoa(n - 256, '0', 0));
	printf("Exiting minishell. Thanks :\")");
	exit(n);
}
